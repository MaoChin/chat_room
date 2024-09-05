/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_GATEWAY_H
#define QPROTOBUF_GATEWAY_H

#include <QtProtobuf/qprotobufmessage.h>
#include <QtProtobuf/qprotobufobject.h>
#include <QtProtobuf/qprotobuflazymessagepointer.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>

#include <QtCore/qmetatype.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>

#include <memory>


namespace my_chat_proto {
class ClientAuthenticationReq;
using ClientAuthenticationReqRepeated = QList<ClientAuthenticationReq>;
class ClientAuthenticationRsp;
using ClientAuthenticationRspRepeated = QList<ClientAuthenticationRsp>;

class ClientAuthenticationReq_QtProtobufData;
class ClientAuthenticationReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(ClientAuthenticationReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SessionIdProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    ClientAuthenticationReq();
    ~ClientAuthenticationReq();
    ClientAuthenticationReq(const ClientAuthenticationReq &other);
    ClientAuthenticationReq &operator =(const ClientAuthenticationReq &other);
    ClientAuthenticationReq(ClientAuthenticationReq &&other) noexcept;
    ClientAuthenticationReq &operator =(ClientAuthenticationReq &&other) noexcept;
    bool operator ==(const ClientAuthenticationReq &other) const;
    bool operator !=(const ClientAuthenticationReq &other) const;

    QString requestId() const;

    QString sessionId() const;
    void setRequestId(const QString &requestId);
    void setSessionId(const QString &sessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<ClientAuthenticationReq_QtProtobufData> dptr;
};

class ClientAuthenticationRsp_QtProtobufData;
class ClientAuthenticationRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(ClientAuthenticationRsp)
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

    ClientAuthenticationRsp();
    ~ClientAuthenticationRsp();
    ClientAuthenticationRsp(const ClientAuthenticationRsp &other);
    ClientAuthenticationRsp &operator =(const ClientAuthenticationRsp &other);
    ClientAuthenticationRsp(ClientAuthenticationRsp &&other) noexcept;
    ClientAuthenticationRsp &operator =(ClientAuthenticationRsp &&other) noexcept;
    bool operator ==(const ClientAuthenticationRsp &other) const;
    bool operator !=(const ClientAuthenticationRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<ClientAuthenticationRsp_QtProtobufData> dptr;
};
} // namespace my_chat_proto

Q_DECLARE_METATYPE(my_chat_proto::ClientAuthenticationReq)
Q_DECLARE_METATYPE(my_chat_proto::ClientAuthenticationRsp)
#endif // QPROTOBUF_GATEWAY_H