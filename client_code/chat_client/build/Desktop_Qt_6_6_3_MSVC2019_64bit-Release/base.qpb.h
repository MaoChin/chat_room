/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_BASE_H
#define QPROTOBUF_BASE_H

#include <QtProtobuf/qprotobufmessage.h>
#include <QtProtobuf/qprotobufobject.h>
#include <QtProtobuf/qprotobuflazymessagepointer.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include <QtProtobuf/qprotobufoneof.h>

#include <QtCore/qmetatype.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>

#include <memory>


namespace my_chat_proto {

namespace MessageTypeGadget {
Q_NAMESPACE
void registerTypes();
enum MessageType {
    STRING = 0,
    IMAGE = 1,
    FILE = 2,
    VOICE = 3,
};
Q_ENUM_NS(MessageType)
using MessageTypeRepeated = QList<MessageType>;
};
class UserInfo;
using UserInfoRepeated = QList<UserInfo>;
class ChatSessionInfo;
using ChatSessionInfoRepeated = QList<ChatSessionInfo>;
class StringMessageInfo;
using StringMessageInfoRepeated = QList<StringMessageInfo>;
class ImageMessageInfo;
using ImageMessageInfoRepeated = QList<ImageMessageInfo>;
class FileMessageInfo;
using FileMessageInfoRepeated = QList<FileMessageInfo>;
class SpeechMessageInfo;
using SpeechMessageInfoRepeated = QList<SpeechMessageInfo>;
class MessageContent;
using MessageContentRepeated = QList<MessageContent>;
class MessageInfo;
using MessageInfoRepeated = QList<MessageInfo>;
class Message;
using MessageRepeated = QList<Message>;
class FileDownloadData;
using FileDownloadDataRepeated = QList<FileDownloadData>;
class FileUploadData;
using FileUploadDataRepeated = QList<FileUploadData>;

class UserInfo_QtProtobufData;
class UserInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(UserInfo)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName SCRIPTABLE true)
    Q_PROPERTY(QString personSignature READ personSignature WRITE setPersonSignature SCRIPTABLE true)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber SCRIPTABLE true)
    Q_PROPERTY(QByteArray headPortrait READ headPortrait WRITE setHeadPortrait SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        UserIdProtoFieldNumber = 1,
        NickNameProtoFieldNumber = 2,
        PersonSignatureProtoFieldNumber = 3,
        PhoneNumberProtoFieldNumber = 4,
        HeadPortraitProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    UserInfo();
    ~UserInfo();
    UserInfo(const UserInfo &other);
    UserInfo &operator =(const UserInfo &other);
    UserInfo(UserInfo &&other) noexcept;
    UserInfo &operator =(UserInfo &&other) noexcept;
    bool operator ==(const UserInfo &other) const;
    bool operator !=(const UserInfo &other) const;

    QString userId() const;

    QString nickName() const;

    QString personSignature() const;

    QString phoneNumber() const;

    QByteArray headPortrait() const;
    void setUserId(const QString &userId);
    void setNickName(const QString &nickName);
    void setPersonSignature(const QString &personSignature);
    void setPhoneNumber(const QString &phoneNumber);
    void setHeadPortrait(const QByteArray &headPortrait);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<UserInfo_QtProtobufData> dptr;
};

class ChatSessionInfo_QtProtobufData;
class ChatSessionInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(ChatSessionInfo)
    Q_PROPERTY(QString singleChatFriendId READ singleChatFriendId WRITE setSingleChatFriendId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionName READ chatSessionName WRITE setChatSessionName SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::MessageInfo *prevMessage_p READ prevMessage_p WRITE setPrevMessage_p SCRIPTABLE false)
    Q_PROPERTY(QByteArray headPortrait READ headPortrait WRITE setHeadPortrait SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        SingleChatFriendIdProtoFieldNumber = 1,
        ChatSessionIdProtoFieldNumber = 2,
        ChatSessionNameProtoFieldNumber = 3,
        PrevMessageProtoFieldNumber = 4,
        HeadPortraitProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    ChatSessionInfo();
    ~ChatSessionInfo();
    ChatSessionInfo(const ChatSessionInfo &other);
    ChatSessionInfo &operator =(const ChatSessionInfo &other);
    ChatSessionInfo(ChatSessionInfo &&other) noexcept;
    ChatSessionInfo &operator =(ChatSessionInfo &&other) noexcept;
    bool operator ==(const ChatSessionInfo &other) const;
    bool operator !=(const ChatSessionInfo &other) const;

    QString singleChatFriendId() const;

    QString chatSessionId() const;

    QString chatSessionName() const;

    MessageInfo &prevMessage() const;

    QByteArray headPortrait() const;
    void setSingleChatFriendId(const QString &singleChatFriendId);
    void setChatSessionId(const QString &chatSessionId);
    void setChatSessionName(const QString &chatSessionName);
    void setPrevMessage(const MessageInfo &prevMessage);
    void setHeadPortrait(const QByteArray &headPortrait);
    static void registerTypes();

private:
    MessageInfo *prevMessage_p() const;
    void setPrevMessage_p(MessageInfo *prevMessage);
    QExplicitlySharedDataPointer<ChatSessionInfo_QtProtobufData> dptr;
};

class StringMessageInfo_QtProtobufData;
class StringMessageInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(StringMessageInfo)
    Q_PROPERTY(QString content READ content WRITE setContent SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        ContentProtoFieldNumber = 1,
    };
    Q_ENUM(QtProtobufFieldEnum)

    StringMessageInfo();
    ~StringMessageInfo();
    StringMessageInfo(const StringMessageInfo &other);
    StringMessageInfo &operator =(const StringMessageInfo &other);
    StringMessageInfo(StringMessageInfo &&other) noexcept;
    StringMessageInfo &operator =(StringMessageInfo &&other) noexcept;
    bool operator ==(const StringMessageInfo &other) const;
    bool operator !=(const StringMessageInfo &other) const;

    QString content() const;
    void setContent(const QString &content);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<StringMessageInfo_QtProtobufData> dptr;
};

class ImageMessageInfo_QtProtobufData;
class ImageMessageInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(ImageMessageInfo)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId SCRIPTABLE true)
    Q_PROPERTY(QByteArray imageContent READ imageContent WRITE setImageContent SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        FileIdProtoFieldNumber = 1,
        ImageContentProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    ImageMessageInfo();
    ~ImageMessageInfo();
    ImageMessageInfo(const ImageMessageInfo &other);
    ImageMessageInfo &operator =(const ImageMessageInfo &other);
    ImageMessageInfo(ImageMessageInfo &&other) noexcept;
    ImageMessageInfo &operator =(ImageMessageInfo &&other) noexcept;
    bool operator ==(const ImageMessageInfo &other) const;
    bool operator !=(const ImageMessageInfo &other) const;

    QString fileId() const;

    QByteArray imageContent() const;
    void setFileId(const QString &fileId);
    void setImageContent(const QByteArray &imageContent);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<ImageMessageInfo_QtProtobufData> dptr;
};

class FileMessageInfo_QtProtobufData;
class FileMessageInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(FileMessageInfo)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId SCRIPTABLE true)
    Q_PROPERTY(QtProtobuf::int64 fileSize READ fileSize WRITE setFileSize SCRIPTABLE false)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName SCRIPTABLE true)
    Q_PROPERTY(QByteArray fileContents READ fileContents WRITE setFileContents SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        FileIdProtoFieldNumber = 1,
        FileSizeProtoFieldNumber = 2,
        FileNameProtoFieldNumber = 3,
        FileContentsProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    FileMessageInfo();
    ~FileMessageInfo();
    FileMessageInfo(const FileMessageInfo &other);
    FileMessageInfo &operator =(const FileMessageInfo &other);
    FileMessageInfo(FileMessageInfo &&other) noexcept;
    FileMessageInfo &operator =(FileMessageInfo &&other) noexcept;
    bool operator ==(const FileMessageInfo &other) const;
    bool operator !=(const FileMessageInfo &other) const;

    QString fileId() const;

    QtProtobuf::int64 fileSize() const;

    QString fileName() const;

    QByteArray fileContents() const;
    void setFileId(const QString &fileId);
    void setFileSize(const QtProtobuf::int64 &fileSize);
    void setFileName(const QString &fileName);
    void setFileContents(const QByteArray &fileContents);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<FileMessageInfo_QtProtobufData> dptr;
};

class SpeechMessageInfo_QtProtobufData;
class SpeechMessageInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SpeechMessageInfo)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId SCRIPTABLE true)
    Q_PROPERTY(QByteArray fileContents READ fileContents WRITE setFileContents SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        FileIdProtoFieldNumber = 1,
        FileContentsProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    SpeechMessageInfo();
    ~SpeechMessageInfo();
    SpeechMessageInfo(const SpeechMessageInfo &other);
    SpeechMessageInfo &operator =(const SpeechMessageInfo &other);
    SpeechMessageInfo(SpeechMessageInfo &&other) noexcept;
    SpeechMessageInfo &operator =(SpeechMessageInfo &&other) noexcept;
    bool operator ==(const SpeechMessageInfo &other) const;
    bool operator !=(const SpeechMessageInfo &other) const;

    QString fileId() const;

    QByteArray fileContents() const;
    void setFileId(const QString &fileId);
    void setFileContents(const QByteArray &fileContents);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SpeechMessageInfo_QtProtobufData> dptr;
};

class MessageContent_QtProtobufData;
class MessageContent : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(MessageContent)
    Q_PROPERTY(my_chat_proto::MessageTypeGadget::MessageType messageType READ messageType WRITE setMessageType SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::StringMessageInfo *stringMessage READ stringMessage_p WRITE setStringMessage_p)
    Q_PROPERTY(bool hasStringMessage READ hasStringMessage)
    Q_PROPERTY(my_chat_proto::FileMessageInfo *fileMessage READ fileMessage_p WRITE setFileMessage_p)
    Q_PROPERTY(bool hasFileMessage READ hasFileMessage)
    Q_PROPERTY(my_chat_proto::SpeechMessageInfo *speechMessage READ speechMessage_p WRITE setSpeechMessage_p)
    Q_PROPERTY(bool hasSpeechMessage READ hasSpeechMessage)
    Q_PROPERTY(my_chat_proto::ImageMessageInfo *imageMessage READ imageMessage_p WRITE setImageMessage_p)
    Q_PROPERTY(bool hasImageMessage READ hasImageMessage)

public:
    enum QtProtobufFieldEnum {
        MessageTypeProtoFieldNumber = 1,
        StringMessageProtoFieldNumber = 2,
        FileMessageProtoFieldNumber = 3,
        SpeechMessageProtoFieldNumber = 4,
        ImageMessageProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    enum class Msg_contentFields {
        UninitializedField = QtProtobuf::InvalidFieldNumber,
        StringMessage = 2,
        FileMessage = 3,
        SpeechMessage = 4,
        ImageMessage = 5,
    };
    Q_ENUM(Msg_contentFields)

    MessageContent();
    ~MessageContent();
    MessageContent(const MessageContent &other);
    MessageContent &operator =(const MessageContent &other);
    MessageContent(MessageContent &&other) noexcept;
    MessageContent &operator =(MessageContent &&other) noexcept;
    bool operator ==(const MessageContent &other) const;
    bool operator !=(const MessageContent &other) const;

    MessageTypeGadget::MessageType messageType() const;

    bool hasStringMessage() const;
    StringMessageInfo &stringMessage() const;

    bool hasFileMessage() const;
    FileMessageInfo &fileMessage() const;

    bool hasSpeechMessage() const;
    SpeechMessageInfo &speechMessage() const;

    bool hasImageMessage() const;
    ImageMessageInfo &imageMessage() const;
    Msg_contentFields msg_contentField() const;
    void setMessageType(const MessageTypeGadget::MessageType &messageType);
    void setStringMessage(const StringMessageInfo &stringMessage);
    void setFileMessage(const FileMessageInfo &fileMessage);
    void setSpeechMessage(const SpeechMessageInfo &speechMessage);
    void setImageMessage(const ImageMessageInfo &imageMessage);
    void clearMsg_content();
    static void registerTypes();

private:
    StringMessageInfo *stringMessage_p() const;
    FileMessageInfo *fileMessage_p() const;
    SpeechMessageInfo *speechMessage_p() const;
    ImageMessageInfo *imageMessage_p() const;
    void setStringMessage_p(StringMessageInfo *stringMessage);
    void setFileMessage_p(FileMessageInfo *fileMessage);
    void setSpeechMessage_p(SpeechMessageInfo *speechMessage);
    void setImageMessage_p(ImageMessageInfo *imageMessage);
    QExplicitlySharedDataPointer<MessageContent_QtProtobufData> dptr;
};

class MessageInfo_QtProtobufData;
class MessageInfo : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(MessageInfo)
    Q_PROPERTY(QString messageId READ messageId WRITE setMessageId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(QtProtobuf::int64 timestamp READ timestamp WRITE setTimestamp SCRIPTABLE false)
    Q_PROPERTY(my_chat_proto::UserInfo *sender_p READ sender_p WRITE setSender_p SCRIPTABLE false)
    Q_PROPERTY(my_chat_proto::MessageContent *message_p READ message_p WRITE setMessage_p SCRIPTABLE false)

public:
    enum QtProtobufFieldEnum {
        MessageIdProtoFieldNumber = 1,
        ChatSessionIdProtoFieldNumber = 2,
        TimestampProtoFieldNumber = 3,
        SenderProtoFieldNumber = 4,
        MessageProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    MessageInfo();
    ~MessageInfo();
    MessageInfo(const MessageInfo &other);
    MessageInfo &operator =(const MessageInfo &other);
    MessageInfo(MessageInfo &&other) noexcept;
    MessageInfo &operator =(MessageInfo &&other) noexcept;
    bool operator ==(const MessageInfo &other) const;
    bool operator !=(const MessageInfo &other) const;

    QString messageId() const;

    QString chatSessionId() const;

    QtProtobuf::int64 timestamp() const;

    UserInfo &sender() const;

    MessageContent &message() const;
    void setMessageId(const QString &messageId);
    void setChatSessionId(const QString &chatSessionId);
    void setTimestamp(const QtProtobuf::int64 &timestamp);
    void setSender(const UserInfo &sender);
    void setMessage(const MessageContent &message);
    static void registerTypes();

private:
    UserInfo *sender_p() const;
    MessageContent *message_p() const;
    void setSender_p(UserInfo *sender);
    void setMessage_p(MessageContent *message);
    QExplicitlySharedDataPointer<MessageInfo_QtProtobufData> dptr;
};

class Message_QtProtobufData;
class Message : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(Message)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::MessageInfo *message_p READ message_p WRITE setMessage_p SCRIPTABLE false)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        MessageProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    Message();
    ~Message();
    Message(const Message &other);
    Message &operator =(const Message &other);
    Message(Message &&other) noexcept;
    Message &operator =(Message &&other) noexcept;
    bool operator ==(const Message &other) const;
    bool operator !=(const Message &other) const;

    QString requestId() const;

    MessageInfo &message() const;
    void setRequestId(const QString &requestId);
    void setMessage(const MessageInfo &message);
    static void registerTypes();

private:
    MessageInfo *message_p() const;
    void setMessage_p(MessageInfo *message);
    QExplicitlySharedDataPointer<Message_QtProtobufData> dptr;
};

class FileDownloadData_QtProtobufData;
class FileDownloadData : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(FileDownloadData)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId SCRIPTABLE true)
    Q_PROPERTY(QByteArray fileContent READ fileContent WRITE setFileContent SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        FileIdProtoFieldNumber = 1,
        FileContentProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    FileDownloadData();
    ~FileDownloadData();
    FileDownloadData(const FileDownloadData &other);
    FileDownloadData &operator =(const FileDownloadData &other);
    FileDownloadData(FileDownloadData &&other) noexcept;
    FileDownloadData &operator =(FileDownloadData &&other) noexcept;
    bool operator ==(const FileDownloadData &other) const;
    bool operator !=(const FileDownloadData &other) const;

    QString fileId() const;

    QByteArray fileContent() const;
    void setFileId(const QString &fileId);
    void setFileContent(const QByteArray &fileContent);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<FileDownloadData_QtProtobufData> dptr;
};

class FileUploadData_QtProtobufData;
class FileUploadData : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(FileUploadData)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName SCRIPTABLE true)
    Q_PROPERTY(QtProtobuf::int64 fileSize READ fileSize WRITE setFileSize SCRIPTABLE false)
    Q_PROPERTY(QByteArray fileContent READ fileContent WRITE setFileContent SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        FileNameProtoFieldNumber = 1,
        FileSizeProtoFieldNumber = 2,
        FileContentProtoFieldNumber = 3,
    };
    Q_ENUM(QtProtobufFieldEnum)

    FileUploadData();
    ~FileUploadData();
    FileUploadData(const FileUploadData &other);
    FileUploadData &operator =(const FileUploadData &other);
    FileUploadData(FileUploadData &&other) noexcept;
    FileUploadData &operator =(FileUploadData &&other) noexcept;
    bool operator ==(const FileUploadData &other) const;
    bool operator !=(const FileUploadData &other) const;

    QString fileName() const;

    QtProtobuf::int64 fileSize() const;

    QByteArray fileContent() const;
    void setFileName(const QString &fileName);
    void setFileSize(const QtProtobuf::int64 &fileSize);
    void setFileContent(const QByteArray &fileContent);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<FileUploadData_QtProtobufData> dptr;
};
} // namespace my_chat_proto

Q_DECLARE_METATYPE(my_chat_proto::UserInfo)
Q_DECLARE_METATYPE(my_chat_proto::ChatSessionInfo)
Q_DECLARE_METATYPE(my_chat_proto::StringMessageInfo)
Q_DECLARE_METATYPE(my_chat_proto::ImageMessageInfo)
Q_DECLARE_METATYPE(my_chat_proto::FileMessageInfo)
Q_DECLARE_METATYPE(my_chat_proto::SpeechMessageInfo)
Q_DECLARE_METATYPE(my_chat_proto::MessageContent)
Q_DECLARE_METATYPE(my_chat_proto::MessageInfo)
Q_DECLARE_METATYPE(my_chat_proto::Message)
Q_DECLARE_METATYPE(my_chat_proto::FileDownloadData)
Q_DECLARE_METATYPE(my_chat_proto::FileUploadData)
#endif // QPROTOBUF_BASE_H