#include "netclient.h"

#include "../model/data.h"
#include "../model/datacenter.h"

#include <QNetworkReply>
#include <QUuid>

namespace network{

NetClient::NetClient(model::DataCenter* dataCenter)
    :_dataCenter(dataCenter)
{
    initWebsocket();

}

void NetClient::ping(){
    // 构建请求
    QNetworkRequest httpReq;
    httpReq.setUrl(QUrl(HTTP_URL + "/ping"));

    // 发起请求，接收响应
    // 异步的请求，只是发出请求，响应由信号槽进行处理
    QNetworkReply* httpResp = _httpClient.get(httpReq);

    // 由于不可靠的网络，这个响应不直到啥时候能回来，所以设置信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        if(httpResp->error() != QNetworkReply::NoError){
            // 出错了
            LOG() << "HTTP ping error: " << httpResp->errorString();
            httpResp->deleteLater();
            return;
        }
        // ping成功
        LOG() << "HTTP ping success，response message: " << httpResp->readAll();
        httpResp->deleteLater();
    });
}


// 初始化 websocket
void NetClient::initWebsocket(){
    // 先关联5个信号槽
    connect(&_websocketClient, &QWebSocket::connected, this, [=]() {
        LOG() << "websocket client: websocket connected";
        // websocket连接成功后发送验证信息
        webSocketSendAuthentication();
    });

    connect(&_websocketClient, &QWebSocket::disconnected, this, [=]() {
        LOG() << "websocket client: websocket disconnected";
    });

    connect(&_websocketClient, &QWebSocket::errorOccurred, this, [=](QAbstractSocket::SocketError error) {
        LOG() << "websocket client: websocket error" << error;
    });

    connect(&_websocketClient, &QWebSocket::textMessageReceived, this, [=](const QString& message) {
        LOG() << "websocket client: websocket receive a text message: " << message;
    });

    connect(&_websocketClient, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray& byteArray) {
        LOG() << "websocket client: websocket receive a binary message, length: " << byteArray.length();
    });

    // 建立连接
    _websocketClient.open(QUrl(WEBSOCKET_URL));

}

void NetClient::webSocketSendAuthentication(){
    // websocket 连接成功后客户端需要给服务器发送身份验证信息
    // 验证信息的请求和响应在 gateway.proto 文件中定义好了
    my_chat_proto::ClientAuthenticationReq clientAuthReq;

    // 标识请求id，给每个请求都生成唯一id，方便打印日志进行区分
    clientAuthReq.setRequestId(makeRequestId());
    // 标识登录会话id
    clientAuthReq.setSessionId(_dataCenter->getLoginSessionId());

    // 进行序列化，方便网络传输
    QByteArray body = clientAuthReq.serialize(&_serializer);
    _websocketClient.sendBinaryMessage(body);
    LOG() << "websocket 身份认证，requestId: " << clientAuthReq.requestId() << " , loginSessonId: " << clientAuthReq.sessionId();
}

QString NetClient::makeRequestId(){
    // 直接使用uuid
    return "Request" + QUuid::createUuid().toString().sliced(25, 12);
}


// 把发送 HTTP 请求的操作单独封装成一个函数
QNetworkReply* NetClient::sendHttpRequest(const QString &httpRequestPath, const QByteArray &httpBody){
    // 构建网络请求
    QNetworkRequest httpReq;
    httpReq.setUrl(QUrl(HTTP_URL + httpRequestPath));
    httpReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-protobuf");
    // 异步的请求，只是发出请求，响应由信号槽进行处理
    return _httpClient.post(httpReq, httpBody);
}

// 获取当前用户自身信息
void NetClient::getMyself(const QString &loginSessionId){
    // 构造请求body
    my_chat_proto::GetUserInfoReq reqObj;
    reqObj.setRequestId(makeRequestId());
    reqObj.setSessionId(loginSessionId);
    QByteArray body = reqObj.serialize(&_serializer);

    // 异步的请求，只是发出请求，响应由信号槽进行处理
    QNetworkReply* httpResp = sendHttpRequest("/service/user/get_user_info", body);
    LOG() << "getMyself: send request, requestId: " << reqObj.requestId();

    // 关联网络请求返回时的信号槽
    connect(httpResp, &QNetworkReply::finished, this, [=]() {
        // 处理响应
        bool ok = false;
        QString errmsg;
        std::shared_ptr<my_chat_proto::GetUserInfoRsp> respObj = handleHttpResponse<my_chat_proto::GetUserInfoRsp>(httpResp, &ok, &errmsg);

        if(!ok){
            LOG() << "getMyself error, requestId: "  << respObj->requestId() << "error message: " << errmsg;
            return;
        }

        // 保存数据
        _dataCenter->setMyself(respObj);

        // 最后要通知调用逻辑，HTTP 响应已经处理完成 --》通过自定义信号槽通知
        emit _dataCenter->getMyselfDone();
        LOG() << "getMyself: handle response succeed, requestId: " << respObj->requestId();
    });
}


}  // end namespace
