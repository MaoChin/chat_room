#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QWebSocket>
#include <QProtobufSerializer>
#include <QNetworkReply>

#include "../model/data.h"


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

    // 把发送 HTTP 请求的操作单独封装成一个函数
    QNetworkReply* sendHttpRequest(const QString& httpRequestPath, const QByteArray& httpBody);

    // 把获取到 HTTP 响应后的通用操作封装成一个函数，如判断网络是否出错，获取响应结果，反序列化，判断业务是否出错等
    // 最后返回反序列化后的对象
    // 由于 HTTP 响应很多，所以返回的对象结构各不相同 --》使用模板，泛型编程
    // 为了提高效率，减少拷贝，并且防止内存泄漏，使用智能指针
    template<typename T>
    std::shared_ptr<T> handleHttpResponse(QNetworkReply* httpResp, bool* ok, QString* errmsg){
        // 模板分离编译有问题！！
        // 定义模板的文件中不知道模板的具体类型，就不会实例化出具体的函数！符号表中就没有函数的地址
        // 链接时就会出错！
        // 所以这里要把声明和定义写在一起！

        // 判断网络是否出错
        if(httpResp->error() != QNetworkReply::NoError){
            // 输出型参数
            *ok = false;
            *errmsg = httpResp->errorString();
            httpResp->deleteLater();
            return std::shared_ptr<T>();
        }

        // 获取响应结果
        QByteArray body = httpResp->readAll();
        std::shared_ptr<T> respObj = std::make_shared<T>();

        // 反序列化
        respObj->deserialize(&_serializer, body);

        // 判断业务是否出错
        if(!respObj->success()){
            *ok = false;
            *errmsg = respObj->errmsg();
            httpResp->deleteLater();
            return std::shared_ptr<T>();
        }

        *ok = true;
        httpResp->deleteLater();
        return respObj;
    }

    // 获取当前用户自身信息
    void getMyself(const QString& loginSessionId);

    // 获取当前用户好友列表
    void getFriendUserList(const QString& logSessionId);


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
