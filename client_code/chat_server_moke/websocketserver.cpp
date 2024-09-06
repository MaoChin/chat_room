#include "websocketserver.h"

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
        });

        connect(socket, &QWebSocket::errorOccurred, this, [=](QAbstractSocket::SocketError error) {
            qDebug() << "websocket server: error " << error;
        });

        connect(socket, &QWebSocket::textMessageReceived, this, [=](const QString& message) {
            qDebug() << "websocket server: receive text message: " << message;
        });

        connect(socket, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray& byteArray) {
            qDebug() << "websocket server: receive binary message, length: " << byteArray.length();
        });
    });

    // 绑定端口，启动服务
    bool ok = _websocketServer.listen(QHostAddress::Any, 8081);
    return ok;
}



