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


}  // end namespace
