#include "httpserver.h"


#include <QDebug>


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
    _httpServer.route("/ping", [](const QHttpServerRequest& req) {
        (void)req;
        qDebug() << "httpserver: get a request";
        return "pong";
    });

    // listen 成功就返回绑定的端口 8080
    return ret == 8080;
}

