#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>
#include <QFileInfo>
#include <QIcon>


// protobuf 编译后的一些头文件
#include "file.qpb.h"
#include "gateway.qpb.h"
#include "user.qpb.h"
#include "friend.qpb.h"
#include "voice_recognition.qpb.h"
#include "base.qpb.h"
#include "message_storage.qpb.h"
#include "message_transmit.qpb.h"
#include "notify.qpb.h"


// 客户端的一些工具函数
#define TAG QString("[file: %1, line: %2]").arg(getFileName(__FILE__), QString::number(__LINE__))
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


// 一些构造用户数据，构造消息的函数
static inline my_chat_proto::UserInfo makeUserInfo(int index, const QByteArray& headPortraitByte){
    my_chat_proto::UserInfo userInfo;
    userInfo.setUserId(QString::number(index));
    userInfo.setNickName("会话" + QString::number(index));
    userInfo.setPersonSignature("你好");
    userInfo.setHeadPortrait(headPortraitByte);
    userInfo.setPhoneNumber("12345466");
    return userInfo;
}

// 这几个消息的构造要多看几遍 proto 文件中 这些不同消息类型的结构
static inline my_chat_proto::MessageInfo makeTextMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait){
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    my_chat_proto::TextMessageInfo textMessage;
    textMessage.setTextContent("这是一条消息" + QString::number(index));

    my_chat_proto::MessageContent messageContent;
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::TEXT);
    messageContent.setTextMessage(textMessage);

    messageInfo.setMessage(messageContent);
    return messageInfo;
}

static inline my_chat_proto::MessageInfo makeImageMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait){
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    // 这里只是一个图片的id，需要再通过fileId发起二次请求获取图片内容
    my_chat_proto::ImageMessageInfo imageMessage;
    imageMessage.setFileId("testImage");

    my_chat_proto::MessageContent messageContent;
    messageContent.setImageMessage(imageMessage);
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::IMAGE);

    messageInfo.setMessage(messageContent);
    return messageInfo;
}

static inline my_chat_proto::MessageInfo makeFileMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait) {
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    // 这里只是一个文件的id，需要再通过fileId发起二次请求获取图片内容
    my_chat_proto::FileMessageInfo fileMessageInfo;
    fileMessageInfo.setFileId("testFile");
    fileMessageInfo.setFileName("test.txt");
    // 此处文件大小, 无法设置. 由于 fileSize 属性, 不是 optional , 此处先设置一个 0 进来
    fileMessageInfo.setFileSize(0);

    my_chat_proto::MessageContent messageContent;
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::FILE);
    messageContent.setFileMessage(fileMessageInfo);
    messageInfo.setMessage(messageContent);
    return messageInfo;
}

static inline my_chat_proto::MessageInfo makeVoiceMessageInfo(int index, const QString& chatSessionId, const QByteArray& headPortrait) {
    my_chat_proto::MessageInfo messageInfo;
    messageInfo.setMessageId(QString::number(index));
    messageInfo.setChatSessionId(chatSessionId);
    messageInfo.setTimestamp(getTimestamp());
    messageInfo.setSender(makeUserInfo(index, headPortrait));

    // 这里只是一个语音文件的id，需要再通过fileId发起二次请求获取图片内容
    my_chat_proto::VoiceMessageInfo voiceMessageInfo;
    voiceMessageInfo.setFileId("testVoice");

    my_chat_proto::MessageContent messageContent;
    messageContent.setMessageType(my_chat_proto::MessageTypeGadget::MessageType::VOICE);
    messageContent.setVoiceMessage(voiceMessageInfo);
    messageInfo.setMessage(messageContent);
    return messageInfo;
}


#endif // UTIL_H
