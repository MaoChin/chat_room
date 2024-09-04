/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_MESSAGE_STORAGE_H
#define QPROTOBUF_MESSAGE_STORAGE_H

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


namespace my_chat_proto {
class GetHistoryMsgReq;
using GetHistoryMsgReqRepeated = QList<GetHistoryMsgReq>;
class GetHistoryMsgRsp;
using GetHistoryMsgRspRepeated = QList<GetHistoryMsgRsp>;
class GetRecentMsgReq;
using GetRecentMsgReqRepeated = QList<GetRecentMsgReq>;
class GetRecentMsgRsp;
using GetRecentMsgRspRepeated = QList<GetRecentMsgRsp>;
class MsgSearchReq;
using MsgSearchReqRepeated = QList<MsgSearchReq>;
class MsgSearchRsp;
using MsgSearchRspRepeated = QList<MsgSearchRsp>;

class GetHistoryMsgReq_QtProtobufData;
class GetHistoryMsgReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetHistoryMsgReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(QtProtobuf::int64 startTime READ startTime WRITE setStartTime SCRIPTABLE false)
    Q_PROPERTY(QtProtobuf::int64 overTime READ overTime WRITE setOverTime SCRIPTABLE false)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        ChatSessionIdProtoFieldNumber = 2,
        StartTimeProtoFieldNumber = 3,
        OverTimeProtoFieldNumber = 4,
        UserIdProtoFieldNumber = 5,
        SessionIdProtoFieldNumber = 6,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetHistoryMsgReq();
    ~GetHistoryMsgReq();
    GetHistoryMsgReq(const GetHistoryMsgReq &other);
    GetHistoryMsgReq &operator =(const GetHistoryMsgReq &other);
    GetHistoryMsgReq(GetHistoryMsgReq &&other) noexcept;
    GetHistoryMsgReq &operator =(GetHistoryMsgReq &&other) noexcept;
    bool operator ==(const GetHistoryMsgReq &other) const;
    bool operator !=(const GetHistoryMsgReq &other) const;

    QString requestId() const;

    QString chatSessionId() const;

    QtProtobuf::int64 startTime() const;

    QtProtobuf::int64 overTime() const;

    QString userId() const;

    QString sessionId() const;
    void setRequestId(const QString &requestId);
    void setChatSessionId(const QString &chatSessionId);
    void setStartTime(const QtProtobuf::int64 &startTime);
    void setOverTime(const QtProtobuf::int64 &overTime);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<GetHistoryMsgReq_QtProtobufData> dptr;
};

class GetHistoryMsgRsp_QtProtobufData;
class GetHistoryMsgRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetHistoryMsgRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::MessageInfoRepeated msgListData READ msgList WRITE setMsgList SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        MsgListProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetHistoryMsgRsp();
    ~GetHistoryMsgRsp();
    GetHistoryMsgRsp(const GetHistoryMsgRsp &other);
    GetHistoryMsgRsp &operator =(const GetHistoryMsgRsp &other);
    GetHistoryMsgRsp(GetHistoryMsgRsp &&other) noexcept;
    GetHistoryMsgRsp &operator =(GetHistoryMsgRsp &&other) noexcept;
    bool operator ==(const GetHistoryMsgRsp &other) const;
    bool operator !=(const GetHistoryMsgRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    MessageInfoRepeated msgList() const;
    MessageInfoRepeated &msgList();
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setMsgList(const MessageInfoRepeated &msgList);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<GetHistoryMsgRsp_QtProtobufData> dptr;
};

class GetRecentMsgReq_QtProtobufData;
class GetRecentMsgReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetRecentMsgReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(QtProtobuf::int64 msgCount READ msgCount WRITE setMsgCount SCRIPTABLE false)
    Q_PROPERTY(QtProtobuf::int64 curTime READ curTime WRITE setCurTime SCRIPTABLE false)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        ChatSessionIdProtoFieldNumber = 2,
        MsgCountProtoFieldNumber = 3,
        CurTimeProtoFieldNumber = 4,
        UserIdProtoFieldNumber = 5,
        SessionIdProtoFieldNumber = 6,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetRecentMsgReq();
    ~GetRecentMsgReq();
    GetRecentMsgReq(const GetRecentMsgReq &other);
    GetRecentMsgReq &operator =(const GetRecentMsgReq &other);
    GetRecentMsgReq(GetRecentMsgReq &&other) noexcept;
    GetRecentMsgReq &operator =(GetRecentMsgReq &&other) noexcept;
    bool operator ==(const GetRecentMsgReq &other) const;
    bool operator !=(const GetRecentMsgReq &other) const;

    QString requestId() const;

    QString chatSessionId() const;

    QtProtobuf::int64 msgCount() const;

    QtProtobuf::int64 curTime() const;

    QString userId() const;

    QString sessionId() const;
    void setRequestId(const QString &requestId);
    void setChatSessionId(const QString &chatSessionId);
    void setMsgCount(const QtProtobuf::int64 &msgCount);
    void setCurTime(const QtProtobuf::int64 &curTime);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<GetRecentMsgReq_QtProtobufData> dptr;
};

class GetRecentMsgRsp_QtProtobufData;
class GetRecentMsgRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetRecentMsgRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::MessageInfoRepeated msgListData READ msgList WRITE setMsgList SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        MsgListProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetRecentMsgRsp();
    ~GetRecentMsgRsp();
    GetRecentMsgRsp(const GetRecentMsgRsp &other);
    GetRecentMsgRsp &operator =(const GetRecentMsgRsp &other);
    GetRecentMsgRsp(GetRecentMsgRsp &&other) noexcept;
    GetRecentMsgRsp &operator =(GetRecentMsgRsp &&other) noexcept;
    bool operator ==(const GetRecentMsgRsp &other) const;
    bool operator !=(const GetRecentMsgRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    MessageInfoRepeated msgList() const;
    MessageInfoRepeated &msgList();
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setMsgList(const MessageInfoRepeated &msgList);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<GetRecentMsgRsp_QtProtobufData> dptr;
};

class MsgSearchReq_QtProtobufData;
class MsgSearchReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(MsgSearchReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QString chatSessionId READ chatSessionId WRITE setChatSessionId SCRIPTABLE true)
    Q_PROPERTY(QString searchKey READ searchKey WRITE setSearchKey SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        ChatSessionIdProtoFieldNumber = 4,
        SearchKeyProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    MsgSearchReq();
    ~MsgSearchReq();
    MsgSearchReq(const MsgSearchReq &other);
    MsgSearchReq &operator =(const MsgSearchReq &other);
    MsgSearchReq(MsgSearchReq &&other) noexcept;
    MsgSearchReq &operator =(MsgSearchReq &&other) noexcept;
    bool operator ==(const MsgSearchReq &other) const;
    bool operator !=(const MsgSearchReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QString chatSessionId() const;

    QString searchKey() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setChatSessionId(const QString &chatSessionId);
    void setSearchKey(const QString &searchKey);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<MsgSearchReq_QtProtobufData> dptr;
};

class MsgSearchRsp_QtProtobufData;
class MsgSearchRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(MsgSearchRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::MessageInfoRepeated msgListData READ msgList WRITE setMsgList SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        MsgListProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    MsgSearchRsp();
    ~MsgSearchRsp();
    MsgSearchRsp(const MsgSearchRsp &other);
    MsgSearchRsp &operator =(const MsgSearchRsp &other);
    MsgSearchRsp(MsgSearchRsp &&other) noexcept;
    MsgSearchRsp &operator =(MsgSearchRsp &&other) noexcept;
    bool operator ==(const MsgSearchRsp &other) const;
    bool operator !=(const MsgSearchRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    MessageInfoRepeated msgList() const;
    MessageInfoRepeated &msgList();
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setMsgList(const MessageInfoRepeated &msgList);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<MsgSearchRsp_QtProtobufData> dptr;
};
} // namespace my_chat_proto

Q_DECLARE_METATYPE(my_chat_proto::GetHistoryMsgReq)
Q_DECLARE_METATYPE(my_chat_proto::GetHistoryMsgRsp)
Q_DECLARE_METATYPE(my_chat_proto::GetRecentMsgReq)
Q_DECLARE_METATYPE(my_chat_proto::GetRecentMsgRsp)
Q_DECLARE_METATYPE(my_chat_proto::MsgSearchReq)
Q_DECLARE_METATYPE(my_chat_proto::MsgSearchRsp)
#endif // QPROTOBUF_MESSAGE_STORAGE_H