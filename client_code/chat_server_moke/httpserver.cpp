#include "httpserver.h"

#include "util.h"

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

bool HttpServer::initHttpServer(){
    // 直接 listen，内部集成了 socket,bind,listen
    int ret = _httpServer.listen(QHostAddress::Any, 8080);

    // 配置“路由”，就是把 请求路径 和对应的 处理函数 进行关联
    _httpServer.route("/ping", [=](const QHttpServerRequest& httpReq) {
        (void)httpReq;
        qDebug() << "httpserver: get a request";
        return "pong";
    });

    // 获取用户信息
    _httpServer.route("/service/user/get_user_info", [=](const QHttpServerRequest& httpReq) {
        return this->getUserInfo(httpReq);
    });

    // 获取好友列表
    _httpServer.route("/service/friend/get_friend_list", [=](const QHttpServerRequest& httpReq) {
        return this->getFriendUserList(httpReq);
    });

    // 获取会话列表
    _httpServer.route("/service/friend/get_chat_session_list", [=](const QHttpServerRequest& httpReq) {
        return this->getChatSessionList(httpReq);
    });

    // 获取好友申请列表
    _httpServer.route("/service/friend/get_pending_friend_events", [=](const QHttpServerRequest& httpReq) {
        return this->getApplyUserList(httpReq);
    });

    // 获取指定会话的最近历史消息
    _httpServer.route("/service/message_storage/get_recent", [=](const QHttpServerRequest& httpReq) {
        return this->getChatSessionRecentMessage(httpReq);
    });

    // 发送消息
    _httpServer.route("/service/message_transmit/new_message", [=](const QHttpServerRequest& httpReq) {
        return this->sendMessage(httpReq);
    });

    _httpServer.route("/service/user/set_nickname", [=](const QHttpServerRequest& httpReq) {
        return this->setNickName(httpReq);
    });

    _httpServer.route("/service/user/set_signature", [=](const QHttpServerRequest& httpReq) {
        return this->setUserSignature(httpReq);
    });

    _httpServer.route("/service/user/get_phone_verify_code", [=](const QHttpServerRequest& httpReq) {
        return this->getPhoneVerifyCode(httpReq);
    });

    _httpServer.route("/service/user/set_phone", [=](const QHttpServerRequest& httpReq) {
        return this->setPhoneNum(httpReq);
    });

    _httpServer.route("/service/user/set_head_portrait", [=](const QHttpServerRequest& httpReq) {
        return this->setHeadPortrait(httpReq);
    });

    _httpServer.route("/service/friend/delete_friend", [=](const QHttpServerRequest& httpReq) {
        return this->deleteFriend(httpReq);
    });

    _httpServer.route("/service/friend/add_friend_apply", [=](const QHttpServerRequest& httpReq) {
        return this->addFriendApply(httpReq);
    });

    _httpServer.route("/service/friend/add_friend_process", [=](const QHttpServerRequest& httpReq) {
        return this->addFriendProcess(httpReq);
    });

    _httpServer.route("/service/friend/create_chat_session", [=](const QHttpServerRequest& httpReq) {
        return this->createChatSession(httpReq);
    });

    _httpServer.route("/service/friend/get_chat_session_member", [=](const QHttpServerRequest& httpReq) {
        return this->getChatSessionMember(httpReq);
    });

    _httpServer.route("/service/friend/search_user", [=](const QHttpServerRequest& httpReq) {
        return this->searchUser(httpReq);
    });

    _httpServer.route("/service/message_storage/search_history_by_search_key", [=](const QHttpServerRequest& httpReq) {
        return this->searchHistoryBySearchKey(httpReq);
    });

    _httpServer.route("/service/message_storage/search_history_by_time", [=](const QHttpServerRequest& httpReq) {
        return this->searchHistoryByTime(httpReq);
    });

    _httpServer.route("/service/user/username_login", [=](const QHttpServerRequest& httpReq) {
        return this->userNameLogin(httpReq);
    });

    _httpServer.route("/service/user/username_register", [=](const QHttpServerRequest& httpReq) {
        return this->userNameSignUp(httpReq);
    });

    _httpServer.route("/service/user/phone_login", [=](const QHttpServerRequest& httpReq) {
        return this->phoneLogin(httpReq);
    });

    _httpServer.route("/service/user/phone_register", [=](const QHttpServerRequest& httpReq) {
        return this->phoneSignUp(httpReq);
    });

    _httpServer.route("/service/file/get_single_file", [=](const QHttpServerRequest& httpReq) {
        return this->getSingleFile(httpReq);
    });

    _httpServer.route("/service/voice/recognition", [=](const QHttpServerRequest& httpReq) {
        return this->recognition(httpReq);
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

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    my_chat_proto::UserInfo userInfo = makeUserInfo(29, headPortraitByte);
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

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
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
        QString chatSessionId = QString::number(i);
        chatSession.setChatSessionId(chatSessionId);
        chatSession.setChatSessionName("会话" + QString::number(i));
        chatSession.setSingleChatFriendId(QString::number(i));
        chatSession.setHeadPortrait(headPortraitByte);

        chatSession.setPrevMessage(makeTextMessageInfo(i, chatSessionId, headPortraitByte));
        chatSessionInfoList.push_back(chatSession);
    }

    // 整个群聊会话
    my_chat_proto::ChatSessionInfo chatSession;
    QString chatSessionId = QString::number(1000);
    chatSession.setChatSessionId(chatSessionId);
    chatSession.setChatSessionName("会话" + QString::number(1000));
    chatSession.setSingleChatFriendId("");
    chatSession.setHeadPortrait(headPortraitByte);

    chatSession.setPrevMessage(makeTextMessageInfo(1000, chatSessionId, headPortraitByte));
    chatSessionInfoList.push_back(chatSession);

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

QHttpServerResponse HttpServer::getChatSessionRecentMessage(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: get chat session recent message";
    // 解析请求
    my_chat_proto::GetRecentMsgReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::GetRecentMsgRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    for (int i = 0; i < 30; ++i) {
        my_chat_proto::MessageInfo messageInfo = makeTextMessageInfo(i, "2000", headPortraitByte);
        respObj.msgList().push_back(messageInfo);
    }
    my_chat_proto::MessageInfo imageMessageInfo = makeImageMessageInfo(30, "2000", headPortraitByte);
    respObj.msgList().push_back(imageMessageInfo);
    my_chat_proto::MessageInfo fileMessageInfo = makeFileMessageInfo(31, "2000", headPortraitByte);
    respObj.msgList().push_back(fileMessageInfo);
    my_chat_proto::MessageInfo speechMessageInfo = makeVoiceMessageInfo(32, "2000", headPortraitByte);
    respObj.msgList().push_back(speechMessageInfo);

    // 序列化
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::sendMessage(const QHttpServerRequest &httpReq)
{
    LOG() << "get a http request: send message";
    // 解析请求
    my_chat_proto::NewMessageReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    if (reqObj.message().messageType() == my_chat_proto::MessageTypeGadget::MessageType::TEXT) {
        LOG() << "发送的消息内容=" << reqObj.message().textMessage().textContent();
    }

    // 构造响应
    my_chat_proto::NewMessageRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::setNickName(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: set nickName";
    // 解析请求
    my_chat_proto::SetUserNicknameReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::SetUserNicknameRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::setUserSignature(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: set userSignature";
    // 解析请求
    my_chat_proto::SetUserSignatureReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::SetUserSignatureRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::getPhoneVerifyCode(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: get phoneVerifyCode";
    // 解析请求
    my_chat_proto::PhoneVerifyCodeReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::PhoneVerifyCodeRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setVerifyCodeId("testVerifyCodeId");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::setPhoneNum(const QHttpServerRequest &httpReq){
    LOG() << "get a http request: set phone number";
    // 解析请求
    my_chat_proto::SetUserPhoneNumberReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::SetUserPhoneNumberRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::setHeadPortrait(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: set head portrait";
    // 解析请求
    my_chat_proto::SetUserHeadPortraitReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::SetUserHeadPortraitRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::deleteFriend(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: delete friend";
    // 解析请求
    my_chat_proto::FriendDeleteReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::FriendDeleteRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::addFriendApply(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: add friend apply";
    // 解析请求
    my_chat_proto::FriendAddReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::FriendAddRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setNotifyEventId("");

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::addFriendProcess(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: add friend pocess";
    // 解析请求
    my_chat_proto::FriendAddProcessReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::FriendAddProcessRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setNewSessionId("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::createChatSession(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: create chat session";
    // 解析请求
    my_chat_proto::ChatSessionCreateReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::ChatSessionCreateRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::getChatSessionMember(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: get chat session member";
    // 解析请求
    my_chat_proto::GetChatSessionMemberReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::GetChatSessionMemberRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    // 循环的构造多个 userInfo, 添加到 memberInfoList 中
    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    for (int i = 0; i < 10; ++i) {
        my_chat_proto::UserInfo userInfo = makeUserInfo(i, headPortraitByte);
        respObj.memberInfoList().push_back(userInfo);
    }

    // 序列化
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::searchUser(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: search user";
    // 解析请求
    my_chat_proto::UserSearchReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::UserSearchRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    for (int i = 0; i < 20; ++i) {
        my_chat_proto::UserInfo userInfo = makeUserInfo(i, headPortraitByte);
        respObj.userInfo().push_back(userInfo);
    }
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应给客户端
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::searchHistoryBySearchKey(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: search history by search key";
    // 解析请求
    my_chat_proto::MsgSearchBySearchKeyReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::MsgSearchBySearchKeyRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    for (int i = 0; i < 10; ++i) {
        my_chat_proto::MessageInfo message = makeTextMessageInfo(i, reqObj.chatSessionId(), headPortraitByte);
        respObj.msgList().push_back(message);
    }
    // 构造图片消息
    my_chat_proto::MessageInfo message = makeImageMessageInfo(10, reqObj.chatSessionId(), headPortraitByte);
    respObj.msgList().push_back(message);
    // 构造文件消息
    message = makeFileMessageInfo(11, reqObj.chatSessionId(), headPortraitByte);
    respObj.msgList().push_back(message);
    // 构造语音消息
    message = makeVoiceMessageInfo(12, reqObj.chatSessionId(), headPortraitByte);
    respObj.msgList().push_back(message);

    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::searchHistoryByTime(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: search history by time";
    // 解析请求
    my_chat_proto::MsgSearchByTimeReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::MsgSearchByTimeRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    QByteArray headPortraitByte = readFileToByteArray(":/resource/image/headPortrait.png");
    for (int i = 0; i < 10; ++i) {
        my_chat_proto::MessageInfo message = makeTextMessageInfo(i,
        reqObj.chatSessionId(), headPortraitByte);
        respObj.msgList().push_back(message);
    }
    QByteArray body = respObj.serialize(&_serializer);

    // 发送响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::userNameLogin(const QHttpServerRequest& httpReq) {
    LOG() << "get a http request: user name login";
    // 解析请求
    my_chat_proto::UserLoginReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::UserLoginRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setLoginSessionId("testLoginSessionId");
    QByteArray body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::userNameSignUp(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: user name sign up";
    // 解析请求
    my_chat_proto::UserRegisterReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::UserRegisterRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QString body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::phoneLogin(const QHttpServerRequest &httpReq)
{
    LOG() << "get a http request: phone login";
    // 解析请求
    my_chat_proto::PhoneLoginReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应
    my_chat_proto::PhoneLoginRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setLoginSessionId("testLoginSessionId");
    QByteArray body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::phoneSignUp(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: phone sign up";
    // 解析请求
    my_chat_proto::PhoneRegisterReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::PhoneRegisterRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    QByteArray body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::getSingleFile(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: get single file";
    // 解析请求
    my_chat_proto::GetSingleFileReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::GetSingleFileRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");

    my_chat_proto::FileDownloadData fileDownloadData;
    fileDownloadData.setFileId(reqObj.fileId());
    // 此处后续要能够支持三个情况, 图片文件, 普通文件, 语音文件.
    // 直接使用 fileId 做区分
    if (reqObj.fileId() == "testImage") {
        // fileDownloadData.setFileContent(readFileToByteArray(":/resource/image/logo.png"));
        fileDownloadData.setFileContent(readFileToByteArray(":/resource/image/headPortrait.png"));
    }
    else if (reqObj.fileId() == "testFile") {
        fileDownloadData.setFileContent(readFileToByteArray(":/resource/file/test.txt"));
    }
    else if (reqObj.fileId() == "testVoice") {
        // 由于此处暂时还没有音频文件. 得后面写了 录音功能 才能生成.
        fileDownloadData.setFileContent(readFileToByteArray(":/resource/file/tmpRecord.pcm"));
    }
    else {
        respObj.setSuccess(false);
        respObj.setErrmsg("fileId 不是预期的测试 fileId");
    }
    respObj.setFileData(fileDownloadData);

    QByteArray body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-Type", "application/x-protobuf");
    return httpResp;
}

QHttpServerResponse HttpServer::recognition(const QHttpServerRequest& httpReq)
{
    LOG() << "get a http request: recognition voice";
    // 解析请求 body
    my_chat_proto::VoiceRecognitionReq reqObj;
    reqObj.deserialize(&_serializer, httpReq.body());

    // 构造响应 body
    my_chat_proto::VoiceRecognitionRsp respObj;
    respObj.setRequestId(reqObj.requestId());
    respObj.setSuccess(true);
    respObj.setErrmsg("");
    respObj.setRecognitionResult("你好你好, 这是一段语音消息, 你好你好, 这是一段语音消息");
    QByteArray body = respObj.serialize(&_serializer);

    // 构造 HTTP 响应
    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-type", "application/x-protobuf");
    return httpResp;
}
