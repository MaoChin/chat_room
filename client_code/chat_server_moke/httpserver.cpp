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

    my_chat_proto::UserInfo userInfo;
    userInfo.setUserId("123");
    userInfo.setNickName("小八");
    userInfo.setPersonSignature("你好");
    userInfo.setPhoneNumber("12345466");
    userInfo.setHeadPortrait(readFileToByteArray(":/resource/image/testPortrait.png"));
    respObj.setUserInfo(userInfo);

    QByteArray body = respObj.serialize(&_serializer);

    QHttpServerResponse httpResp(body, QHttpServerResponse::StatusCode::Ok);
    httpResp.setHeader("Content-type", "application/x-protobuf");

    return httpResp;
}
