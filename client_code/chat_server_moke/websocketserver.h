#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>


// 模拟的Websocket服务器
class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    static WebsocketServer* getInstance();

    // 初始化
    bool initWebsocket();


private:
    // 构造
    explicit WebsocketServer();


private:
    // 单例
    static WebsocketServer* _instance;

    // websocket服务器
    QWebSocketServer _websocketServer;



signals:
};

#endif // WEBSOCKETSERVER_H
