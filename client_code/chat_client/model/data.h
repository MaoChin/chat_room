#pragma once

#include <QString>
#include <QIcon>
#include <QUuid>
#include <QDateTime>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QFileInfo>

// protobuf 文件编译后生成的头文件，搞了个 qpb
#include "base.qpb.h"

// 命名空间：约定最外层目录下使用全局空间，子目录下命名空间和目录名一致
namespace model{

////////////////////////
/// \brief some micro
// qDebug , __FILE__ , __LINE__ 也是宏，arg() 表示格式化解析，noquote()表示打印时不带""
#define TAG QString("[file: %1, line: %2]").arg(model::getFileName(__FILE__), QString::number(__LINE__))
#define LOG() qDebug().noquote() << TAG

////////////////////////
/// \brief some util function
/// 使用static和inline修饰，避免链接时出现 函数重定义
static inline QString makeFormatTime(int64_t timestamp){
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(timestamp);
    return dateTime.toString("MM-dd HH:mm:ss");
}
static inline int64_t getTimestamp(){
    return QDateTime::currentSecsSinceEpoch();
}

// 获取当前文件名称
static inline QString getFileName(const QString& path){
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

// QByteArray转QIcon
static inline QIcon makeQIcon(const QByteArray& byteArray){
    // 借助QPixmap
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    QIcon icon(pixmap);
    return icon;
}

// 文件操作
// 读文件到 QByteArray
static inline QByteArray readFileToByteArray(const QString& path){
    QFile file(path);
    bool ok = file.open(QFile::ReadOnly);
    if(!ok){
        LOG() << "open file: " + path + "error!";
        return QByteArray();
    }
    QByteArray content = file.readAll();
    file.close();
    return content;
}

// 写文件
static inline bool writeByteArrayToFile(const QString& path, const QByteArray& content){
    QFile file(path);
    bool ok = file.open(QFile::WriteOnly);
    if(!ok){
        LOG() << "open file: " + path + " error!";
        return false;
    }
    file.write(content);
    // 写文件时都是先写到缓冲区，再统一刷盘。这里需要手动刷新一下缓冲区
    file.flush();
    file.close();
    return true;
}

////////////////////////
/// \brief The UserInfo class
///
class UserInfo{
public:
    QString _userId = "";                 // ID
    QString _phoneNum = "";               // 电话
    QString _nickName = "";               // 昵称/用户名
    QString _personalSignature = "";      // 个性签名
    QIcon _headPortrait;             	  // 头像

    // 把 protobuf 文件中的 UserInfo 对象转换到Qt中
    void loadUserInfo(const my_chat_proto::UserInfo& userInfo){
        this->_userId = userInfo.userId();
        this->_phoneNum = userInfo.phoneNumber();
        this->_nickName = userInfo.nickName();
        this->_personalSignature = userInfo.personSignature();
        if(userInfo.headPortrait().isEmpty()){
            // 用户没有设置头像，就使用默认头像
            this->_headPortrait = QIcon(":/resource/image/defaultHeadPortrait.png");
        }
        else{
            // makeIcon 可以将 QByteArray 类型转换成 QIcon
            this->_headPortrait = makeQIcon(userInfo.headPortrait());
        }
    }

};

enum MessageType{
    TEXT_TYPE,
    IMAGE_TYPE,
    FILE_TYPE,
    VOICE_TYPE
};
//////////////////////
/// \brief The MessageInfo class
///
class MessageInfo{
public:
    QString _messageId = ""; 			// ID
    QString _chatSessionId = "";		// 所属会话（外键）
    QString _sendTime = "";				// 消息发送的时间
    MessageType _messageType;			// 消息类型
    UserInfo _sender;					// 发送者信息
    QByteArray _content;				// 消息内容，由于类型多变，所以使用QByteArray，表示二进制数据
    // 文件消息一般比较大，而网络是比较慢且贵的资源，所以获取文件消息时可以先拿到fileId，再获取相关文件(常用)
    QString _fileId = "";				// 标识文件消息，如图片，文件，语音
    QString _fileName = "";				// 只有消息类型是FILE_TYPE时才有用

    // 工厂模式
    static MessageInfo makeMessageInfo(const QString& chatSessionId, MessageType messageType,
                            const UserInfo& sender, const QByteArray& content, const QString& extraData) {
        if(messageType == TEXT_TYPE){
            return makeTextMessage(chatSessionId, sender, content);
        }
        else if(messageType == IMAGE_TYPE){
            return makeImageMessage(chatSessionId, sender, content);
        }
        else if(messageType == FILE_TYPE){
            // 是文件类型时，这个extraData就是文件名
           return makeFileMessage(chatSessionId, sender, content, extraData);
        }
        else if(messageType == VOICE_TYPE){
            return makeVoiceMessage(chatSessionId, sender, content);
        }
        else{
            return MessageInfo();
        }
    }

private:
    // 使用UUID生成唯一的 messageId
    static QString makeId(){
        // 不使用int类型进行自增是为了考虑分布式环境
        // 在分布式环境下自增类型不能保证一致性
        // UUID很长，这里截取最后一段
        return "Message" + QUuid::createUuid().toString().sliced(25, 12);
    }
    static MessageInfo makeTextMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content){
        MessageInfo messageInfo;
        messageInfo._messageId = makeId();
        messageInfo._chatSessionId = chatSessionId;
        messageInfo._sendTime = makeFormatTime(getTimestamp());
        messageInfo._messageType = TEXT_TYPE;
        messageInfo._sender = sender;
        messageInfo._content = content;
        messageInfo._fileId = "";
        messageInfo._fileName = "";
        return messageInfo;
    }
    static MessageInfo makeImageMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content){
        MessageInfo messageInfo;
        messageInfo._messageId = makeId();
        messageInfo._chatSessionId = chatSessionId;
        messageInfo._sendTime = makeFormatTime(getTimestamp());
        messageInfo._messageType = IMAGE_TYPE;
        messageInfo._sender = sender;
        messageInfo._content = content;
        messageInfo._fileId = "";
        messageInfo._fileName = "";
        return messageInfo;
    }
    static MessageInfo makeFileMessage(const QString& chatSessionId, const UserInfo& sender,
                                       const QByteArray& content, const QString& fileName){
        MessageInfo messageInfo;
        messageInfo._messageId = makeId();
        messageInfo._chatSessionId = chatSessionId;
        messageInfo._sendTime = makeFormatTime(getTimestamp());
        messageInfo._messageType = FILE_TYPE;
        messageInfo._sender = sender;
        messageInfo._content = content;
        messageInfo._fileId = "";
        messageInfo._fileName = fileName;
        return messageInfo;
    }
    static MessageInfo makeVoiceMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content){
        MessageInfo messageInfo;
        messageInfo._messageId = makeId();
        messageInfo._chatSessionId = chatSessionId;
        messageInfo._sendTime = makeFormatTime(getTimestamp());
        messageInfo._messageType = VOICE_TYPE;
        messageInfo._sender = sender;
        messageInfo._content = content;
        messageInfo._fileId = "";
        messageInfo._fileName = "";
        return messageInfo;
    }
};

///////////////////////
/// \brief The SessionInfo class
///
class ChatSessionInfo{
public:
    QString _chatSessionId = "";         // ID
    QString _chatSessionName = "";       // 会话名字，单聊时就是对方昵称，群聊时就是群名称
    QString _userId = "";				 // 对于单聊就是对方ID，群聊就设成""
    MessageInfo _lastMessage;       	 // 最后一条消息，用于在会话列表中显示
    QIcon _headPortrait;		  	 	 // 会话图标，用于在会话列表中显示
};


} // end model
