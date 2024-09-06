#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QWebSocket>
#include <QProtobufSerializer>

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
    NetClient(model::DataCenter* dataCenter);

    // 测试HTTP协议
    void ping();
    // 初始化websocket
    void initWebsocket();
    // websocket 连接成功后客户端需要给服务器发送身份验证信息
    void webSocketSendAuthentication();

    // 生成 唯一的请求id
    static QString makeRequestId();


private:
    // 数据中心模块（DataCenter和网络模块强相关！）
    model::DataCenter* _dataCenter;

    // HTTP协议的客户端
    QNetworkAccessManager _httpClient;

    // Websockets协议的客户端
    QWebSocket _websocketClient;

    // protobuf 模块
    QProtobufSerializer _serializer;


    // 一些常量
    const QString HTTP_URL = "http://127.0.0.1:8080";
    const QString WEBSOCKET_URL = "ws://127.0.0.1:8081/ws";


signals:
};

}  // end namespace

#endif // NETCLIENT_H
