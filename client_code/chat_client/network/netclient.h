#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QWebSocket>


// 这里包含的话会造成 循环包含头文件！！--》死锁
// #include "../model/datacenter.h"

// 使用前置声明解决 循环包含头文件问题
namespace model{
    class DataCenter;
}  // end namespace

namespace network{

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient(model::DataCenter* dataCenter = nullptr);

    // 测试网络
    void ping();

private:
    // 数据中心模块（DataCenter和网络模块强相关！）
    model::DataCenter* _dataCenter;

    // HTTP协议的客户端
    QNetworkAccessManager _httpClient;

    // Websockets协议的客户端
    QWebSocket _websocketClient;


    // 一些常量
    const QString HTTP_URL = "http://127.0.0.1:8080";
    const QString WEBSOCKET_URL = "ws://127.0.0.1:8081/ws";


signals:
};

}  // end namespace

#endif // NETCLIENT_H
