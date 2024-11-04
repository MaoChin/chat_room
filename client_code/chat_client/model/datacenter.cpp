#include "datacenter.h"

#include <QStandardPaths>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


// 数据中心类，用于管理所有的数据
namespace model {

// 单例
DataCenter* DataCenter::_instance = nullptr;
DataCenter* DataCenter::getInstance(){
    if(_instance == nullptr){
        _instance = new DataCenter();
    }
    return _instance;
}

DataCenter::DataCenter()
    :_netClient(this)
{
    // 进行一些初始化
    // 其他的指针可以通过 nullptr 判断数据是否有效，所以先不 new 出来，等到从服务端获取到数据再说
    // 而 hash 类型直接通过key的有无就可以判断数据是否有效了
    _chatSessionToMemberList = new QHash<QString, QList<UserInfo>>();
    _chatSessionToPrevMessage = new QHash<QString, QList<MessageInfo>>();
    _chatSessionToUnreadMessageNum = new QHash<QString, int>();

    // 加载本地文件中持久化的数据
    readFromDataFile();
}

DataCenter::~DataCenter(){
    // delete 掉所有的数据
    // 注意：对于 nullptr 是可以直接 delete 的！！
    delete _myself;
    delete _friendUserList;
    delete _applyUserList;
    delete _searchUserList;
    delete _searchHistoryMessageList;
    delete _chatSessionList;
    delete _chatSessionToMemberList;
    delete _chatSessionToPrevMessage;
    delete _chatSessionToUnreadMessageNum;
}

void DataCenter::initDataFile(){
    // 选定文件目录：1.使用相对路径 2.使用系统路径
    // 1.相对路径
    // QString filePath = "./localData/chatClient.json";
    // 2.系统路径，通过下述API可以获取到操作系统的 AppData 路径！
    // QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/chatClient.json";
    // LOG() << filePath;

    // 先创建目录
    QDir dir;
    if(!dir.exists(PERSISTENCE_DIR_PATH)){
        dir.mkpath(PERSISTENCE_DIR_PATH);
    }

    // 文件操作
    QFile file(PERSISTENCE_FILE_PATH);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        LOG() << "打开文件失败: " << file.errorString();
        return;
    }
    file.write("{\n\n}");
    file.close();
}

void DataCenter::writeToDataFile(){
    // 对于一些数据可以保存到本地文件中进行持久化存储
    // 比如：1.logSessionId，后续可以实现跳过登录  2.未读消息次数，后续可以直接从本地文件加载
    QFile file(PERSISTENCE_FILE_PATH);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        LOG() << "打开文件失败：" << file.errorString();
        return;
    }

    // 构造 json 格式数据
    QJsonObject jsonObject;
    jsonObject["logSessionId"] = _loginSessionId;
    QJsonObject jsonUnreadMessageNum;
    for(auto elem = _chatSessionToUnreadMessageNum->begin(); elem != _chatSessionToUnreadMessageNum->end(); ++elem){
        jsonUnreadMessageNum[elem.key()] = elem.value();
    }
    jsonObject["unreadMessageNum"] = jsonUnreadMessageNum;

    // 借助 QJsonDocument 把json对象转成字符串
    QJsonDocument jsonDocument(jsonObject);
    QString data = jsonDocument.toJson();
    file.write(data.toUtf8());
    file.close();
}

void DataCenter::readFromDataFile(){
    // 从文件中读取持久化的数据
    // 判断文件是否存在
    QFileInfo fileInfo(PERSISTENCE_FILE_PATH);
    if(!fileInfo.exists()){
        initDataFile();
        return;
    }

    QFile file(PERSISTENCE_FILE_PATH);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG() << "打开文件失败" << file.errorString();
        return;
    }

    // 把读取的字符串转成 jsonDocument，再转成 jsonObject
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
    if(jsonDocument.isNull()){
        LOG() << "json文件解析失败";
        return;
    }

    QJsonObject jsonObject = jsonDocument.object();
    this->_loginSessionId = jsonObject["logSessionId"].toString();

    QJsonObject jsonUnreadMessageNum = jsonObject["unreadMessageNum"].toObject();
    for(auto elem = jsonUnreadMessageNum.begin(); elem != jsonUnreadMessageNum.end(); ++elem){
        this->_chatSessionToUnreadMessageNum->insert(elem.key(), elem.value().toInt());
    }
}

void DataCenter::getMyselfAsync(){
    // 数据中心类只负责数据相关，网络部分还是交给netClinet
    _netClient.getMyself(_loginSessionId);
}

void DataCenter::setMyself(std::shared_ptr<my_chat_proto::GetUserInfoRsp> respObj){
    if(_myself == nullptr){
        _myself = new model::UserInfo();
    }
    _myself->load(respObj->userInfo());
}

void DataCenter::deleteFriendById(const QString &friendId){
    // 删除好友时也要把对应的会话给删了（单聊会话）
    if(_friendUserList == nullptr || _chatSessionList == nullptr){
        return;
    }

    // 使用这个删除接口！参数是 lambda表达式
    _friendUserList->removeIf([=](const UserInfo& userInfo) {
        // true表示删除！
        return userInfo._userId == friendId;
    });

    // 删除单聊会话
    _chatSessionList->removeIf([=](const ChatSessionInfo& chatSessionInfo) {
        if(chatSessionInfo._userId == ""){
            // 群聊
            return false;
        }
        if(chatSessionInfo._userId != friendId){
            return false;
        }
        // 如果要删除的会话是当前选中的会话，还要清空右侧显示界面
        if(chatSessionInfo._chatSessionId == this->_currentChatSessionId){
            // 通过信号实现
            emit this->clearCurChatSession();
        }
        return true;
    });
}

UserInfo DataCenter::deleteFromApplyUserList(const QString &friendId){
    if(_applyUserList == nullptr){
        return UserInfo();
    }

    for(auto it = _applyUserList->begin(); it != _applyUserList->end(); ++it){
        if(it->_userId == friendId){
            UserInfo newFriendInfo = *it;
            _applyUserList->erase(it);
            return newFriendInfo;
        }
    }
    return UserInfo();
}

ChatSessionInfo *DataCenter::getChatSessionInfo(const QString &chatSessionId){
    if(_chatSessionList == nullptr){
        return nullptr;
    }
    for(auto& chatSession : *_chatSessionList){
        if(chatSession._chatSessionId == chatSessionId){
            return &chatSession;
        }
    }
    return nullptr;
}

ChatSessionInfo *DataCenter::getChatSessionInfoByUserId(const QString &userId){
    if(_chatSessionList == nullptr){
        return nullptr;
    }
    for(auto& chatSession : *_chatSessionList){
        if(chatSession._userId == userId){
            return &chatSession;
        }
    }
    return nullptr;
}

void DataCenter::topChatSession(const ChatSessionInfo &chatSessionInfo){
    if(_chatSessionList == nullptr){
        return;
    }
    auto it = _chatSessionList->begin();
    for(; it != _chatSessionList->end(); ++it){
        if(it->_chatSessionId == chatSessionInfo._chatSessionId){
            break;
        }
    }
    if(it != _chatSessionList->end()){
        // 保存一下
        ChatSessionInfo tmp = chatSessionInfo;
        _chatSessionList->erase(it);
        _chatSessionList->push_front(tmp);
    }
}

void DataCenter::addChatSessionMessage(const MessageInfo &messageInfo){
    QList<MessageInfo>& messageList = (*_chatSessionToPrevMessage)[messageInfo._chatSessionId];
    messageList.push_back(messageInfo);
}

void DataCenter::getFriendUserListAsync(){
    // 一样的抛给NitClient
    _netClient.getFriendUserList(_loginSessionId);
}

void DataCenter::setFriendUserList(std::shared_ptr<my_chat_proto::GetFriendListRsp> respObj){
    if(_friendUserList == nullptr){
        _friendUserList = new QList<UserInfo>();
    }
    // 清除旧的数据
    _friendUserList->clear();

    const QList<my_chat_proto::UserInfo>& userInfoListPb = respObj->friendList();
    for(const auto& userInfoPb : userInfoListPb){
        UserInfo userInfo;
        userInfo.load(userInfoPb);
        _friendUserList->push_back(userInfo);
    }
}

void DataCenter::getChatSessionListAsync(){
    _netClient.getChatSessionList(_loginSessionId);
}

void DataCenter::setChatSessionList(std::shared_ptr<my_chat_proto::GetChatSessionListRsp> respObj){
    if(_chatSessionList == nullptr){
        _chatSessionList = new QList<ChatSessionInfo>();
    }
    // 清除旧的数据
    _chatSessionList->clear();

    const QList<my_chat_proto::ChatSessionInfo>& chatSessionListPb = respObj->chatSessionInfoList();
    for(const my_chat_proto::ChatSessionInfo& chatSessionInfoPb : chatSessionListPb){
        ChatSessionInfo chatSessionInfo;
        chatSessionInfo.load(chatSessionInfoPb);
        _chatSessionList->push_back(chatSessionInfo);
    }
}

void DataCenter::getApplyUserListAsync(){
    _netClient.getApplyUserList(_loginSessionId);
}

void DataCenter::setApplyUserList(std::shared_ptr<my_chat_proto::GetPendingFriendEventListRsp> respObj){
    if(_applyUserList == nullptr){
        _applyUserList = new QList<UserInfo>();
    }
    _applyUserList->clear();

    const QList<my_chat_proto::FriendEvent>& applyUserEventListPb = respObj->event();
    for(const my_chat_proto::FriendEvent& applyUserEventPb : applyUserEventListPb){
        UserInfo userInfo;
        userInfo.load(applyUserEventPb.sender());
        _applyUserList->push_back(userInfo);
    }
}

void DataCenter::getChatSessionRecentMessageAsync(const QString &chatSessionId, bool updateUI){
    _netClient.getChatSessionRecentMessage(_loginSessionId, chatSessionId, updateUI);
}

void DataCenter::setChatSessionRecentMessage(const QString &chatSessionId, std::shared_ptr<my_chat_proto::GetRecentMsgRsp> respObj){
    QList<MessageInfo>& messageList = (*_chatSessionToPrevMessage)[chatSessionId];
    messageList.clear();
    for(auto& elem : respObj->msgList()){
        MessageInfo message;
        message.load(elem);
        messageList.push_back(message);
    }
}

void DataCenter::sendTextMessageAsync(const QString &chatSessionId, const QString &content){
    // 网络统一发送所有类型的数据，所以要传数据类型，最后把文本消息转成 QByteArray 类型
    _netClient.sendMessage(_loginSessionId, chatSessionId, model::MessageType::TEXT_TYPE, content.toUtf8(), "");
}

void DataCenter::sendImageMessageAsync(const QString &chatSessionId, const QByteArray &content){
    // 网络统一发送所有类型的数据，所以要传数据类型
    _netClient.sendMessage(_loginSessionId, chatSessionId, model::MessageType::IMAGE_TYPE, content, "");
}

void DataCenter::sendFileMessageAsync(const QString &chatSessionId, const QString &fileName, const QByteArray &content){
    // 网络统一发送所有类型的数据，所以要传数据类型
    _netClient.sendMessage(_loginSessionId, chatSessionId, model::MessageType::FILE_TYPE, content, fileName);
}

void DataCenter::sendVoiceMessageAsync(const QString &chatSessionId, const QByteArray &content){
    // 网络统一发送所有类型的数据，所以要传数据类型
    _netClient.sendMessage(_loginSessionId, chatSessionId, model::MessageType::VOICE_TYPE, content, "");
}

void DataCenter::modifyNickNameAsync(const QString &newNickName){
    _netClient.modifyNickName(_loginSessionId, newNickName);
}

void DataCenter::modifyPersonalSignatureAsync(const QString &newPersonalSignature){
    _netClient.modifyPersonalSignature(_loginSessionId, newPersonalSignature);
}

void DataCenter::getPhoneVerifyCodeAsync(const QString &phoneNum){
    // 这里不传 loginSessionId，为了兼容手机号注册登录！
    _netClient.getPhoneVerifyCode(phoneNum);
}

void DataCenter::modifyPhoneNumAsync(const QString &newPhoneNum, const QString& verifyCodeId,
                                     const QString& verifyCode){
    _netClient.modifyPhoneNum(_loginSessionId, newPhoneNum, verifyCodeId, verifyCode);
}

void DataCenter::modifyHeadPortraitAsync(const QByteArray &newHeadPortraitBytes){
    _netClient.modifyHeadPortrait(_loginSessionId, newHeadPortraitBytes);
}

void DataCenter::addFriendApplyAsync(const QString &friendId){
    _netClient.addFriendApply(_loginSessionId, friendId);
}

void DataCenter::deleteFriendAsync(const QString &friendId){
    _netClient.deleteFriend(_loginSessionId, friendId);
}

void DataCenter::acceptAddFriendApplyAsync(const QString &friendId){
    _netClient.acceptAddFriendApply(_loginSessionId, friendId);
}

void DataCenter::refuseAddFriendApplyAsync(const QString &friendId){
    _netClient.refuseAddFriendApply(_loginSessionId, friendId);
}

void DataCenter::createGroupChatSessionAsync(const QList<QString> &groupSessionIdList){
    _netClient.createGroupChatSession(_loginSessionId, groupSessionIdList);
}

void DataCenter::getChatSessionMemberListAsync(const QString& chatSessionId){
    _netClient.getChatSessionMemberList(_loginSessionId, chatSessionId);
}

void DataCenter::setChatSessionMemberList(const QString &chatSessionId, const QList<my_chat_proto::UserInfo> &memberListPb){
    QList<model::UserInfo>& curMemberList = (*_chatSessionToMemberList)[chatSessionId];
    // 先清空
    curMemberList.clear();
    for(const auto& userInfoPb : memberListPb){
        // 把pb结构的userInfo转换成自己的userInfo
        UserInfo userInfo;
        userInfo.load(userInfoPb);
        curMemberList.push_back(userInfo);
    }
}

void DataCenter::searchUserAsync(const QString &searchKey){
    _netClient.searchUser(_loginSessionId, searchKey);
}

void DataCenter::setSearchUserList(const QList<my_chat_proto::UserInfo> &searchUserListPb){
    if(_searchUserList == nullptr){
        _searchUserList = new QList<UserInfo>();
    }
    // 先清空
    _searchUserList->clear();
    for(const auto& userInfoPb : searchUserListPb){
        // 把pb结构的userInfo转换成自己的userInfo
        UserInfo userInfo;
        userInfo.load(userInfoPb);
        _searchUserList->push_back(userInfo);
    }
}

void DataCenter::searchHistoryMessageBySearchKeyAsync(const QString &searchKey){
    _netClient.searchHistoryMessageBySearchKey(_loginSessionId, _currentChatSessionId, searchKey);
}

void DataCenter::setSearchHistoryMessageList(const QList<my_chat_proto::MessageInfo> &searchHistoryMessageListPb){
    if(_searchHistoryMessageList == nullptr){
        _searchHistoryMessageList = new QList<MessageInfo>();
    }
    // 先清空
    _searchHistoryMessageList->clear();
    for(const auto& messageInfoPb : searchHistoryMessageListPb){
        // 把pb结构的userInfo转换成自己的userInfo
        MessageInfo messageInfo;
        messageInfo.load(messageInfoPb);
        _searchHistoryMessageList->push_back(messageInfo);
    }
}

void DataCenter::searchHistoryMessageByTimeAsync(const QDateTime &beginTime, const QDateTime &endTime){
    _netClient.searchHistoryMessageByTime(_loginSessionId, _currentChatSessionId, beginTime, endTime);
}

void DataCenter::userNameSignUpAsync(const QString& userName, const QString& password){
    // 登录注册的http请求都不需要 loginSessionId
    _netClient.userNameSignUp(userName, password);
}

void DataCenter::userNameLoginAsync(const QString& userName, const QString& password){
    // 登录注册的http请求都不需要 loginSessionId
    _netClient.userNameLogin(userName, password);
}

void DataCenter::phoneSignUpAsync(const QString &phoneNum, const QString &verifyCode){
    // 登录注册的http请求都不需要 loginSessionId
    // 对于手机号的登录/注册，有一个验证码ID
    _netClient.phoneSignUp(phoneNum, this->getPhoneVerifyCodeId(), verifyCode);
}

void DataCenter::phoneLoginAsync(const QString &phoneNum, const QString &verifyCode){
    // 登录注册的http请求都不需要 loginSessionId
    // 对于手机号的登录/注册，有一个验证码ID
    _netClient.phoneLogin(phoneNum, this->getPhoneVerifyCodeId(), verifyCode);
}

void DataCenter::getSingleFileContentAsync(const QString &fileId){
    _netClient.getSingleFileContent(_loginSessionId, fileId);
}

void DataCenter::voiceConvertTextAsync(const QString &fileId, const QByteArray &content){
    _netClient.voiceConvertText(_loginSessionId, fileId, content);
}

}  // end namespace
