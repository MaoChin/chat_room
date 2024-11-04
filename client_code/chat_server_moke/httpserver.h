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

    // 获取当前用户好友信息
    QHttpServerResponse getFriendUserList(const QHttpServerRequest& httpReq);

    // 获取当前用户会话列表信息
    QHttpServerResponse getChatSessionList(const QHttpServerRequest& httpReq);

    // 获取当前用户好友申请列表信息
    QHttpServerResponse getApplyUserList(const QHttpServerRequest& httpReq);

    // 获取指定会话的最近历史消息
    QHttpServerResponse getChatSessionRecentMessage(const QHttpServerRequest& httpReq);

    // 发送消息
    QHttpServerResponse sendMessage(const QHttpServerRequest& httpReq);

    // 修改用户名
    QHttpServerResponse setNickName(const QHttpServerRequest& httpReq);

    // 修改用户的个性签名
    QHttpServerResponse setUserSignature(const QHttpServerRequest& httpReq);

    // 获取短信验证码
    QHttpServerResponse getPhoneVerifyCode(const QHttpServerRequest& httpReq);

    // 修改用户手机号
    QHttpServerResponse setPhoneNum(const QHttpServerRequest& httpReq);

    // 修改用户头像
    QHttpServerResponse setHeadPortrait(const QHttpServerRequest& httpReq);

    // 删除好友
    QHttpServerResponse deleteFriend(const QHttpServerRequest& httpReq);

    // 添加好友申请
    QHttpServerResponse addFriendApply(const QHttpServerRequest& httpReq);

    // 对好友申请的处理
    QHttpServerResponse addFriendProcess(const QHttpServerRequest& httpReq);

    // 创建会话
    QHttpServerResponse createChatSession(const QHttpServerRequest& httpReq);

    // 获取群聊会话成员列表
    QHttpServerResponse getChatSessionMember(const QHttpServerRequest& httpReq);

    // 搜索用户
    QHttpServerResponse searchUser(const QHttpServerRequest& httpReq);

    // 根据关键字搜索历史消息
    QHttpServerResponse searchHistoryBySearchKey(const QHttpServerRequest& httpReq);

    // 根据时间搜索历史消息
    QHttpServerResponse searchHistoryByTime(const QHttpServerRequest& httpReq);

    // 用户名登录
    QHttpServerResponse userNameLogin(const QHttpServerRequest& httpReq);

    // 用户名注册
    QHttpServerResponse userNameSignUp(const QHttpServerRequest& httpReq);

    // 手机号登录
    QHttpServerResponse phoneLogin(const QHttpServerRequest& httpReq);

    // 手机号注册
    QHttpServerResponse phoneSignUp(const QHttpServerRequest& httpReq);

    // 获取单个文件
    QHttpServerResponse getSingleFile(const QHttpServerRequest& httpReq);

    // 语音识别
    QHttpServerResponse recognition(const QHttpServerRequest& httpReq);

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
