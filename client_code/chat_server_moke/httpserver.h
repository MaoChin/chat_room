#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QHttpServer>
#include <QProtobufSerializer>

class HttpServer : public QObject
{
    Q_OBJECT
public:
    // 单例
    static HttpServer* getInstance();

    // 初始化
    bool init();

private:
    HttpServer();


private:
    // 单例
    static HttpServer* _instance;

    // Http 服务器
    QHttpServer _httpServer;
    QProtobufSerializer _serializer;



signals:
};

#endif // HTTPSERVER_H
