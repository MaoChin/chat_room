#include "widget.h"

#include "httpserver.h"
#include "websocketserver.h"

#include <QApplication>


// serverMoke 搭建一个模拟的服务端，用于构建假的数据测试客户端程序
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 启动HTTP服务器
    HttpServer* httpserver = HttpServer::getInstance();
    if(httpserver->initHttpServer()){
        qDebug() << "HTTP服务器启动成功";
    }
    else{
        qDebug() << "HTTP服务器启动失败";
    }

    // 启动websocket服务器
    WebsocketServer* websocketServer = WebsocketServer::getInstance();
    if(websocketServer->initWebsocket()){
        qDebug() << "websocket 服务器启动成功";
    }
    else{
        qDebug() << "websocket 服务器启动失败";
    }

    Widget w;
    w.show();
    return a.exec();
}
