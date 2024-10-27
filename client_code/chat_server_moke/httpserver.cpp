#include "httpserver.h"

#include "util.h"


// protobuf 编译后的一些头文件
#include "file.qpb.h"
#include "gateway.qpb.h"
#include "user.qpb.h"
#include "friend.qpb.h"
#include "voice_recognition.qpb.h"
#include "base.qpb.h"

#include <QDebug>
#include <QHttpServerResponse>


HttpServer* HttpServer::_instance = nullptr;

HttpServer::HttpServer()
{}

HttpServer* HttpServer::getInstance(){
    if(_instance == nullptr){
        _instance = new HttpServer();
    }
    return _instance;
}

my_chat_proto::UserInfo makeUserInfo(int index, const QByteArray& headPortraitByte){
    my_chat_proto::UserInfo userInfo;
    userInfo.setUserId(QString::number(100 + index));
    userInfo.setNickName("小八");
    userInfo.setPersonSignature("你好");
    userInfo.setHeadPortrait(headPortraitByte);
    userInfo.setPhoneNumber("12345466");
    return userInfo;
}

// 这几个消息的构造要多看几遍 proto 文件中 这些不同消息类型的结构
my_chat_proto::MessageInfo makeTextMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait){
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    my_chat_proto::TextMessageInfo textMessage;
    textMessage.setTextContent("这是一条消息");

    my_chat_proto::MessageContent messageContent;
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::TEXT);
    messageContent.setTextMessage(textMessage);

    messageInfo.setMessage(messageContent);
    return messageInfo;
}

my_chat_proto::MessageInfo makeImageMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait){
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    my_chat_proto::ImageMessageInfo imageMessage;
    imageMessage.setFileId("testImage");

    my_chat_proto::MessageContent messageContent;
    messageContent.setImageMessage(imageMessage);
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::IMAGE);

    messageInfo.setMessage(messageContent);
    return messageInfo;
}

bool HttpServer::initHttpServer(){
    // 直接 listen，内部集成了 socket,bind,listen
    int ret = _httpServer.listen(QHostAddress::Any, 8080);

    // 配置“路由”，就是把 请求路径 和对应的 处理函数 进行关联
    _httpServer.route("/ping", [=](const QHttpServerRequest& httpReq) {
        (void)httpReq;
        qDebug() << "httpserver: get a request";
        return "pong";
    });

    _httpServer.route("/service/user/get_user_info", [=](const QHttpServerRequest& httpReq) {
        return this->getUserInfo(httpReq);
    });

    _httpServer.route("/service/friend/get_friend_list", [=](const QHttpServerRequest& httpReq) {
        return this->getFriendUserList(httpReq);
    });

    _httpServer.route("/service/friend/get_chat_session_list", [=](const QHttpServerRequest& httpReq) {
        return this->getChatSessionList(httpReq);
    });

    _httpServer.route("/service/friend/get_pending_friend_events", [=](const QHttpServerRequest& httpReq) {
        return this->getApplyUserList(httpReq);
    });

    // listen 成功就返回绑定的端口 8080
    return ret == 8080;
}

QHttpServerResponse HttpServer::getUserInfo(const QHttpServerRequest& httpReq){
    LOG() << "get a http request: get user info";
    // 解析请求
    my_chat_proto::GetUserInfoReq reqObj;
    // 把请求的body反序列化
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应(构造假的数据)
    my_chat_proto::GetUserInfoRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/testPortrait.png");
    my_chat_proto::UserInfo userInfo = makeUserInfo(1, headPortraitByte);
    respObj.setUserInfo(userInfo);

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");

    return httpResp;
}

QHttpServerResponse HttpServer::getFriendUserList(const QHttpServerRequest &httpReq)
{
    LOG() << "get a http request: get friend user list";
    // 解析请求
    my_chat_proto::GetFriendListReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::GetFriendListRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/testPortrait.png");
    for(int i = 0; i < 20; ++i){
        my_chat_proto::UserInfo userInfo = makeUserInfo(i, headPortraitByte);
        respObj.friendList().push_back(userInfo);
    }

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::getChatSessionList(const QHttpServerRequest &httpReq){
    LOG() << "get a http request: get chat session list";
    // 解析请求
    my_chat_proto::GetChatSessionListReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::GetChatSessionListRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");


    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    QList<my_chat_proto::ChatSessionInfo> chatSessionInfoList;
    for(int i = 0; i < 20; ++i){
        my_chat_proto::ChatSessionInfo chatSession;
        QString chatSessionId = QString::number(100 + i);
        chatSession.setChatSessionId(chatSessionId);
        chatSession.setChatSessionName("会话" + QString::number(i));
        chatSession.setSingleChatFriendId(QString::number(1000 + 1));
        chatSession.setHeadPortrait(headPortraitByte);

        chatSession.setPrevMessage(makeTextMessageInfo(i, chatSessionId, headPortraitByte));
        chatSessionInfoList.push_back(chatSession);
    }
    respObj.setChatSessionInfoList(chatSessionInfoList);

    // 序列化
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::getApplyUserList(const QHttpServerRequest &httpReq){
    LOG() << "get a http request: get apply user list";
    // 解析请求
    my_chat_proto::GetPendingFriendEventListReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::GetPendingFriendEventListRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    QList<my_chat_proto::FriendEvent> friendEventList;
    for(int i = 0; i < 10; ++i){
        my_chat_proto::FriendEvent friendEvent;
        friendEvent.setEventId(QString::number(10 + i));
        friendEvent.setSender(makeUserInfo(i, headPortraitByte));
        friendEventList.push_back(friendEvent);
    }
    respObj.setEvent(friendEventList);

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}
