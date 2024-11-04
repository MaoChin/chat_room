#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QProtobufSerializer>


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

    // protobuf模块
    QProtobufSerializer _serializer;

    // 构造的消息下标，递增的
    int _messageIndex = 0;

signals:
    // 推送文本消息
    void sendTextResp();
    // 推送图片消息
    void sendImageResp();
    // 推送文件消息
    void sendFileResp();
    // 推送语音消息
    void sendVoiceResp();
    // 推送好友删除信息
    void sendFriendDelete();
    // 推送好友申请信息
    void sendAddFriendApply();
    // 推送好友申请处理结果
    void sendAddFriendProcess(bool agree);
    // 推送好友申请处理结果
    void sendCreateChatSession();
};

#endif // WEBSOCKETSERVER_H
