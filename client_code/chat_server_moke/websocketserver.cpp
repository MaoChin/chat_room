#include "websocketserver.h"
#include "util.h"

#include <QWebSocket>

// 单例
WebsocketServer* WebsocketServer::_instance = nullptr;

WebsocketServer::WebsocketServer()
    :_websocketServer("websocket server", QWebSocketServer::NonSecureMode)
{}

WebsocketServer* WebsocketServer::getInstance(){
    if(_instance == nullptr){
        _instance = new WebsocketServer();
    }
    return _instance;
}

bool WebsocketServer::initWebsocket(){
    // 连接信号槽
    connect(&_websocketServer, &QWebSocketServer::newConnection, this, [=]() {
        qDebug() << "websocket server: connected";

        // 获取用于通信的socket，这个_websocketServer中的socket相当于listenSocket！
        // nextPendingConnection 操作类似于 accept
        QWebSocket* socket = _websocketServer.nextPendingConnection();

        // 再连接 socket 的信号槽，这些信号和客户端的就一样了（不用connected了）
        connect(socket, &QWebSocket::disconnected, this, [=]() {
            qDebug() << "websocket server: disconnected";

            // 客户端断开连接时 断开所有的自定义信号槽
            // 因为这些信号槽是 this 和 this 之间关联的！！而this是WebsocketServer，不会销毁的！
            // 之所以是 this 和 this 关联，是为了使用 socket 这个句柄！！！
            disconnect(this, &WebsocketServer::sendTextResp, this, nullptr);
            disconnect(this, &WebsocketServer::sendImageResp, this, nullptr);
            disconnect(this, &WebsocketServer::sendFileResp, this, nullptr);
            disconnect(this, &WebsocketServer::sendVoiceResp, this, nullptr);
            disconnect(this, &WebsocketServer::sendFriendDelete, this, nullptr);
            disconnect(this, &WebsocketServer::sendAddFriendApply, this, nullptr);
            disconnect(this, &WebsocketServer::sendAddFriendProcess, this, nullptr);
            disconnect(this, &WebsocketServer::sendCreateChatSession, this, nullptr);
        });

        connect(socket, &QWebSocket::errorOccurred, this, [=](QAbstractSocket::SocketError error) {
            qDebug() << "websocket server: error " << error;
        });

        // 收到文本数据
        connect(socket, &QWebSocket::textMessageReceived, this, [=](const QString& message) {
            qDebug() << "websocket server: receive text message: " << message;
        });

        // 收到二进制数据
        connect(socket, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray& byteArray) {
            qDebug() << "websocket server: receive binary message, length: " << byteArray.length();
        });

        // 自定义的信号槽：推送一条测试文本消息
        connect(this, &WebsocketServer::sendTextResp, this, [=]() {
            // 此处就可以捕获到 socket 对象, 从而可以通过 socket 对象给客户端返回数据.
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }
            // 构造响应数据
            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::MessageInfo messageInfo = makeTextMessageInfo(_messageIndex++, "1", headPortraitByte);

            my_chat_proto::NotifyNewMessage notifyNewMessage;
            notifyNewMessage.setMessageInfo(messageInfo);

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_MESSAGE_NOTIFY);
            notifyMessage.setNewMessageInfo(notifyNewMessage);

            // 序列化
            QByteArray body = notifyMessage.serialize(&_serializer);

            // 发送消息给客户端
            socket->sendBinaryMessage(body);

            LOG() << "websocket: send a new text message: " << messageInfo.message().textMessage().textContent();
        });


        // 自定义的信号槽：推送一条测试图片消息
        connect(this, &WebsocketServer::sendImageResp, this, [=]() {
            // 此处就可以捕获到 socket 对象, 从而可以通过 socket 对象给客户端返回数据.
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }
            // 构造响应数据
            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::MessageInfo messageInfo = makeImageMessageInfo(this->_messageIndex++, "2", headPortraitByte);

            my_chat_proto::NotifyNewMessage notifyNewMessage;
            notifyNewMessage.setMessageInfo(messageInfo);

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_MESSAGE_NOTIFY);
            notifyMessage.setNewMessageInfo(notifyNewMessage);

            // 序列化
            QByteArray body = notifyMessage.serialize(&_serializer);

            // 发送消息给客户端
            socket->sendBinaryMessage(body);

            LOG() << "websocket: send a new image message: " << messageInfo.message().imageMessage().fileId();
        });

        connect(this, &WebsocketServer::sendFileResp, this, [=]() {
            // 此处就可以捕获到 socket 对象, 从而可以通过 socket 对象给客户端返回数据.
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }
            // 构造响应数据
            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::MessageInfo messageInfo = makeFileMessageInfo(this->_messageIndex++, "2", headPortraitByte);

            my_chat_proto::NotifyNewMessage notifyNewMessage;
            notifyNewMessage.setMessageInfo(messageInfo);

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_MESSAGE_NOTIFY);
            notifyMessage.setNewMessageInfo(notifyNewMessage);

            // 序列化
            QByteArray body = notifyMessage.serialize(&this->_serializer);

            // 发送消息给客户端
            socket->sendBinaryMessage(body);

            LOG() << "websocket: send a new file message: " << messageInfo.message().fileMessage().fileName();
        });

        connect(this, &WebsocketServer::sendVoiceResp, this, [=]() {
            // 此处就可以捕获到 socket 对象, 从而可以通过 socket 对象给客户端返回数据.
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }
            // 构造响应数据
            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::MessageInfo messageInfo = makeVoiceMessageInfo(this->_messageIndex++, "2", headPortraitByte);

            my_chat_proto::NotifyNewMessage notifyNewMessage;
            notifyNewMessage.setMessageInfo(messageInfo);

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_MESSAGE_NOTIFY);
            notifyMessage.setNewMessageInfo(notifyNewMessage);

            // 序列化
            QByteArray body = notifyMessage.serialize(&this->_serializer);

            // 发送消息给客户端
            socket->sendBinaryMessage(body);

            LOG() << "websocket: send a new voice message: " << messageInfo.message().voiceMessage().fileId();
        });

        connect(this, &WebsocketServer::sendFriendDelete, this, [=]() {
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_REMOVE_NOTIFY);

            my_chat_proto::NotifyFriendDelete notifyFriendRemove;
            notifyFriendRemove.setUserId("10");
            notifyMessage.setFriendDelete(notifyFriendRemove);

            QByteArray body = notifyMessage.serialize(&_serializer);
            socket->sendBinaryMessage(body);
            LOG() << "websocket: send friend delete: userId=10";
        });

        connect(this, &WebsocketServer::sendAddFriendApply, this, [=]() {
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_ADD_APPLY_NOTIFY);

            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::UserInfo userInfo = makeUserInfo(100, headPortraitByte);

            my_chat_proto::NotifyFriendAddApply friendAddApply;
            friendAddApply.setUserInfo(userInfo);

            notifyMessage.setFriendAddApply(friendAddApply);

            QByteArray body = notifyMessage.serialize(&_serializer);
            socket->sendBinaryMessage(body);
            LOG() << "websocket: send add friend apply";
        });

        connect(this, &WebsocketServer::sendAddFriendProcess, this, [=](bool agree) {
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }

            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_ADD_PROCESS_NOTIFY);

            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::UserInfo userInfo = makeUserInfo(100, headPortraitByte);

            my_chat_proto::NotifyFriendAddProcess friendAddProcess;
            friendAddProcess.setUserInfo(userInfo);
            friendAddProcess.setAgree(agree);

            notifyMessage.setFriendProcessResult(friendAddProcess);

            QByteArray body = notifyMessage.serialize(&_serializer);
            socket->sendBinaryMessage(body);
            LOG() << "websocket: send add friend process, userId= "
                  << userInfo.userId() << ", agree= " << agree;
        });

        connect(this, &WebsocketServer::sendCreateChatSession, this, [=]() {
            if (socket == nullptr || !socket->isValid()) {
                LOG() << "socket is invalid";
                return;
            }

            QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
            my_chat_proto::NotifyMessage notifyMessage;
            notifyMessage.setNotifyEventId("");
            notifyMessage.setNotifyType(my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_SESSION_CREATE_NOTIFY);

            my_chat_proto::MessageInfo messageInfo = makeTextMessageInfo(0, "200", headPortraitByte);

            my_chat_proto::ChatSessionInfo chatSessionInfo;
            chatSessionInfo.setChatSessionId("200");
            chatSessionInfo.setSingleChatFriendId("");
            chatSessionInfo.setChatSessionName("新的群聊");
            chatSessionInfo.setPrevMessage(messageInfo);
            chatSessionInfo.setHeadPortrait(headPortraitByte);

            my_chat_proto::NotifyNewChatSession newChatSession;
            newChatSession.setChatSessionInfo(chatSessionInfo);
            notifyMessage.setNewChatSessionInfo(newChatSession);

            // 序列化操作
            QByteArray body = notifyMessage.serialize(&_serializer);

            // 通过 websocket 推送数据
            socket->sendBinaryMessage(body);
            LOG() << "websocket: send create chat session";
        });

    });

    // 绑定端口，启动服务
    bool ok = _websocketServer.listen(QHostAddress::Any, 8081);
    return ok;
}



