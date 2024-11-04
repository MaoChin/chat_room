/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#include "message_storage.qpb.h"
#include <QtProtobuf/qprotobufserializer.h>

namespace my_chat_proto {

class MsgSearchByTimeReq_QtProtobufData : public QSharedData
{
public:
    MsgSearchByTimeReq_QtProtobufData()
        : QSharedData(),
          m_startTime(0),
          m_overTime(0)
    {
    }

    MsgSearchByTimeReq_QtProtobufData(const MsgSearchByTimeReq_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_chatSessionId(other.m_chatSessionId),
          m_startTime(other.m_startTime),
          m_overTime(other.m_overTime),
          m_userId(other.m_userId),
          m_loginSessionId(other.m_loginSessionId)
    {
    }

    QString m_requestId;
    QString m_chatSessionId;
    QtProtobuf::int64 m_startTime;
    QtProtobuf::int64 m_overTime;
    QString m_userId;
    QString m_loginSessionId;
};

MsgSearchByTimeReq::~MsgSearchByTimeReq() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 25> qt_protobuf_MsgSearchByTimeReq_uint_data;
    const char qt_protobuf_MsgSearchByTimeReq_char_data[99];
} qt_protobuf_MsgSearchByTimeReq_metadata {
    // data
    {
        0, /* = version */
        6, /* = num fields */
        7, /* = field number offset */
        13, /* = property index offset */
        19, /* = field flags offset */
        32, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        33, /* = requestId */
        43, /* = chatSessionId */
        57, /* = startTime */
        67, /* = overTime */
        76, /* = userId */
        83, /* = loginSessionId */
        98, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = chatSessionId */
        3, /* = startTime */
        4, /* = overTime */
        5, /* = userId */
        6, /* = loginSessionId */
        // Property indices:
        0, /* = requestId */
        1, /* = chatSessionId */
        2, /* = startTime */
        3, /* = overTime */
        4, /* = userId */
        5, /* = loginSessionId */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = chatSessionId */
        QtProtobufPrivate::NoFlags, /* = startTime */
        QtProtobufPrivate::NoFlags, /* = overTime */
        QtProtobufPrivate::NoFlags, /* = userId */
        QtProtobufPrivate::NoFlags, /* = loginSessionId */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.MsgSearchByTimeReq\0" /* = full message name */
    /* field char_data: */
    "requestId\0chatSessionId\0startTime\0overTime\0userId\0"
    "loginSessionId\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering MsgSearchByTimeReq::propertyOrdering = {
    &qt_protobuf_MsgSearchByTimeReq_metadata.data
};

void MsgSearchByTimeReq::registerTypes()
{
    qRegisterMetaType<MsgSearchByTimeReq>();
    qRegisterMetaType<MsgSearchByTimeReqRepeated>();
}

MsgSearchByTimeReq::MsgSearchByTimeReq()
    : QProtobufMessage(&MsgSearchByTimeReq::staticMetaObject),
      dptr(new MsgSearchByTimeReq_QtProtobufData)
{
}

MsgSearchByTimeReq::MsgSearchByTimeReq(const MsgSearchByTimeReq &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
MsgSearchByTimeReq &MsgSearchByTimeReq::operator =(const MsgSearchByTimeReq &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
MsgSearchByTimeReq::MsgSearchByTimeReq(MsgSearchByTimeReq &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
MsgSearchByTimeReq &MsgSearchByTimeReq::operator =(MsgSearchByTimeReq &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool MsgSearchByTimeReq::operator ==(const MsgSearchByTimeReq &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_chatSessionId == other.dptr->m_chatSessionId
        && dptr->m_startTime == other.dptr->m_startTime
        && dptr->m_overTime == other.dptr->m_overTime;
}

bool MsgSearchByTimeReq::operator !=(const MsgSearchByTimeReq &other) const
{
    return !this->operator ==(other);
}

QString MsgSearchByTimeReq::requestId() const
{
    return dptr->m_requestId;
}

QString MsgSearchByTimeReq::chatSessionId() const
{
    return dptr->m_chatSessionId;
}

QtProtobuf::int64 MsgSearchByTimeReq::startTime() const
{
    return dptr->m_startTime;
}

QtProtobuf::int64 MsgSearchByTimeReq::overTime() const
{
    return dptr->m_overTime;
}

QString MsgSearchByTimeReq::userId() const
{
    return dptr->m_userId;
}

QString MsgSearchByTimeReq::loginSessionId() const
{
    return dptr->m_loginSessionId;
}

void MsgSearchByTimeReq::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void MsgSearchByTimeReq::setChatSessionId(const QString &chatSessionId)
{
    if (dptr->m_chatSessionId != chatSessionId) {
        dptr.detach();
        dptr->m_chatSessionId = chatSessionId;
    }
}

void MsgSearchByTimeReq::setStartTime(const QtProtobuf::int64 &startTime)
{
    if (dptr->m_startTime != startTime) {
        dptr.detach();
        dptr->m_startTime = startTime;
    }
}

void MsgSearchByTimeReq::setOverTime(const QtProtobuf::int64 &overTime)
{
    if (dptr->m_overTime != overTime) {
        dptr.detach();
        dptr->m_overTime = overTime;
    }
}

void MsgSearchByTimeReq::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}

void MsgSearchByTimeReq::setLoginSessionId(const QString &loginSessionId)
{
    if (dptr->m_loginSessionId != loginSessionId) {
        dptr.detach();
        dptr->m_loginSessionId = loginSessionId;
    }
}


class MsgSearchByTimeRsp_QtProtobufData : public QSharedData
{
public:
    MsgSearchByTimeRsp_QtProtobufData()
        : QSharedData(),
          m_success(false)
    {
    }

    MsgSearchByTimeRsp_QtProtobufData(const MsgSearchByTimeRsp_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_success(other.m_success),
          m_errmsg(other.m_errmsg),
          m_msgList(other.m_msgList)
    {
    }

    QString m_requestId;
    bool m_success;
    QString m_errmsg;
    MessageInfoRepeated m_msgList;
};

MsgSearchByTimeRsp::~MsgSearchByTimeRsp() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_MsgSearchByTimeRsp_uint_data;
    const char qt_protobuf_MsgSearchByTimeRsp_char_data[67];
} qt_protobuf_MsgSearchByTimeRsp_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        32, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        33, /* = requestId */
        43, /* = success */
        51, /* = errmsg */
        58, /* = msgList */
        66, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = success */
        3, /* = errmsg */
        4, /* = msgList */
        // Property indices:
        0, /* = requestId */
        1, /* = success */
        2, /* = errmsg */
        3, /* = msgList */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = success */
        QtProtobufPrivate::NoFlags, /* = errmsg */
        QtProtobufPrivate::NoFlags, /* = msgList */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.MsgSearchByTimeRsp\0" /* = full message name */
    /* field char_data: */
    "requestId\0success\0errmsg\0msgList\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering MsgSearchByTimeRsp::propertyOrdering = {
    &qt_protobuf_MsgSearchByTimeRsp_metadata.data
};

void MsgSearchByTimeRsp::registerTypes()
{
    qRegisterMetaType<MsgSearchByTimeRsp>();
    qRegisterMetaType<MsgSearchByTimeRspRepeated>();
}

MsgSearchByTimeRsp::MsgSearchByTimeRsp()
    : QProtobufMessage(&MsgSearchByTimeRsp::staticMetaObject),
      dptr(new MsgSearchByTimeRsp_QtProtobufData)
{
}

MsgSearchByTimeRsp::MsgSearchByTimeRsp(const MsgSearchByTimeRsp &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
MsgSearchByTimeRsp &MsgSearchByTimeRsp::operator =(const MsgSearchByTimeRsp &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
MsgSearchByTimeRsp::MsgSearchByTimeRsp(MsgSearchByTimeRsp &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
MsgSearchByTimeRsp &MsgSearchByTimeRsp::operator =(MsgSearchByTimeRsp &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool MsgSearchByTimeRsp::operator ==(const MsgSearchByTimeRsp &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_success == other.dptr->m_success
        && dptr->m_errmsg == other.dptr->m_errmsg
        && QtProtobuf::repeatedValueCompare(dptr->m_msgList, other.dptr->m_msgList);
}

bool MsgSearchByTimeRsp::operator !=(const MsgSearchByTimeRsp &other) const
{
    return !this->operator ==(other);
}

QString MsgSearchByTimeRsp::requestId() const
{
    return dptr->m_requestId;
}

bool MsgSearchByTimeRsp::success() const
{
    return dptr->m_success;
}

QString MsgSearchByTimeRsp::errmsg() const
{
    return dptr->m_errmsg;
}

MessageInfoRepeated MsgSearchByTimeRsp::msgList() const
{
    return dptr->m_msgList;
}

MessageInfoRepeated &MsgSearchByTimeRsp::msgList()
{
    dptr.detach();
    return dptr->m_msgList;
}

void MsgSearchByTimeRsp::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void MsgSearchByTimeRsp::setSuccess(const bool &success)
{
    if (dptr->m_success != success) {
        dptr.detach();
        dptr->m_success = success;
    }
}

void MsgSearchByTimeRsp::setErrmsg(const QString &errmsg)
{
    if (dptr->m_errmsg != errmsg) {
        dptr.detach();
        dptr->m_errmsg = errmsg;
    }
}

void MsgSearchByTimeRsp::setMsgList(const MessageInfoRepeated &msgList)
{
    if (dptr->m_msgList != msgList) {
        dptr.detach();
        dptr->m_msgList = msgList;
    }
}


class GetRecentMsgReq_QtProtobufData : public QSharedData
{
public:
    GetRecentMsgReq_QtProtobufData()
        : QSharedData(),
          m_msgCount(0),
          m_curTime(0)
    {
    }

    GetRecentMsgReq_QtProtobufData(const GetRecentMsgReq_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_chatSessionId(other.m_chatSessionId),
          m_msgCount(other.m_msgCount),
          m_curTime(other.m_curTime),
          m_userId(other.m_userId),
          m_loginSessionId(other.m_loginSessionId)
    {
    }

    QString m_requestId;
    QString m_chatSessionId;
    QtProtobuf::int64 m_msgCount;
    QtProtobuf::int64 m_curTime;
    QString m_userId;
    QString m_loginSessionId;
};

GetRecentMsgReq::~GetRecentMsgReq() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 25> qt_protobuf_GetRecentMsgReq_uint_data;
    const char qt_protobuf_GetRecentMsgReq_char_data[94];
} qt_protobuf_GetRecentMsgReq_metadata {
    // data
    {
        0, /* = version */
        6, /* = num fields */
        7, /* = field number offset */
        13, /* = property index offset */
        19, /* = field flags offset */
        29, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        30, /* = requestId */
        40, /* = chatSessionId */
        54, /* = msgCount */
        63, /* = curTime */
        71, /* = userId */
        78, /* = loginSessionId */
        93, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = chatSessionId */
        3, /* = msgCount */
        4, /* = curTime */
        5, /* = userId */
        6, /* = loginSessionId */
        // Property indices:
        0, /* = requestId */
        1, /* = chatSessionId */
        2, /* = msgCount */
        3, /* = curTime */
        4, /* = userId */
        5, /* = loginSessionId */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = chatSessionId */
        QtProtobufPrivate::NoFlags, /* = msgCount */
        QtProtobufPrivate::NoFlags, /* = curTime */
        QtProtobufPrivate::NoFlags, /* = userId */
        QtProtobufPrivate::NoFlags, /* = loginSessionId */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.GetRecentMsgReq\0" /* = full message name */
    /* field char_data: */
    "requestId\0chatSessionId\0msgCount\0curTime\0userId\0"
    "loginSessionId\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering GetRecentMsgReq::propertyOrdering = {
    &qt_protobuf_GetRecentMsgReq_metadata.data
};

void GetRecentMsgReq::registerTypes()
{
    qRegisterMetaType<GetRecentMsgReq>();
    qRegisterMetaType<GetRecentMsgReqRepeated>();
}

GetRecentMsgReq::GetRecentMsgReq()
    : QProtobufMessage(&GetRecentMsgReq::staticMetaObject),
      dptr(new GetRecentMsgReq_QtProtobufData)
{
}

GetRecentMsgReq::GetRecentMsgReq(const GetRecentMsgReq &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
GetRecentMsgReq &GetRecentMsgReq::operator =(const GetRecentMsgReq &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
GetRecentMsgReq::GetRecentMsgReq(GetRecentMsgReq &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
GetRecentMsgReq &GetRecentMsgReq::operator =(GetRecentMsgReq &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool GetRecentMsgReq::operator ==(const GetRecentMsgReq &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_chatSessionId == other.dptr->m_chatSessionId
        && dptr->m_msgCount == other.dptr->m_msgCount;
}

bool GetRecentMsgReq::operator !=(const GetRecentMsgReq &other) const
{
    return !this->operator ==(other);
}

QString GetRecentMsgReq::requestId() const
{
    return dptr->m_requestId;
}

QString GetRecentMsgReq::chatSessionId() const
{
    return dptr->m_chatSessionId;
}

QtProtobuf::int64 GetRecentMsgReq::msgCount() const
{
    return dptr->m_msgCount;
}

QtProtobuf::int64 GetRecentMsgReq::curTime() const
{
    return dptr->m_curTime;
}

QString GetRecentMsgReq::userId() const
{
    return dptr->m_userId;
}

QString GetRecentMsgReq::loginSessionId() const
{
    return dptr->m_loginSessionId;
}

void GetRecentMsgReq::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void GetRecentMsgReq::setChatSessionId(const QString &chatSessionId)
{
    if (dptr->m_chatSessionId != chatSessionId) {
        dptr.detach();
        dptr->m_chatSessionId = chatSessionId;
    }
}

void GetRecentMsgReq::setMsgCount(const QtProtobuf::int64 &msgCount)
{
    if (dptr->m_msgCount != msgCount) {
        dptr.detach();
        dptr->m_msgCount = msgCount;
    }
}

void GetRecentMsgReq::setCurTime(const QtProtobuf::int64 &curTime)
{
    if (dptr->m_curTime != curTime) {
        dptr.detach();
        dptr->m_curTime = curTime;
    }
}

void GetRecentMsgReq::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}

void GetRecentMsgReq::setLoginSessionId(const QString &loginSessionId)
{
    if (dptr->m_loginSessionId != loginSessionId) {
        dptr.detach();
        dptr->m_loginSessionId = loginSessionId;
    }
}


class GetRecentMsgRsp_QtProtobufData : public QSharedData
{
public:
    GetRecentMsgRsp_QtProtobufData()
        : QSharedData(),
          m_success(false)
    {
    }

    GetRecentMsgRsp_QtProtobufData(const GetRecentMsgRsp_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_success(other.m_success),
          m_errmsg(other.m_errmsg),
          m_msgList(other.m_msgList)
    {
    }

    QString m_requestId;
    bool m_success;
    QString m_errmsg;
    MessageInfoRepeated m_msgList;
};

GetRecentMsgRsp::~GetRecentMsgRsp() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_GetRecentMsgRsp_uint_data;
    const char qt_protobuf_GetRecentMsgRsp_char_data[64];
} qt_protobuf_GetRecentMsgRsp_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        29, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        30, /* = requestId */
        40, /* = success */
        48, /* = errmsg */
        55, /* = msgList */
        63, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = success */
        3, /* = errmsg */
        4, /* = msgList */
        // Property indices:
        0, /* = requestId */
        1, /* = success */
        2, /* = errmsg */
        3, /* = msgList */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = success */
        QtProtobufPrivate::NoFlags, /* = errmsg */
        QtProtobufPrivate::NoFlags, /* = msgList */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.GetRecentMsgRsp\0" /* = full message name */
    /* field char_data: */
    "requestId\0success\0errmsg\0msgList\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering GetRecentMsgRsp::propertyOrdering = {
    &qt_protobuf_GetRecentMsgRsp_metadata.data
};

void GetRecentMsgRsp::registerTypes()
{
    qRegisterMetaType<GetRecentMsgRsp>();
    qRegisterMetaType<GetRecentMsgRspRepeated>();
}

GetRecentMsgRsp::GetRecentMsgRsp()
    : QProtobufMessage(&GetRecentMsgRsp::staticMetaObject),
      dptr(new GetRecentMsgRsp_QtProtobufData)
{
}

GetRecentMsgRsp::GetRecentMsgRsp(const GetRecentMsgRsp &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
GetRecentMsgRsp &GetRecentMsgRsp::operator =(const GetRecentMsgRsp &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
GetRecentMsgRsp::GetRecentMsgRsp(GetRecentMsgRsp &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
GetRecentMsgRsp &GetRecentMsgRsp::operator =(GetRecentMsgRsp &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool GetRecentMsgRsp::operator ==(const GetRecentMsgRsp &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_success == other.dptr->m_success
        && dptr->m_errmsg == other.dptr->m_errmsg
        && QtProtobuf::repeatedValueCompare(dptr->m_msgList, other.dptr->m_msgList);
}

bool GetRecentMsgRsp::operator !=(const GetRecentMsgRsp &other) const
{
    return !this->operator ==(other);
}

QString GetRecentMsgRsp::requestId() const
{
    return dptr->m_requestId;
}

bool GetRecentMsgRsp::success() const
{
    return dptr->m_success;
}

QString GetRecentMsgRsp::errmsg() const
{
    return dptr->m_errmsg;
}

MessageInfoRepeated GetRecentMsgRsp::msgList() const
{
    return dptr->m_msgList;
}

MessageInfoRepeated &GetRecentMsgRsp::msgList()
{
    dptr.detach();
    return dptr->m_msgList;
}

void GetRecentMsgRsp::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void GetRecentMsgRsp::setSuccess(const bool &success)
{
    if (dptr->m_success != success) {
        dptr.detach();
        dptr->m_success = success;
    }
}

void GetRecentMsgRsp::setErrmsg(const QString &errmsg)
{
    if (dptr->m_errmsg != errmsg) {
        dptr.detach();
        dptr->m_errmsg = errmsg;
    }
}

void GetRecentMsgRsp::setMsgList(const MessageInfoRepeated &msgList)
{
    if (dptr->m_msgList != msgList) {
        dptr.detach();
        dptr->m_msgList = msgList;
    }
}


class MsgSearchBySearchKeyReq_QtProtobufData : public QSharedData
{
public:
    MsgSearchBySearchKeyReq_QtProtobufData()
        : QSharedData()
    {
    }

    MsgSearchBySearchKeyReq_QtProtobufData(const MsgSearchBySearchKeyReq_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_userId(other.m_userId),
          m_loginSessionId(other.m_loginSessionId),
          m_chatSessionId(other.m_chatSessionId),
          m_searchKey(other.m_searchKey)
    {
    }

    QString m_requestId;
    QString m_userId;
    QString m_loginSessionId;
    QString m_chatSessionId;
    QString m_searchKey;
};

MsgSearchBySearchKeyReq::~MsgSearchBySearchKeyReq() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 21> qt_protobuf_MsgSearchBySearchKeyReq_uint_data;
    const char qt_protobuf_MsgSearchBySearchKeyReq_char_data[95];
} qt_protobuf_MsgSearchBySearchKeyReq_metadata {
    // data
    {
        0, /* = version */
        5, /* = num fields */
        6, /* = field number offset */
        11, /* = property index offset */
        16, /* = field flags offset */
        37, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        38, /* = requestId */
        48, /* = userId */
        55, /* = loginSessionId */
        70, /* = chatSessionId */
        84, /* = searchKey */
        94, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = userId */
        3, /* = loginSessionId */
        4, /* = chatSessionId */
        5, /* = searchKey */
        // Property indices:
        0, /* = requestId */
        1, /* = userId */
        2, /* = loginSessionId */
        3, /* = chatSessionId */
        4, /* = searchKey */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = userId */
        QtProtobufPrivate::NoFlags, /* = loginSessionId */
        QtProtobufPrivate::NoFlags, /* = chatSessionId */
        QtProtobufPrivate::NoFlags, /* = searchKey */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.MsgSearchBySearchKeyReq\0" /* = full message name */
    /* field char_data: */
    "requestId\0userId\0loginSessionId\0chatSessionId\0searchKey\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering MsgSearchBySearchKeyReq::propertyOrdering = {
    &qt_protobuf_MsgSearchBySearchKeyReq_metadata.data
};

void MsgSearchBySearchKeyReq::registerTypes()
{
    qRegisterMetaType<MsgSearchBySearchKeyReq>();
    qRegisterMetaType<MsgSearchBySearchKeyReqRepeated>();
}

MsgSearchBySearchKeyReq::MsgSearchBySearchKeyReq()
    : QProtobufMessage(&MsgSearchBySearchKeyReq::staticMetaObject),
      dptr(new MsgSearchBySearchKeyReq_QtProtobufData)
{
}

MsgSearchBySearchKeyReq::MsgSearchBySearchKeyReq(const MsgSearchBySearchKeyReq &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
MsgSearchBySearchKeyReq &MsgSearchBySearchKeyReq::operator =(const MsgSearchBySearchKeyReq &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
MsgSearchBySearchKeyReq::MsgSearchBySearchKeyReq(MsgSearchBySearchKeyReq &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
MsgSearchBySearchKeyReq &MsgSearchBySearchKeyReq::operator =(MsgSearchBySearchKeyReq &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool MsgSearchBySearchKeyReq::operator ==(const MsgSearchBySearchKeyReq &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_chatSessionId == other.dptr->m_chatSessionId
        && dptr->m_searchKey == other.dptr->m_searchKey;
}

bool MsgSearchBySearchKeyReq::operator !=(const MsgSearchBySearchKeyReq &other) const
{
    return !this->operator ==(other);
}

QString MsgSearchBySearchKeyReq::requestId() const
{
    return dptr->m_requestId;
}

QString MsgSearchBySearchKeyReq::userId() const
{
    return dptr->m_userId;
}

QString MsgSearchBySearchKeyReq::loginSessionId() const
{
    return dptr->m_loginSessionId;
}

QString MsgSearchBySearchKeyReq::chatSessionId() const
{
    return dptr->m_chatSessionId;
}

QString MsgSearchBySearchKeyReq::searchKey() const
{
    return dptr->m_searchKey;
}

void MsgSearchBySearchKeyReq::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void MsgSearchBySearchKeyReq::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}

void MsgSearchBySearchKeyReq::setLoginSessionId(const QString &loginSessionId)
{
    if (dptr->m_loginSessionId != loginSessionId) {
        dptr.detach();
        dptr->m_loginSessionId = loginSessionId;
    }
}

void MsgSearchBySearchKeyReq::setChatSessionId(const QString &chatSessionId)
{
    if (dptr->m_chatSessionId != chatSessionId) {
        dptr.detach();
        dptr->m_chatSessionId = chatSessionId;
    }
}

void MsgSearchBySearchKeyReq::setSearchKey(const QString &searchKey)
{
    if (dptr->m_searchKey != searchKey) {
        dptr.detach();
        dptr->m_searchKey = searchKey;
    }
}


class MsgSearchBySearchKeyRsp_QtProtobufData : public QSharedData
{
public:
    MsgSearchBySearchKeyRsp_QtProtobufData()
        : QSharedData(),
          m_success(false)
    {
    }

    MsgSearchBySearchKeyRsp_QtProtobufData(const MsgSearchBySearchKeyRsp_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_success(other.m_success),
          m_errmsg(other.m_errmsg),
          m_msgList(other.m_msgList)
    {
    }

    QString m_requestId;
    bool m_success;
    QString m_errmsg;
    MessageInfoRepeated m_msgList;
};

MsgSearchBySearchKeyRsp::~MsgSearchBySearchKeyRsp() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_MsgSearchBySearchKeyRsp_uint_data;
    const char qt_protobuf_MsgSearchBySearchKeyRsp_char_data[72];
} qt_protobuf_MsgSearchBySearchKeyRsp_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        37, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        38, /* = requestId */
        48, /* = success */
        56, /* = errmsg */
        63, /* = msgList */
        71, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = success */
        3, /* = errmsg */
        4, /* = msgList */
        // Property indices:
        0, /* = requestId */
        1, /* = success */
        2, /* = errmsg */
        3, /* = msgList */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = success */
        QtProtobufPrivate::NoFlags, /* = errmsg */
        QtProtobufPrivate::NoFlags, /* = msgList */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.MsgSearchBySearchKeyRsp\0" /* = full message name */
    /* field char_data: */
    "requestId\0success\0errmsg\0msgList\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering MsgSearchBySearchKeyRsp::propertyOrdering = {
    &qt_protobuf_MsgSearchBySearchKeyRsp_metadata.data
};

void MsgSearchBySearchKeyRsp::registerTypes()
{
    qRegisterMetaType<MsgSearchBySearchKeyRsp>();
    qRegisterMetaType<MsgSearchBySearchKeyRspRepeated>();
}

MsgSearchBySearchKeyRsp::MsgSearchBySearchKeyRsp()
    : QProtobufMessage(&MsgSearchBySearchKeyRsp::staticMetaObject),
      dptr(new MsgSearchBySearchKeyRsp_QtProtobufData)
{
}

MsgSearchBySearchKeyRsp::MsgSearchBySearchKeyRsp(const MsgSearchBySearchKeyRsp &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
MsgSearchBySearchKeyRsp &MsgSearchBySearchKeyRsp::operator =(const MsgSearchBySearchKeyRsp &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
MsgSearchBySearchKeyRsp::MsgSearchBySearchKeyRsp(MsgSearchBySearchKeyRsp &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
MsgSearchBySearchKeyRsp &MsgSearchBySearchKeyRsp::operator =(MsgSearchBySearchKeyRsp &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool MsgSearchBySearchKeyRsp::operator ==(const MsgSearchBySearchKeyRsp &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_success == other.dptr->m_success
        && dptr->m_errmsg == other.dptr->m_errmsg
        && QtProtobuf::repeatedValueCompare(dptr->m_msgList, other.dptr->m_msgList);
}

bool MsgSearchBySearchKeyRsp::operator !=(const MsgSearchBySearchKeyRsp &other) const
{
    return !this->operator ==(other);
}

QString MsgSearchBySearchKeyRsp::requestId() const
{
    return dptr->m_requestId;
}

bool MsgSearchBySearchKeyRsp::success() const
{
    return dptr->m_success;
}

QString MsgSearchBySearchKeyRsp::errmsg() const
{
    return dptr->m_errmsg;
}

MessageInfoRepeated MsgSearchBySearchKeyRsp::msgList() const
{
    return dptr->m_msgList;
}

MessageInfoRepeated &MsgSearchBySearchKeyRsp::msgList()
{
    dptr.detach();
    return dptr->m_msgList;
}

void MsgSearchBySearchKeyRsp::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void MsgSearchBySearchKeyRsp::setSuccess(const bool &success)
{
    if (dptr->m_success != success) {
        dptr.detach();
        dptr->m_success = success;
    }
}

void MsgSearchBySearchKeyRsp::setErrmsg(const QString &errmsg)
{
    if (dptr->m_errmsg != errmsg) {
        dptr.detach();
        dptr->m_errmsg = errmsg;
    }
}

void MsgSearchBySearchKeyRsp::setMsgList(const MessageInfoRepeated &msgList)
{
    if (dptr->m_msgList != msgList) {
        dptr.detach();
        dptr->m_msgList = msgList;
    }
}

} // namespace my_chat_proto

#include "moc_message_storage.qpb.cpp"
