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

    // 对于未读消息的操作
    void clearUnreadMessage(const QString& chatSessionId){
        (*_chatSessionToUnreadMessageNum)[chatSessionId] = 0;
        // 将结果保存到本地
        writeToDataFile();
    }
    void addUnreadNum(const QString& chatSessionId){
        (*_chatSessionToUnreadMessageNum)[chatSessionId]++;
        // 将结果保存到本地
        writeToDataFile();
    }
    int getUnreadNum(const QString& chatSessionId){
        return (*_chatSessionToUnreadMessageNum)[chatSessionId];
    }

    const QString& getLoginSessionId(){
        return _loginSessionId;
    }

    void ping(){
        _netClient.ping();
    }

    // 初始化websocket
    void initWebsocket(){
        _netClient.initWebsocket();
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

    // 直接获取好友列表信息
    QList<UserInfo>* getFriendUserList(){
        return _friendUserList;
    }
    // 根据friend查找用户的好友
    UserInfo* findFriendById(const QString& friendId){
        if(_friendUserList == nullptr){
            return nullptr;
        }
        for(auto& friendInfo : (*_friendUserList)){
            if(friendInfo._userId == friendId){
                return &friendInfo;
            }
        }
        return nullptr;
    }
    // 根据friendId删除好友
    void deleteFriendById(const QString& friendId);

    // 根据friendId删除好友申请列表中的好友，并返回该好友信息
    UserInfo deleteFromApplyUserList(const QString& friendId);


    // 获取当前用户选中的会话id
    const QString& getCurChatSessionId(){
        return _currentChatSessionId;
    }
    // 设置当前用户选中的会话id
    void setCurChatSessionId(const QString& chatSessionId){
        this->_currentChatSessionId = chatSessionId;
    }

    // 通过chatSessionId获取chatSession信息
    ChatSessionInfo* getChatSessionInfo(const QString& chatSessionId);

    // 通过userId获取chatSession信息
    ChatSessionInfo* getChatSessionInfoByUserId(const QString& userId);

    // 将指定的会话置顶
    void topChatSession(const ChatSessionInfo& chatSessionInfo);

    // 向会话中添加消息
    void addChatSessionMessage(const MessageInfo& messageInfo);


    // 通过网络获取当前用户好友列表信息
    // asynchronous：异步的，由于网络I/O非常慢而且不可靠，所以网络请求一般都设置成异步的
    // 通过信号槽机制处理请求完成时的事务
    void getFriendUserListAsync();
    // 设置当前用户好友列表信息
    void setFriendUserList(std::shared_ptr<my_chat_proto::GetFriendListRsp> respObj);


    // 通过网络获取当前用户会话列表信息
    // asynchronous：异步的，由于网络I/O非常慢而且不可靠，所以网络请求一般都设置成异步的
    // 通过信号槽机制处理请求完成时的事务
    void getChatSessionListAsync();
    // 设置当前用户好友列表信息
    void setChatSessionList(std::shared_ptr<my_chat_proto::GetChatSessionListRsp> respObj);

    // 直接获取会话列表信息
    QList<ChatSessionInfo>* getChatSessionList(){
        return _chatSessionList;
    }

    // 通过网络获取当前用户好友申请列表信息
    void getApplyUserListAsync();
    // 设置当前用户好友申请列表信息
    void setApplyUserList(std::shared_ptr<my_chat_proto::GetPendingFriendEventListRsp> respObj);
    // 直接获取好友申请列表信息
    QList<UserInfo>* getApplyUserList(){
        return _applyUserList;
    }

    // 通过网络获取会话最近消息列表
    void getChatSessionRecentMessageAsync(const QString& chatSessionId, bool updateUI);
    // 设置当前会话最近消息列表
    void setChatSessionRecentMessage(const QString& chatSessionId, std::shared_ptr<my_chat_proto::GetRecentMsgRsp> respObj);
    // 直接获取会话最近消息列表
    QList<MessageInfo>* getChatSessionRecentMessage(const QString& chatSessionId){
        if(_chatSessionToPrevMessage->contains(chatSessionId)){
            return &(*_chatSessionToPrevMessage)[chatSessionId];
        }
        return nullptr;
    }

    // 通过网络发送文本消息
    void sendTextMessageAsync(const QString& chatSessionId, const QString& content);
    // 通过网络发送图片消息
    void sendImageMessageAsync(const QString& chatSessionId, const QByteArray& content);
    // 通过网络发送文件消息
    void sendFileMessageAsync(const QString& chatSessionId, const QString& fileName, const QByteArray& content);
    // 通过网络发送语音消息
    void sendVoiceMessageAsync(const QString& chatSessionId, const QByteArray& content);

    // 通过网络修改用户的用户名
    void modifyNickNameAsync(const QString& newNickName);
    // 直接修改用户的用户名
    void modifyNickName(const QString& newNickName){
        if(_myself != nullptr){
            _myself->_nickName = newNickName;
        }
    }

    // 通过网络修改用户的个性签名
    void modifyPersonalSignatureAsync(const QString& newPersonalSignature);
    // 直接修改用户的个性签名
    void modifyPersonalSignature(const QString& newPersonalSignature){
        if(_myself != nullptr){
            _myself->_nickName = newPersonalSignature;
        }
    }

    // 通过网络获取手机验证码
    void getPhoneVerifyCodeAsync(const QString& phoneNum);
    // 直接修改手机号验证码ID
    void setPhoneVerifyCodeId(const QString& verifyCodeId){
        _phoneVerifyCodeId = verifyCodeId;
    }
    // 直接获取手机号验证码ID
    QString getPhoneVerifyCodeId(){
        return _phoneVerifyCodeId;
    }

    // 通过网络修改用户的手机号
    void modifyPhoneNumAsync(const QString& newPhoneNum, const QString& verifyCodeId,
                             const QString& verifyCode);
    // 直接修改用户的手机号
    void modifyPhoneNum(const QString& newPhoneNum){
        if(_myself != nullptr){
            _myself->_phoneNum = newPhoneNum;
        }
    }

    // 通过网络修改用户头像
    void modifyHeadPortraitAsync(const QByteArray& newHeadPortraitBytes);
    // 直接修改用户的头像
    void modifyHeadPortrait(const QByteArray& newHeadPortraitBytes){
        if(_myself != nullptr){
            _myself->_headPortrait = makeQIcon(newHeadPortraitBytes);
        }
    }

    // 添加好友申请 的网络请求
    void addFriendApplyAsync(const QString& friendId);

    // 删除好友的网络请求
    void deleteFriendAsync(const QString& friendId);

    // 接受好友申请的网络请求
    void acceptAddFriendApplyAsync(const QString& friendId);
    // 拒绝好友申请的网络请求
    void refuseAddFriendApplyAsync(const QString& friendId);

    // 群聊相关
    // 创建群聊的网络请求
    void createGroupChatSessionAsync(const QList<QString>& groupSessionIdList);
    // 通过网络获取群聊成员列表
    void getChatSessionMemberListAsync(const QString& chatSessionId);
    // 直接设置群聊成员列表
    void setChatSessionMemberList(const QString& chatSessionId, const QList<my_chat_proto::UserInfo>& memberListPb);
    // 直接获取特定会话的成员列表
    QList<UserInfo>* getChatSessionMemberList(const QString& chatSessionId){
        return &(*_chatSessionToMemberList)[chatSessionId];
    }

    // 搜索相关
    // 搜索用户
    void searchUserAsync(const QString& searchKey);
    // 设置用户搜索列表
    void setSearchUserList(const QList<my_chat_proto::UserInfo>& searchUserListPb);
    // 直接获取用户搜索列表
    QList<UserInfo>* getSearchUserList(){
        return _searchUserList;
    }

    // 按关键字搜索历史消息
    void searchHistoryMessageBySearchKeyAsync(const QString& searchKey);
    // 设置历史消息搜索列表
    void setSearchHistoryMessageList(const QList<my_chat_proto::MessageInfo>& searchHistoryMessageListPb);
    // 直接获取历史消息搜索列表
    QList<MessageInfo>* getSearchHistoryMessageList(){
        return _searchHistoryMessageList;
    }

    // 按时间搜索历史消息
    void searchHistoryMessageByTimeAsync(const QDateTime& beginTime, const QDateTime& endTime);


    // 登录注册相关
    // 用户名注册
    void userNameSignUpAsync(const QString& userName, const QString& password);
    // 用户名登录
    void userNameLoginAsync(const QString& userName, const QString& password);
    // 手机号注册
    void phoneSignUpAsync(const QString& phoneNum, const QString& verifyCode);
    // 手机号登录
    void phoneLoginAsync(const QString& phoneNum, const QString& verifyCode);

    // 设置 loginSessionId
    void setLoginSessionId(const QString& loginSessionId){
        _loginSessionId = loginSessionId;
        // 对于 loginSessionId 需要保存到磁盘
        writeToDataFile();
    }

    // 根据 fileId 获取单个文件内容
    void getSingleFileContentAsync(const QString& fileId);

    // 语音转文字
    void voiceConvertTextAsync(const QString& fileId, const QByteArray& content);


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

    // 搜索好友时搜索结果（我想给别人发送好友申请）
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
    QString _phoneVerifyCodeId = "";

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

    // 5. getChatSessionRecentMessageAsync() 请求完成信号
    void getChatSessionRecentMessageAsyncDone(const QString& chatSessionId);
    // 6. getChatSessionRecentMessageAsync() 请求完成信号---不更新右侧消息显示界面
    void getChatSessionRecentMessageAsyncNoUIDone(const QString& chatSessionId);

    // 7. sendTextMessageAsync() sendFileMessageAsync() sendImageMessageAsync() sendVoiceMessageAsync() 请求完成信号
    void sendMessageAsyncDone(model::MessageType messageType, const QByteArray& content, const QString& extraInfo);

    // 8. 中间会话界面更新对应会话的最后一条消息(在发送消息时触发)---websocket
    void updateLastMessage(const QString& chatSessionId);

    // 9. 网络模块处理收到新消息结束---websocket
    void netClientReceiveMessageDone(const MessageInfo& newMessage);

    // 10. modifyNickNameAsync() 请求处理完成信号
    void modifyNickNameAsyncDone();

    // 11. modifyPersonalSignatureAsync() 请求处理完成信号
    void modifyPersonalSignatureAsyncDone();

    // 12. modifyPhoneNumAsync() 请求处理完成信号
    void modifyPhoneNumAsyncDone();

    // 13. getPhoneVerifyCodeAsync() 请求处理完成信号
    void getPhoneVerifyCodeAsyncDone();

    // 14. modifyHeadPortraitAsync() 请求处理完成信号
    void modifyHeadPortraitAsyncDone();

    // 15. 删除好友时需要清空右侧消息显示界面
    void clearCurChatSession();

    // 16. deleteFriendAsync() 请求处理完成信号
    void deleteFriendAsyncDone();

    // 17. addFriendApplyAsync() 请求处理完成信号
    void addFriendApplyAsyncDone();

    // 18. 收到好友申请推送时需要更新界面的信号---websocket
    void receiveAddFriendApplyDone();
    // 19. 收到好友申请处理结果时需要更新界面的信号---websocket
    void receiveAddFriendProcessDone(bool agree, const QString& friendNickname);

    // 20. acceptAddFriendApplyAsync() 请求处理完成信号
    void acceptAddFriendApplyAsyncDone(const QString& userNickname);

    // 21. refuseAddFriendApplyAsync() 请求处理完成信号
    void refuseAddFriendApplyAsyncDone(const QString& userNickname);

    // 22. createGroupChatSessionAsync() 请求处理完成信号
    void createGroupChatSessionAsyncDone();

    // 23. 收到创建会话时更新界面的信号---websocket
    void receiveCreateChatSessionDone();

    // 24. getChatSessionMemberListAsync() 请求处理完成信号
    void getChatSessionMemberListAsyncDone();

    // 25. searchUserAsync() 请求处理完成信号
    void searchUserAsyncDone();

    // 26. searchHistoryMessageBySearchKeyAsync() 请求处理完成信号
    void searchHistoryMessageAsyncDone();

    // 27. userNameSignUpAsync() 请求处理完成信号
    void userNameSignUpAsyncDone(bool ok, const QString& errmsg);

    // 28. userNameLoginAsync() 请求处理完成信号
    void userNameLoginAsyncDone(bool ok, const QString& errmsg);

    // 29. phoneSignUpAsync() 请求处理完成信号
    void phoneSignUpAsyncDone(bool ok, const QString& errmsg);

    // 30. phoneLoginAsync() 请求处理完成信号
    void phoneLoginAsyncDone(bool ok, const QString& errmsg);

    // 31. getSingleFileContentAsync() 请求处理完成信号
    void getSingleFileContentAsyncDone(const QString& fileId, const QByteArray& fileContent);

    // 33. voiceConvertTextAsync() 请求处理完成信号
    void voiceConvertTextAsyncDone(const QString &fileId, const QString &text);

};

}  // end namespace

#endif // DATACENTER_H
