#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QHttpServer>
#include <QProtobufSerializer>


// 模拟的HTTP服务器
class HttpServer : public QObject
{
    Q_OBJECT
public:
    // 单例
    static HttpServer* getInstance();

    // 初始化
    bool initHttpServer();

    // 获取用户信息
    QHttpServerResponse getUserInfo(const QHttpServerRequest& httpReq);

private:
    HttpServer();


private:
    // 单例
    static HttpServer* _instance;

    // Http 服务器
    QHttpServer _httpServer;
    // protobuf 模块
    QProtobufSerializer _serializer;



signals:
};

#endif // HTTPSERVER_H
