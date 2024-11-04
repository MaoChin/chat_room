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

    //////////////////////////
    /// \brief Websocket 相关
    ///
    // 初始化websocket
    void initWebsocket();

    // websocket 连接成功后客户端需要给服务器发送身份验证信息
    void webSocketSendAuthentication();

    // 收到二进制websocket信息的总的处理
    void handleWebsocketResp(const my_chat_proto::NotifyMessage& notifyMessage);
    // 收到新消息的处理
    void handleWebsocketNewMessage(const model::MessageInfo& messageInfo);
    void receiveMessage(const QString& chatSessionId);
    // 删除好友时的推送
    void handleWebsocketDeleteFriend(const QString& friendId);
    // 获取添加好友申请的推送
    void handleWebsocketAddFriendApply(const model::UserInfo& friendInfo);
    // 好友申请处理结果的推送
    void handleWebsocketAddFriendProcess(const model::UserInfo& friendInfo, bool agree);
    // 创建聊天会话的推送（单聊/群聊）
    void handleWebsocketCreateChatSession(const model::ChatSessionInfo& chatSessionInfo);



    //////////////////////////
    /// \brief HTTP 相关
    ///
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

    // 获取当前用户会话列表
    void getChatSessionList(const QString& loginSessionId);

    // 获取当前用户好友申请列表
    void getApplyUserList(const QString& loginSessionId);

    // 获取指定会话的最近消息列表
    void getChatSessionRecentMessage(const QString& loginSessionId, const QString& chatSessionId, bool updateUI);

    // 给指定会话发送文本消息
    void sendMessage(const QString& loginSessionId, const QString& chatSessionId, model::MessageType meseageType,
                     const QByteArray& content, const QString& extraInfo);

    // 修改用户的用户名
    void modifyNickName(const QString& loginSessionId, const QString& newNickName);
    // 修改用户的个性签
    void modifyPersonalSignature(const QString& loginSessionId, const QString& newPersonalSignature);
    // 获取手机验证码
    void getPhoneVerifyCode(const QString& phoneNum);
    // 修改用户的手机号
    void modifyPhoneNum(const QString& loginSessionId, const QString& newPhoneNum,
                        const QString& verifyCodeId, const QString& verifyCode);
    // 修改用户头像
    void modifyHeadPortrait(const QString& loginSessionId, const QByteArray& newHeadPortraitBytes);

    // 添加好友申请
    void addFriendApply(const QString& loginSessionId, const QString& friendId);
    // 接受好友申请
    void acceptAddFriendApply(const QString& loginSessionId, const QString& friendId);
    // 拒绝好友申请
    void refuseAddFriendApply(const QString& loginSessionId, const QString& friendId);

    // 删除好友
    void deleteFriend(const QString& loginSessionId, const QString& friendId);

    // 创建群聊
    void createGroupChatSession(const QString& loginSessionId, const QList<QString>& groupSessionIdList);

    // 获取群聊会话成员列表
    void getChatSessionMemberList(const QString& loginSessionId, const QString& chatSessionId);

    // 搜索用户
    void searchUser(const QString& loginSessionId, const QString& searchKey);

    // 通过关键字搜索历史消息
    void searchHistoryMessageBySearchKey(const QString& loginSessionId, const QString& chatSessionId,
                                         const QString& searchKey);

    // 通过时间区间搜索历史消息
    void searchHistoryMessageByTime(const QString& loginSessionId, const QString& chatSessionId,
                                         const QDateTime& startTime, const QDateTime& endTime);

    // 用户名注册
    void userNameSignUp(const QString& userName, const QString& password);
    // 用户名登录
    void userNameLogin(const QString& userName, const QString& password);
    // 手机号注册
    void phoneSignUp(const QString& phoneNum, const QString& verifyCodeId, const QString& verifyCode);
    // 手机号登录
    void phoneLogin(const QString& phoneNum, const QString& verifyCodeId, const QString& verifyCode);

    // 根据fileId获取文件内容
    void getSingleFileContent(const QString& loginSessionId, const QString& fileId);

    // 语音转文字
    void voiceConvertText(const QString& loginSessionId, const QString& fileId, const QByteArray& content);

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
