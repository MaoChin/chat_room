/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_MESSAGE_TRANSMIT_H
#define QPROTOBUF_MESSAGE_TRANSMIT_H

#include <QtProtobuf/qprotobufmessage.h>
#include <QtProtobuf/qprotobufobject.h>
#include <QtProtobuf/qprotobuflazymessagepointer.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include <QtProtobuf/qprotobufoneof.h>
#include "base.qpb.h"

#include <QtCore/qmetatype.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>

#include <memory>


namespace bite_im {
class NewMessageReq;
using NewMessageReqRepeated = QList<NewMessageReq>;
class NewMessageRsp;
using NewMessageRspRepeated = QList<NewMessageRsp>;
class GetTransmitTargetRsp;
using GetTransmitTargetRspRepeated = QList<GetTransmitTargetRsp>;

class NewMessageReq_QtProtobufData;
class NewMessageReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(NewMessageReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(bite_im::MessageContent *message_p READ message_p WRITE setMessage_p SCRIPTABLE false)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        ChatSessionIdProtoFieldNumber = 4,
        MessageProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    NewMessageReq();
    ~NewMessageReq();
    NewMessageReq(const NewMessageReq &other);
    NewMessageReq &operator =(const NewMessageReq &other);
    NewMessageReq(NewMessageReq &&other) noexcept;
    NewMessageReq &operator =(NewMessageReq &&other) noexcept;
    bool operator ==(const NewMessageReq &other) const;
    bool operator !=(const NewMessageReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QString chatSessionId() const;

    MessageContent &message() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setChatSessionId(const QString &chatSessionId);
    void setMessage(const MessageContent &message);
    static void registerTypes();

private:
    MessageContent *message_p() const;
    void setMessage_p(MessageContent *message);
    QExplicitlySharedDataPointer<NewMessageReq_QtProtobufData> dptr;
};

class NewMessageRsp_QtProtobufData;
class NewMessageRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(NewMessageRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
    };
    Q_ENUM(QtProtobufFieldEnum)

    NewMessageRsp();
    ~NewMessageRsp();
    NewMessageRsp(const NewMessageRsp &other);
    NewMessageRsp &operator =(const NewMessageRsp &other);
    NewMessageRsp(NewMessageRsp &&other) noexcept;
    NewMessageRsp &operator =(NewMessageRsp &&other) noexcept;
    bool operator ==(const NewMessageRsp &other) const;
    bool operator !=(const NewMessageRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<NewMessageRsp_QtProtobufData> dptr;
};

class GetTransmitTargetRsp_QtProtobufData;
class GetTransmitTargetRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetTransmitTargetRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(bite_im::MessageInfo *message_p READ message_p WRITE setMessage_p SCRIPTABLE false)
    Q_PROPERTY(QStringList targetIdList READ targetIdList WRITE setTargetIdList SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        MessageProtoFieldNumber = 4,
        TargetIdListProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetTransmitTargetRsp();
    ~GetTransmitTargetRsp();
    GetTransmitTargetRsp(const GetTransmitTargetRsp &other);
    GetTransmitTargetRsp &operator =(const GetTransmitTargetRsp &other);
    GetTransmitTargetRsp(GetTransmitTargetRsp &&other) noexcept;
    GetTransmitTargetRsp &operator =(GetTransmitTargetRsp &&other) noexcept;
    bool operator ==(const GetTransmitTargetRsp &other) const;
    bool operator !=(const GetTransmitTargetRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    MessageInfo &message() const;

    QStringList targetIdList() const;
    QStringList &targetIdList();
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setMessage(const MessageInfo &message);
    void setTargetIdList(const QStringList &targetIdList);
    static void registerTypes();

private:
    MessageInfo *message_p() const;
    void setMessage_p(MessageInfo *message);
    QExplicitlySharedDataPointer<GetTransmitTargetRsp_QtProtobufData> dptr;
};
} // namespace bite_im

Q_DECLARE_METATYPE(bite_im::NewMessageReq)
Q_DECLARE_METATYPE(bite_im::NewMessageRsp)
Q_DECLARE_METATYPE(bite_im::GetTransmitTargetRsp)
#endif // QPROTOBUF_MESSAGE_TRANSMIT_H
