#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>

#include "data.h"
#include "../network/netclient.h"

// 数据中心类，用于管理所有的数据
namespace model {


// 继承QObject是为了使用信号槽
class DataCenter : public QObject
{
    Q_OBJECT
public:
    // 设置成单例
    static DataCenter* getInstance();

    // 析构
    ~DataCenter();

    // 对于一些数据做持久化处理（保存到本地文件中）
    // 初始化本地文件
    void initDataFile();
    // 写数据到本地文件
    void writeToDataFile();
    // 从文件中读取数据到内存中
    void readFromDataFile();

    const QString& getLoginSessionId(){
        return _loginSessionId;
    }

    void ping(){
        _netClient.ping();
    }

    // 通过网络获取当前用户个人信息
    // asynchronous：异步的，由于网络I/O非常慢而且不可靠，所以网络请求一般都设置成异步的
    // 通过信号槽机制处理请求完成时的事务
    void getMyselfAsync();
    // 设置个人用户信息
    void setMyself(std::shared_ptr<my_chat_proto::GetUserInfoRsp> respObj);

    // 直接获取个人信息
    UserInfo* getMyself() {
        return _myself;
    }

    // 通过网络获取当前用户好友列表信息
    // asynchronous：异步的，由于网络I/O非常慢而且不可靠，所以网络请求一般都设置成异步的
    // 通过信号槽机制处理请求完成时的事务
    void getFriendUserListAsync();
    // 设置当前用户好友列表信息
    void setFriendUserList(std::shared_ptr<my_chat_proto::GetFriendListRsp> respObj);

    // 直接获取好友列表信息
    QList<UserInfo>* getFriendUserList(){
        return _friendUserList;
    }

    // 通过网络获取当前用户会话列表信息
    // asynchronous：异步的，由于网络I/O非常慢而且不可靠，所以网络请求一般都设置成异步的
    // 通过信号槽机制处理请求完成时的事务
    void getChatSessionListAsync();
    // 设置当前用户好友列表信息
    void setChatSessionList(std::shared_ptr<my_chat_proto::GetFriendListRsp> respObj);

    // 直接获取会话列表信息
    QList<ChatSessionInfo>* getChatSessionList(){
        return _chatSessionList;
    }


private:
    // 构造函数私有
    DataCenter();

private:
    // 单例
    static DataCenter* _instance;

    // 数据
    // 登录会话ID，这个和 聊天会话ID 是两套ID
    QString _loginSessionId = "";

    // 当前用户信息，使用指针可以更方便的标识 “无效值” -- nullptr
    UserInfo* _myself = nullptr;

    // 当前用户好友信息,使用指针可以更方便的标识 “无效值” -- nullptr
    QList<UserInfo>* _friendUserList = nullptr;

    // 当前用户的好友申请列表（别人给我发送的好友申请）
    QList<UserInfo>* _applyUserList = nullptr;

    // 搜索添加好友时搜索结果（我想给别人发送好友申请）
    QList<UserInfo>* _searchUserList = nullptr;

    // 搜索历史消息时搜索结果
    QList<MessageInfo>* _searchHistoryMessageList = nullptr;

    // 当前用户会话列表，会话和好友是分开的，比如群聊会话就和好友没啥关系！！
    QList<ChatSessionInfo>* _chatSessionList = nullptr;

    // 当前用户选中的会话
    QString _currentChatSessionId = "";

    // 针对群聊会话，会话中的所有用户信息。对于单聊会话成员只有自己和 ChatSessionInfo 中的 _userId
    // chatSessionId <-> 用户信息列表
    QHash<QString, QList<UserInfo>>* _chatSessionToMemberList = nullptr;

    // 会话中的最近消息列表，用于在右侧窗口展示
    // chatSessionId <-> 最近消息列表
    QHash<QString, QList<MessageInfo>>* _chatSessionToPrevMessage = nullptr;

    // 每个会话中未读消息的数量
    // chatSession <-> 未读消息数量
    QHash<QString, int>* _chatSessionToUnreadMessageNum = nullptr;

    // 当前用户注册登录时的 短信验证码ID，注意不是验证码本身，而是另一个由服务端随机生成的id
    // 最终是 短信验证码ID + 具体的短信验证码 组合起来共同进行验证！！可以防止冲突，强化验证
    QString phoneVerifyCodeId = "";

    // 网络模块（DataCenter和网络模块强相关）
    network::NetClient _netClient;


    // 一些常量
    // 持久化到文件的文件信息
    const QString PERSISTENCE_DIR_PATH = "./localData";
    const QString PERSISTENCE_FILE_PATH = PERSISTENCE_DIR_PATH + "/chatClient.json";


signals:
    // 自定义信号槽
    // 1. getMyselfAsync() 请求完成信号
    void getMyselfAsyncDone();

    // 2. getFriendUserListAsync() 请求完成信号
    void getFriendUserListAsyncDone();

    // 3. getChatSessionListAsync() 请求完成信号
    void getChatSessionListAsyncDone();

    // 4. getApplyUserListAsync() 请求完成信号
    void getApplyUserListAsyncDone();

};

}  // end namespace

#endif // DATACENTER_H
