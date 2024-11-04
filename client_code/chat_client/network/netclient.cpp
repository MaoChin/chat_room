#include "netclient.h"

#include "../model/data.h"
#include "../model/datacenter.h"
#include "../toast.h"

#include <QNetworkReply>
#include <QUuid>

namespace network{

NetClient::NetClient(model::DataCenter* dataCenter)
    :_dataCenter(dataCenter)
{
    // websocket 的初始化不能在这里！因为这个初始化会给客户端发送身份验证，而登陆注册的时候还没有身份！！
    // 应该是主窗口初始化的时候进行websocket的初始化
    // initWebsocket();
}

void NetClient::ping(){
    // 构建请求
    QNetworkRequest httpReq;
    httpReq.setUrl(QUrl(HTTP_URL + "/ping"));

    // 发起请求，接收响应
    // 异步的请求，只是发出请求，响应由信号槽进行处理
    QNetworkReply* httpResp = _httpClient.get(httpReq);

    // 由于不可靠的网络，这个响应不直到啥时候能回来，所以设置信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        if(httpResp->error() != QNetworkReply::NoError){
            // 出错了
            LOG() << "HTTP ping error: " << httpResp->errorString();
            httpResp->deleteLater();
            return;
        }
        // ping成功
        LOG() << "HTTP ping success，response message: " << httpResp->readAll();
        httpResp->deleteLater();
    });
}

/////////////////////////////
/// \brief Websocket 相关
///

// 初始化 websocket
void NetClient::initWebsocket(){
    // 先关联5个信号槽
    connect(&_websocketClient, &QWebSocket::connected, this, [=]() {
        LOG() << "websocket client: websocket connected";
        // websocket连接成功后发送验证信息
        webSocketSendAuthentication();
    });

    connect(&_websocketClient, &QWebSocket::disconnected, this, [=]() {
        LOG() << "websocket client: websocket disconnected";
    });

    connect(&_websocketClient, &QWebSocket::errorOccurred, this, [=](QAbstractSocket::SocketError error) {
        LOG() << "websocket client: websocket error" << error;
    });

    // 收到文本消息的信号槽
    connect(&_websocketClient, &QWebSocket::textMessageReceived, this, [=](const QString& message) {
        LOG() << "websocket client: websocket receive a text message: " << message;
    });

    // 收到二进制消息的信号槽
    connect(&_websocketClient, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray& byteArray) {
        LOG() << "websocket client: websocket receive a binary message, length: " << byteArray.length();
        my_chat_proto::NotifyMessage notifyMessage;
        notifyMessage.deserialize(&_serializer, byteArray);
        handleWebsocketResp(notifyMessage);
    });

    // 建立连接
    _websocketClient.open(QUrl(WEBSOCKET_URL));
}

void NetClient::webSocketSendAuthentication(){
    // websocket 连接成功后客户端需要给服务器发送身份验证信息
    // 验证信息的请求和响应在 gateway.proto 文件中定义好了
    my_chat_proto::ClientAuthenticationReq clientAuthReq;

    // 标识请求id，给每个请求都生成唯一id，方便打印日志进行区分
    clientAuthReq.setRequestId(makeRequestId());
    // 标识登录会话id
    clientAuthReq.setSessionId(_dataCenter->getLoginSessionId());

    // 进行序列化，方便网络传输
    QByteArray body = clientAuthReq.serialize(&_serializer);
    _websocketClient.sendBinaryMessage(body);
    LOG() << "websocket 身份认证，requestId: " << clientAuthReq.requestId() << " , loginSessonId: " << clientAuthReq.sessionId();
}


void NetClient::handleWebsocketResp(const my_chat_proto::NotifyMessage &notifyMessage){
    if(notifyMessage.notifyType() == my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_ADD_APPLY_NOTIFY){
        // 发起好友申请的通知
        model::UserInfo friendInfo;
        friendInfo.load(notifyMessage.friendAddApply().userInfo());
        handleWebsocketAddFriendApply(friendInfo);
    }
    else if(notifyMessage.notifyType() == my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_ADD_PROCESS_NOTIFY){
        // 发起好友申请处理结果的通知
        model::UserInfo friendInfo;
        friendInfo.load(notifyMessage.friendProcessResult().userInfo());
        bool agree = notifyMessage.friendProcessResult().agree();
        handleWebsocketAddFriendProcess(friendInfo, agree);
    }
    else if(notifyMessage.notifyType() == my_chat_proto::NotifyTypeGadget::NotifyType::FRIEND_REMOVE_NOTIFY){
        // 发起好友删除的通知
        const QString& friendId = notifyMessage.friendDelete().userId();
        handleWebsocketDeleteFriend(friendId);
    }
    else if(notifyMessage.notifyType() == my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_SESSION_CREATE_NOTIFY){
        // 发起创建群聊会话的通知
        model::ChatSessionInfo chatSessionInfo;
        chatSessionInfo.load(notifyMessage.newChatSessionInfo().chatSessionInfo());
        handleWebsocketCreateChatSession(chatSessionInfo);
    }
    else if(notifyMessage.notifyType() == my_chat_proto::NotifyTypeGadget::NotifyType::CHAT_MESSAGE_NOTIFY){
        // 发起收到新消息的通知
        // 1. 取出新消息并转换成客户端的结构
        model::MessageInfo messageInfo;
        messageInfo.load(notifyMessage.newMessageInfo().messageInfo());
        // 2. 对新消息进行处理
        handleWebsocketNewMessage(messageInfo);
    }
    else{
        LOG() << "notify message type error: " << notifyMessage.notifyType();
        return;
    }

}

void NetClient::handleWebsocketNewMessage(const model::MessageInfo &messageInfo){
    QList<model::MessageInfo>* messageList = _dataCenter->getChatSessionRecentMessage(messageInfo._chatSessionId);
    if(messageList == nullptr){
        // 1. 这个新消息 所属会话中的消息列表没有在本地加载，需要通过HTTP网络加载整个消息列表
        connect(_dataCenter, &model::DataCenter::getChatSessionRecentMessageAsyncNoUIDone, this,
                &NetClient::receiveMessage, Qt::UniqueConnection);
        // 这个操作不需要更新右侧消息显示区
        _dataCenter->getChatSessionRecentMessageAsync(messageInfo._chatSessionId, false);
    }
    else{
        // 2. 这个新消息 所属会话中的消息列表已经在本地加载，则直接把新消息插入到其中即可
        messageList->push_back(messageInfo);
        this->receiveMessage(messageInfo._chatSessionId);
    }
}

void NetClient::receiveMessage(const QString &chatSessionId){
    if(_dataCenter->getCurChatSessionId() == chatSessionId){
        // 收到新消息的会话是当前选中的会话，则需要更新显示
        const model::MessageInfo& newMessage = _dataCenter->getChatSessionRecentMessage(chatSessionId)->back();

        emit _dataCenter->netClientReceiveMessageDone(newMessage);
    }
    else{
        // 收到新消息的会话不是当前选中的会话，更新中间页面未读消息描述
        _dataCenter->addUnreadNum(chatSessionId);
        Toast::showMessage("收到新消息");
    }
    // 都需要更新中间页面的会话预览
    // 使用信号槽，使会话预览时更新最后一条消息
    emit _dataCenter->updateLastMessage(chatSessionId);
}

void NetClient::handleWebsocketDeleteFriend(const QString &friendId){
    // 1. 给个通知
    model::UserInfo* friendInfo = _dataCenter->findFriendById(friendId);
    QString friendNickName;
    if(friendInfo){
        friendNickName = friendInfo->_nickName;
    }
    Toast::showMessage("好友 " + friendNickName + " 已将您删除！");

    // 2. 删除 DataCenter 中好友列表的数据
    _dataCenter->deleteFriendById(friendId);
    // 3. 通知界面变化，更新 好友列表 / 会话列表
    emit _dataCenter->deleteFriendAsyncDone();
}

void NetClient::handleWebsocketAddFriendApply(const model::UserInfo &friendInfo){
   // 1. 把好友信息添加到dataCenter的好友申请列表中
    QList<model::UserInfo>* applyUserList = _dataCenter->getApplyUserList();
    if (applyUserList == nullptr) {
        applyUserList = new QList<model::UserInfo>();
    }
    // 把新的元素放到列表前面
    applyUserList->push_front(friendInfo);

    // 2. 通知界面更新.
    emit _dataCenter->receiveAddFriendApplyDone();
}

void NetClient::handleWebsocketAddFriendProcess(const model::UserInfo &friendInfo, bool agree){
    if(agree){
        // 对方同意了
        // 1. 把好友信息添加到dataCenter的好友列表中
        QList<model::UserInfo>* friendUserList = _dataCenter->getFriendUserList();
        if (friendUserList == nullptr) {
            friendUserList = new QList<model::UserInfo>();
        }
        // 把新的元素放到列表前面
        friendUserList->push_front(friendInfo);

        // 2. 通知界面更新.
        emit _dataCenter->receiveAddFriendProcessDone(agree, friendInfo._nickName);
    }
    else{
        // 对方没同意, 直接通知
        emit _dataCenter->receiveAddFriendProcessDone(agree, friendInfo._nickName);
    }
}

void NetClient::handleWebsocketCreateChatSession(const model::ChatSessionInfo &chatSessionInfo){
    // 1. 把会话信息添加到dataCenter的会话列表中
    QList<model::ChatSessionInfo>* chatSessionList = _dataCenter->getChatSessionList();
    if (chatSessionList == nullptr) {
        chatSessionList = new QList<model::ChatSessionInfo>();
    }
    // 把新的元素放到列表前面
    chatSessionList->push_front(chatSessionInfo);

    // 2. 通知界面更新.
    emit _dataCenter->receiveCreateChatSessionDone();
}



//////////////////////////////
/// \brief HTTP 相关
///
QString NetClient::makeRequestId(){
    // 直接使用uuid
    return "Request" + QUuid::createUuid().toString().sliced(25, 12);
}

// 把发送 HTTP 请求的操作单独封装成一个函数
QNetworkReply* NetClient::sendHttpRequest(const QString &httpRequestPath, const QByteArray &httpBody){
    // 构建网络请求
    QNetworkRequest httpReq;
    httpReq.setUrl(QUrl(HTTP_URL + httpRequestPath));
    httpReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-protobuf");
    // 异步的请求，只是发出请求，响应由信号槽进行处理
    return _httpClient.post(httpReq, httpBody);
}

// 获取当前用户自身信息
void NetClient::getMyself(const QString &loginSessionId){
    // 构造请求body
    my_chat_proto::GetUserInfoReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    QByteArray body = reqObj.serialize(&_serializer);

    // 异步的请求，只是发出请求，响应由信号槽进行处理
    QNetworkReply* httpResp = sendHttpRequest("/service/user/get_user_info", body);
    LOG() << "getMyself: send request, requestId: " << reqObj.requestId();

    // 关联网络请求返回时的信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        // 处理响应
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetUserInfoRsp> respObj =
            handleHttpResponse<my_chat_proto::GetUserInfoRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getMyself error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 保存数据
        _dataCenter->setMyself(respObj);

        // 最后要通知调用逻辑，HTTP 响应已经处理完成 --》通过自定义信号槽通知
        emit _dataCenter->getMyselfAsyncDone();
        LOG() << "getMyself: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getFriendUserList(const QString &logSessionId){
    // 构造请求
    my_chat_proto::GetFriendListReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(logSessionId);
    QByteArray body = reqObj.serialize(&_serializer);

    // 发送请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/get_friend_list", body);
    LOG() << "getFriendUserList: send request, requestId: " << reqObj.requestId();

    // 关联网络请求返回时的信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetFriendListRsp> respObj =
            handleHttpResponse<my_chat_proto::GetFriendListRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getFriendUserList error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到dataCenter处理一下数据
        _dataCenter->setFriendUserList(respObj);

        // 发出响应处理完成信号
        emit _dataCenter->getFriendUserListAsyncDone();
        LOG() << "getFriendUserList: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getChatSessionList(const QString& loginSessionId){
    // 构造请求
    my_chat_proto::GetChatSessionListReq reqObj;
    reqObj.setSessionId(loginSessionId);
    reqObj.setRequestId(makeRequestId());
    QByteArray body = reqObj.serialize(&_serializer);

    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/get_chat_session_list", body);
    LOG() << "getChatSesionList: send request, requestId: " << reqObj.requestId();

    // 关联HTTP请求返回时的信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetChatSessionListRsp> respObj =
            handleHttpResponse<my_chat_proto::GetChatSessionListRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getChatSesionList error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到dataCenter处理一下数据
        _dataCenter->setChatSessionList(respObj);

        // 发出响应处理完毕的信号，让界面进行填充
        emit _dataCenter->getChatSessionListAsyncDone();
        LOG() << "getFriendUserList: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getApplyUserList(const QString& loginSessionId){
    // 构造请求
    my_chat_proto::GetPendingFriendEventListReq reqObj;
    reqObj.setSessionId(loginSessionId);
    reqObj.setRequestId(makeRequestId());

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/get_pending_friend_events", body);
    LOG() << "getApplyUserList: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetPendingFriendEventListRsp> respObj =
            handleHttpResponse<my_chat_proto::GetPendingFriendEventListRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getApplyUserList error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把proto类型的数据放到DataCenter中
        _dataCenter->setApplyUserList(respObj);

        // 发出 getApplyUserListAsyncDone 信号，让界面填充相关信息
        emit _dataCenter->getApplyUserListAsyncDone();
        LOG() << "getApplyUserList: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getChatSessionRecentMessage(const QString &loginSessionId, const QString &chatSessionId, bool updateUI){
    // 构造请求
    my_chat_proto::GetRecentMsgReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setChatSessionId(chatSessionId);
    reqObj.setMsgCount(50);
    reqObj.setLoginSessionId(loginSessionId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/message_storage/get_recent", body);
    LOG() << "getChatSessionRecentMessage: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetRecentMsgRsp> respObj =
            handleHttpResponse<my_chat_proto::GetRecentMsgRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getChatSessionRecentMessage error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把proto类型的数据放到DataCenter中
        _dataCenter->setChatSessionRecentMessage(chatSessionId, respObj);

        // 发出 getChatSessionRecentMessageAsyncDone 信号，让界面填充相关信息
        // 根据 updateUI 决定是否要更新界面！如果不是当前选中的会话收到消息，就不需要更新界面
        if(updateUI){
            emit _dataCenter->getChatSessionRecentMessageAsyncDone(chatSessionId);
        }
        else{
            emit _dataCenter->getChatSessionRecentMessageAsyncNoUIDone(chatSessionId);
        }
        LOG() << "getChatSessionRecentMessageAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

// extraInfo 传递一些特殊信息，如文件名，其他类型的消息给""即可
void NetClient::sendMessage(const QString &loginSessionId, const QString &chatSessionId, model::MessageType messageType,
                            const QByteArray &content, const QString& extraInfo){
    // 构造请求
    my_chat_proto::NewMessageReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setChatSessionId(chatSessionId);
    reqObj.setLoginSessionId(loginSessionId);

    my_chat_proto::MessageContent messageContent;
    if(messageType == model::MessageType::TEXT_TYPE){
        messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::TEXT);
        my_chat_proto::TextMessageInfo textMessageInfo;
        textMessageInfo.setTextContent(content);
        // fileIf是服务器存储的时候设置的，这里给个空就好

        messageContent.setTextMessage(textMessageInfo);
    }
    else if(messageType == model::MessageType::FILE_TYPE){
        messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::FILE);
        my_chat_proto::FileMessageInfo fileMessageInfo;
        // fileIf是服务器存储的时候设置的，这里给个空就好
        fileMessageInfo.setFileId("");
        fileMessageInfo.setFileName(extraInfo);
        fileMessageInfo.setFileSize(content.size());
        fileMessageInfo.setFileContents(content);

        messageContent.setFileMessage(fileMessageInfo);
    }
    else if(messageType == model::MessageType::IMAGE_TYPE){
        messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::IMAGE);
        my_chat_proto::ImageMessageInfo imageMessageInfo;
        // fileIf是服务器存储的时候设置的，这里给个空就好
        imageMessageInfo.setFileId("");
        imageMessageInfo.setImageContent(content);

        messageContent.setImageMessage(imageMessageInfo);
    }
    else if(messageType == model::MessageType::VOICE_TYPE){
        messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::VOICE);
        my_chat_proto::VoiceMessageInfo voiceMessageInfo;
        // fileIf是服务器存储的时候设置的，这里给个空就好
        voiceMessageInfo.setFileId("");
        voiceMessageInfo.setVoiceContents(content);

        messageContent.setVoiceMessage(voiceMessageInfo);
    }
    else{
        LOG() << "message type error: " << messageType;
        return;
    }
    reqObj.setMessage(messageContent);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/message_transmit/new_message", body);
    LOG() << "sendMessage: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::NewMessageRsp> respObj =
            handleHttpResponse<my_chat_proto::NewMessageRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "sendMessage error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 这个数据不需要写到dataCenter中

        // 发出 sendMessageAsyncDone 信号，让界面填充相关信息
        // 消息处理时需要将消息渲染到界面，所以传递消息相关的信息出去
        emit _dataCenter->sendMessageAsyncDone(messageType, content, extraInfo);
        LOG() << "sendMessageAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });

}

void NetClient::modifyNickName(const QString& loginSessionId, const QString &newNickName){
    // 构造请求
    my_chat_proto::SetUserNicknameReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setNickname(newNickName);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/set_nickname", body);
    LOG() << "modifyNickName: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::SetUserNicknameRsp> respObj =
            handleHttpResponse<my_chat_proto::SetUserNicknameRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "modifyNickName error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把用户的新用户名放到DataCenter中
        _dataCenter->modifyNickName(newNickName);

        // 发出 modifyNickNameAsyncDome 信号，让界面修改相关信息
        emit _dataCenter->modifyNickNameAsyncDone();
        LOG() << "modifyNickNameAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::modifyPersonalSignature(const QString &loginSessionId, const QString &newPersonalSignature){
    // 构造请求
    my_chat_proto::SetUserSignatureReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setSignature(newPersonalSignature);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/set_signature", body);
    LOG() << "modifyPersonalSignature: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::SetUserSignatureRsp> respObj =
            handleHttpResponse<my_chat_proto::SetUserSignatureRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "modifyPersonalSignature error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把用户的新个性签名放到DataCenter中
        _dataCenter->modifyPersonalSignature(newPersonalSignature);

        // 发出 modifyPersonalSignatureAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->modifyPersonalSignatureAsyncDone();
        LOG() << "modifyPersonalSignatureAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getPhoneVerifyCode(const QString &phoneNum){
    // 构造请求
    my_chat_proto::PhoneVerifyCodeReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setPhoneNumber(phoneNum);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/get_phone_verify_code", body);
    LOG() << "getPhoneVerifyCode: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::PhoneVerifyCodeRsp> respObj =
            handleHttpResponse<my_chat_proto::PhoneVerifyCodeRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "modifyPersonalSignature error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把verifyCodeId设置到dataCenter中
        _dataCenter->setPhoneVerifyCodeId(respObj->verifyCodeId());

        // 发出 getPhoneVerifyCodeAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->getPhoneVerifyCodeAsyncDone();
        LOG() << "getPhoneVerifyCodeAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::modifyPhoneNum(const QString &loginSessionId, const QString &newPhoneNum,
                               const QString& verifyCodeId, const QString& verifyCode){
    // 构造请求
    my_chat_proto::SetUserPhoneNumberReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setPhoneNumber(newPhoneNum);
    reqObj.setPhoneVerifyCodeId(verifyCodeId);
    reqObj.setPhoneVerifyCode(verifyCode);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/set_phone", body);
    LOG() << "modifyPhoneNum: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::SetUserPhoneNumberRsp> respObj =
            handleHttpResponse<my_chat_proto::SetUserPhoneNumberRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "modifyPhoneNum error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把用户的新手机号放到DataCenter中
        _dataCenter->modifyPhoneNum(newPhoneNum);

        // 发出 modifyPersonalSignatureAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->modifyPhoneNumAsyncDone();
        LOG() << "modifyPhoneNumAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::modifyHeadPortrait(const QString &loginSessionId, const QByteArray &newHeadPortraitBytes){
    // 构造请求
    my_chat_proto::SetUserHeadPortraitReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setHeadPortrait(newHeadPortraitBytes);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/set_head_portrait", body);
    LOG() << "modifyHeadPortrait: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::SetUserHeadPortraitRsp> respObj =
            handleHttpResponse<my_chat_proto::SetUserHeadPortraitRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "modifyHeadPortrait error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把用户的新头像放到DataCenter中
        _dataCenter->modifyHeadPortrait(newHeadPortraitBytes);

        // 发出 modifyHeadPortraitAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->modifyHeadPortraitAsyncDone();
        LOG() << "modifyHeadPortraitAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::addFriendApply(const QString& loginSessionId, const QString &friendId){
    // 构造请求
    my_chat_proto::FriendAddReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setFriendId(friendId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/add_friend_apply", body);
    LOG() << "addFriendApply: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::FriendAddRsp> respObj =
            handleHttpResponse<my_chat_proto::FriendAddRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "addFriendApply error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 这里不需要在 DataCenter 做任何记录

        // 发出 addFriendApplyAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->addFriendApplyAsyncDone();
        LOG() << "addFriendApplyAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::acceptAddFriendApply(const QString &loginSessionId, const QString &friendId){
    // 构造请求
    my_chat_proto::FriendAddProcessReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setAgree(true);
    reqObj.setSessionId(loginSessionId);
    reqObj.setApplyUserId(friendId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/add_friend_process", body);
    LOG() << "acceptAddFriendApply: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::FriendAddProcessRsp> respObj =
            handleHttpResponse<my_chat_proto::FriendAddProcessRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "acceptAddFriendApply error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在DataCenter中进行处理：1.在申请列表中删除该信息 2.在好友列表中加入该好友信息；
        model::UserInfo newFriendInfo = _dataCenter->deleteFromApplyUserList(friendId);
        QList<model::UserInfo>* friendList = _dataCenter->getFriendUserList();
        friendList->push_front(newFriendInfo);

        // 发出 acceptAddFriendApplyAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->acceptAddFriendApplyAsyncDone(newFriendInfo._nickName);
        LOG() << "acceptAddFriendApplyAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::refuseAddFriendApply(const QString &loginSessionId, const QString &friendId){
    // 构造请求
    my_chat_proto::FriendAddProcessReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setAgree(false);
    reqObj.setSessionId(loginSessionId);
    reqObj.setApplyUserId(friendId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/add_friend_process", body);
    LOG() << "refuseAddFriendApply: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::FriendAddProcessRsp> respObj =
            handleHttpResponse<my_chat_proto::FriendAddProcessRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "refuseAddFriendApply error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在DataCenter中进行处理：直接在申请列表中删除该用户即可
        model::UserInfo friendInfo = _dataCenter->deleteFromApplyUserList(friendId);

        // 发出 refuseAddFriendApplyAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->refuseAddFriendApplyAsyncDone(friendInfo._nickName);
        LOG() << "refuseAddFriendApplyAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::deleteFriend(const QString& loginSessionId, const QString &friendId){
    // 构造请求
    my_chat_proto::FriendDeleteReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setFriendId(friendId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/delete_friend", body);
    LOG() << "deleteFriend: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::FriendDeleteRsp> respObj =
            handleHttpResponse<my_chat_proto::FriendDeleteRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "deleteFriend error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 再回到DataCenter中把好友从好友列表中删除掉
        LOG() << "test1";
        _dataCenter->deleteFriendById(friendId);

        // 发出 deleteFriendAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->deleteFriendAsyncDone();
        LOG() << "deleteFriendAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::createGroupChatSession(const QString &loginSessionId, const QList<QString> &groupSessionIdList){
    // 构造请求
    my_chat_proto::ChatSessionCreateReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setChatSessionName("新的群聊");

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/create_chat_session", body);
    LOG() << "createGroupChatSession: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::ChatSessionCreateRsp> respObj =
            handleHttpResponse<my_chat_proto::ChatSessionCreateRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "createGroupChatSession error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 创建会话不需要在dataCenter中做什么操作，会通过websocket进行推送

        // 发出 createGroupChatSessionAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->createGroupChatSessionAsyncDone();
        LOG() << "createGroupChatSessionAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getChatSessionMemberList(const QString &loginSessionId, const QString &chatSessionId){
    // 构造请求
    my_chat_proto::GetChatSessionMemberReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setChatSessionId(chatSessionId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/get_chat_session_member", body);
    LOG() << "getChatSessionMemberList: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetChatSessionMemberRsp> respObj =
            handleHttpResponse<my_chat_proto::GetChatSessionMemberRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getChatSessionMemberList error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在dataCenter中设置群聊会话成员列表
        _dataCenter->setChatSessionMemberList(chatSessionId, respObj->memberInfoList());

        // 发出 getChatSessionMemberListAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->getChatSessionMemberListAsyncDone();
        LOG() << "getChatSessionMemberListAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::searchUser(const QString &loginSessionId, const QString &searchKey){
    // 构造请求
    my_chat_proto::UserSearchReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    reqObj.setSearchKey(searchKey);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/friend/search_user", body);
    LOG() << "searchUser: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::UserSearchRsp> respObj =
            handleHttpResponse<my_chat_proto::UserSearchRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "searchUser error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在dataCenter中设置用户搜索列表
        _dataCenter->setSearchUserList(respObj->userInfo());

        // 发出 searchUserAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->searchUserAsyncDone();
        LOG() << "searchUserAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::searchHistoryMessageBySearchKey(const QString &loginSessionId, const QString &chatSessionId, const QString &searchKey){
    // 构造请求
    my_chat_proto::MsgSearchBySearchKeyReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setLoginSessionId(loginSessionId);
    reqObj.setChatSessionId(chatSessionId);
    reqObj.setSearchKey(searchKey);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/message_storage/search_history_by_search_key", body);
    LOG() << "searchHistoryMessageBySearchKey: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::MsgSearchBySearchKeyRsp> respObj =
            handleHttpResponse<my_chat_proto::MsgSearchBySearchKeyRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "searchHistoryMessageBySearchKey error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在dataCenter中设置历史消息搜索列表
        _dataCenter->setSearchHistoryMessageList(respObj->msgList());

        // 发出 searchHistoryMessageAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->searchHistoryMessageAsyncDone();
        LOG() << "searchHistoryMessageAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::searchHistoryMessageByTime(const QString &loginSessionId, const QString &chatSessionId, const QDateTime &startTime, const QDateTime &endTime){
    // 构造请求
    my_chat_proto::MsgSearchByTimeReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setLoginSessionId(loginSessionId);
    reqObj.setChatSessionId(chatSessionId);
    reqObj.setStartTime(startTime.toSecsSinceEpoch());
    reqObj.setOverTime(endTime.toSecsSinceEpoch());

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/message_storage/search_history_by_time", body);
    LOG() << "searchHistoryMessageByTime: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::MsgSearchByTimeRsp> respObj =
            handleHttpResponse<my_chat_proto::MsgSearchByTimeRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "searchHistoryMessageByTime error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 在dataCenter中设置历史消息搜索列表
        _dataCenter->setSearchHistoryMessageList(respObj->msgList());

        // 发出 searchHistoryMessageAsyncDone 信号，让界面修改相关信息
        emit _dataCenter->searchHistoryMessageAsyncDone();
        LOG() << "searchHistoryMessageAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::userNameSignUp(const QString &userName, const QString &password){
    // 构造请求
    my_chat_proto::UserRegisterReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setNickname(userName);
    reqObj.setPassword(password);
    reqObj.setVerifyCodeId("");
    reqObj.setVerifyCode("");

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/username_register", body);
    LOG() << "userNameSignUp: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::UserRegisterRsp> respObj =
            handleHttpResponse<my_chat_proto::UserRegisterRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "userNameSignUp error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            // 这里也要发出信号，通知用户失败及原因
            emit _dataCenter->userNameSignUpAsyncDone(false, errmsg);
            return;
        }

        // 对于注册来说不需要在dataCenter中进行任何设置

        // 发出 userNameSignUpAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->userNameSignUpAsyncDone(true, errmsg);
        LOG() << "userNameSignUpAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::userNameLogin(const QString &userName, const QString &password){
    // 构造请求
    my_chat_proto::UserLoginReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setNickname(userName);
    reqObj.setPassword(password);
    reqObj.setVerifyCodeId("");
    reqObj.setVerifyCode("");

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/username_login", body);
    LOG() << "userNameLogin: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::UserLoginRsp> respObj =
            handleHttpResponse<my_chat_proto::UserLoginRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "userNameLogin error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            // 这里也要发出信号，通知用户失败及原因
            emit _dataCenter->userNameLoginAsyncDone(false, errmsg);
            return;
        }

        // 在dataCenter中设置 loginSessionId 信息
        _dataCenter->setLoginSessionId(respObj->loginSessionId());

        // 发出 userNameLoginAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->userNameLoginAsyncDone(true, errmsg);
        LOG() << "userNameLoginAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::phoneSignUp(const QString &phoneNum, const QString& verifyCodeId, const QString &verifyCode){
    // 构造请求
    my_chat_proto::PhoneRegisterReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setPhoneNumber(phoneNum);
    reqObj.setVerifyCodeId(verifyCodeId);
    reqObj.setVerifyCode(verifyCode);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/phone_register", body);
    LOG() << "phoneSignUp: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::PhoneRegisterRsp> respObj =
            handleHttpResponse<my_chat_proto::PhoneRegisterRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "phoneSignUp error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            // 这里也要发出信号，通知用户失败及原因
            emit _dataCenter->phoneSignUpAsyncDone(false, errmsg);
            return;
        }

        // 对于注册来说不需要在dataCenter中进行任何设置

        // 发出 phoneSignUpAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->phoneSignUpAsyncDone(true, errmsg);
        LOG() << "phoneSignUpAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::phoneLogin(const QString &phoneNum, const QString& verifyCodeId, const QString &verifyCode){
    // 构造请求
    my_chat_proto::PhoneLoginReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setPhoneNumber(phoneNum);
    reqObj.setVerifyCodeId(verifyCodeId);
    reqObj.setVerifyCode(verifyCode);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/user/phone_login", body);
    LOG() << "phoneLogin: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::PhoneLoginRsp> respObj =
            handleHttpResponse<my_chat_proto::PhoneLoginRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "phoneLogin error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            // 这里也要发出信号，通知用户失败及原因
            emit _dataCenter->phoneLoginAsyncDone(false, errmsg);
            return;
        }

        // 在dataCenter中设置 loginSessionId 信息
        _dataCenter->setLoginSessionId(respObj->loginSessionId());

        // 发出 phoneLoginAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->phoneLoginAsyncDone(true, errmsg);
        LOG() << "phoneLoginAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::getSingleFileContent(const QString &loginSessionId, const QString &fileId){
    // 构造请求
    my_chat_proto::GetSingleFileReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setFileId(fileId);
    reqObj.setSessionId(loginSessionId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/file/get_single_file", body);
    LOG() << "getSingleFileContent: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetSingleFileRsp> respObj =
            handleHttpResponse<my_chat_proto::GetSingleFileRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getSingleFileContent error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 文件类型很多（图片，文件，语音），并且可能很大，所以就不在dataCenter中存了，而是直接通过信号槽返回

        // 发出 getSingleFileContentAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->getSingleFileContentAsyncDone(fileId, respObj->fileData().fileContent());
        LOG() << "getSingleFileContentAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });
}

void NetClient::voiceConvertText(const QString &loginSessionId, const QString &fileId, const QByteArray &content){
    // 构造请求
    my_chat_proto::VoiceRecognitionReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setVoiceContent(content);
    reqObj.setSessionId(loginSessionId);

    QByteArray body = reqObj.serialize(&_serializer);
    // 发送HTTP请求
    QNetworkReply* httpResp = sendHttpRequest("/service/voice/recognition", body);
    LOG() << "voiceConvertText: send request, requestId: " << reqObj.requestId();

    // 关联HTTP响应的槽函数
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::VoiceRecognitionRsp> respObj =
            handleHttpResponse<my_chat_proto::VoiceRecognitionRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "voiceConvertText error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 这里转换结果也不再dataCenter中存储了，直接通过信号槽带出去即可

        // 发出 voiceConvertTextAsyncDone 信号，让界面修改相关信息,这个信号需要把成功与否的信息带出去展示给用户
        emit _dataCenter->voiceConvertTextAsyncDone(fileId, respObj->recognitionResult());
        LOG() << "voiceConvertTextAsyncDone: handle response succeed, requestId: " << respObj->requestId();
    });

}


}  // end namespace
