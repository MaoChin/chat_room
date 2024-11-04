/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#include "notify.qpb.h"
#include <QtProtobuf/qprotobufserializer.h>

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyTypeGadget(NotifyTypeGadget::registerTypes);
void NotifyTypeGadget::registerTypes()
{
    qRegisterMetaType<NotifyType>();
    qRegisterMetaType<my_chat_proto::NotifyTypeGadget::NotifyType>();
    qRegisterProtobufEnumType<my_chat_proto::NotifyTypeGadget::NotifyType>();
}


class NotifyFriendAddApply_QtProtobufData : public QSharedData
{
public:
    NotifyFriendAddApply_QtProtobufData()
        : QSharedData(),
          m_userInfo(nullptr)
    {
    }

    NotifyFriendAddApply_QtProtobufData(const NotifyFriendAddApply_QtProtobufData &other)
        : QSharedData(other),
          m_userInfo(other.m_userInfo
                                               ? new UserInfo(*other.m_userInfo)
                                               : nullptr)
    {
    }

    QtProtobufPrivate::QProtobufLazyMessagePointer<UserInfo> m_userInfo;
};

NotifyFriendAddApply::~NotifyFriendAddApply() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 5> qt_protobuf_NotifyFriendAddApply_uint_data;
    const char qt_protobuf_NotifyFriendAddApply_char_data[45];
} qt_protobuf_NotifyFriendAddApply_metadata {
    // data
    {
        0, /* = version */
        1, /* = num fields */
        2, /* = field number offset */
        3, /* = property index offset */
        4, /* = field flags offset */
        34, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        35, /* = userInfo */
        44, /* = end-of-string-marker */
        // Field numbers:
        1, /* = userInfo */
        // Property indices:
        0, /* = userInfo */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = userInfo */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyFriendAddApply\0" /* = full message name */
    /* field char_data: */
    "userInfo\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyFriendAddApply::propertyOrdering = {
    &qt_protobuf_NotifyFriendAddApply_metadata.data
};

void NotifyFriendAddApply::registerTypes()
{
    qRegisterMetaType<NotifyFriendAddApply>();
    qRegisterMetaType<NotifyFriendAddApplyRepeated>();
}

NotifyFriendAddApply::NotifyFriendAddApply()
    : QProtobufMessage(&NotifyFriendAddApply::staticMetaObject),
      dptr(new NotifyFriendAddApply_QtProtobufData)
{
}

NotifyFriendAddApply::NotifyFriendAddApply(const NotifyFriendAddApply &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyFriendAddApply &NotifyFriendAddApply::operator =(const NotifyFriendAddApply &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyFriendAddApply::NotifyFriendAddApply(NotifyFriendAddApply &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyFriendAddApply &NotifyFriendAddApply::operator =(NotifyFriendAddApply &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyFriendAddApply::operator ==(const NotifyFriendAddApply &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && (dptr->m_userInfo == other.dptr->m_userInfo
            || *dptr->m_userInfo == *other.dptr->m_userInfo);
}

bool NotifyFriendAddApply::operator !=(const NotifyFriendAddApply &other) const
{
    return !this->operator ==(other);
}

UserInfo *NotifyFriendAddApply::userInfo_p() const
{
    return dptr->m_userInfo ? dptr->m_userInfo.get() : nullptr;
}

UserInfo &NotifyFriendAddApply::userInfo() const
{
    return *dptr->m_userInfo;
}

void NotifyFriendAddApply::setUserInfo_p(UserInfo *userInfo)
{
    if (dptr->m_userInfo.get() != userInfo) {
        dptr.detach();
        dptr->m_userInfo.reset(userInfo);
    }
}

void NotifyFriendAddApply::setUserInfo(const UserInfo &userInfo)
{
    if (*dptr->m_userInfo != userInfo) {
        dptr.detach();
        *dptr->m_userInfo = userInfo;
    }
}


class NotifyFriendAddProcess_QtProtobufData : public QSharedData
{
public:
    NotifyFriendAddProcess_QtProtobufData()
        : QSharedData(),
          m_agree(false),
          m_userInfo(nullptr)
    {
    }

    NotifyFriendAddProcess_QtProtobufData(const NotifyFriendAddProcess_QtProtobufData &other)
        : QSharedData(other),
          m_agree(other.m_agree),
          m_userInfo(other.m_userInfo
                                               ? new UserInfo(*other.m_userInfo)
                                               : nullptr)
    {
    }

    bool m_agree;
    QtProtobufPrivate::QProtobufLazyMessagePointer<UserInfo> m_userInfo;
};

NotifyFriendAddProcess::~NotifyFriendAddProcess() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 9> qt_protobuf_NotifyFriendAddProcess_uint_data;
    const char qt_protobuf_NotifyFriendAddProcess_char_data[53];
} qt_protobuf_NotifyFriendAddProcess_metadata {
    // data
    {
        0, /* = version */
        2, /* = num fields */
        3, /* = field number offset */
        5, /* = property index offset */
        7, /* = field flags offset */
        36, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        37, /* = agree */
        43, /* = userInfo */
        52, /* = end-of-string-marker */
        // Field numbers:
        1, /* = agree */
        2, /* = userInfo */
        // Property indices:
        0, /* = agree */
        1, /* = userInfo */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = agree */
        QtProtobufPrivate::NoFlags, /* = userInfo */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyFriendAddProcess\0" /* = full message name */
    /* field char_data: */
    "agree\0userInfo\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyFriendAddProcess::propertyOrdering = {
    &qt_protobuf_NotifyFriendAddProcess_metadata.data
};

void NotifyFriendAddProcess::registerTypes()
{
    qRegisterMetaType<NotifyFriendAddProcess>();
    qRegisterMetaType<NotifyFriendAddProcessRepeated>();
}

NotifyFriendAddProcess::NotifyFriendAddProcess()
    : QProtobufMessage(&NotifyFriendAddProcess::staticMetaObject),
      dptr(new NotifyFriendAddProcess_QtProtobufData)
{
}

NotifyFriendAddProcess::NotifyFriendAddProcess(const NotifyFriendAddProcess &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyFriendAddProcess &NotifyFriendAddProcess::operator =(const NotifyFriendAddProcess &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyFriendAddProcess::NotifyFriendAddProcess(NotifyFriendAddProcess &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyFriendAddProcess &NotifyFriendAddProcess::operator =(NotifyFriendAddProcess &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyFriendAddProcess::operator ==(const NotifyFriendAddProcess &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_agree == other.dptr->m_agree
        && (dptr->m_userInfo == other.dptr->m_userInfo
            || *dptr->m_userInfo == *other.dptr->m_userInfo);
}

bool NotifyFriendAddProcess::operator !=(const NotifyFriendAddProcess &other) const
{
    return !this->operator ==(other);
}

bool NotifyFriendAddProcess::agree() const
{
    return dptr->m_agree;
}

UserInfo *NotifyFriendAddProcess::userInfo_p() const
{
    return dptr->m_userInfo ? dptr->m_userInfo.get() : nullptr;
}

UserInfo &NotifyFriendAddProcess::userInfo() const
{
    return *dptr->m_userInfo;
}

void NotifyFriendAddProcess::setAgree(const bool &agree)
{
    if (dptr->m_agree != agree) {
        dptr.detach();
        dptr->m_agree = agree;
    }
}

void NotifyFriendAddProcess::setUserInfo_p(UserInfo *userInfo)
{
    if (dptr->m_userInfo.get() != userInfo) {
        dptr.detach();
        dptr->m_userInfo.reset(userInfo);
    }
}

void NotifyFriendAddProcess::setUserInfo(const UserInfo &userInfo)
{
    if (*dptr->m_userInfo != userInfo) {
        dptr.detach();
        *dptr->m_userInfo = userInfo;
    }
}


class NotifyFriendDelete_QtProtobufData : public QSharedData
{
public:
    NotifyFriendDelete_QtProtobufData()
        : QSharedData()
    {
    }

    NotifyFriendDelete_QtProtobufData(const NotifyFriendDelete_QtProtobufData &other)
        : QSharedData(other),
          m_userId(other.m_userId)
    {
    }

    QString m_userId;
};

NotifyFriendDelete::~NotifyFriendDelete() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 5> qt_protobuf_NotifyFriendDelete_uint_data;
    const char qt_protobuf_NotifyFriendDelete_char_data[41];
} qt_protobuf_NotifyFriendDelete_metadata {
    // data
    {
        0, /* = version */
        1, /* = num fields */
        2, /* = field number offset */
        3, /* = property index offset */
        4, /* = field flags offset */
        32, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        33, /* = userId */
        40, /* = end-of-string-marker */
        // Field numbers:
        1, /* = userId */
        // Property indices:
        0, /* = userId */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = userId */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyFriendDelete\0" /* = full message name */
    /* field char_data: */
    "userId\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyFriendDelete::propertyOrdering = {
    &qt_protobuf_NotifyFriendDelete_metadata.data
};

void NotifyFriendDelete::registerTypes()
{
    qRegisterMetaType<NotifyFriendDelete>();
    qRegisterMetaType<NotifyFriendDeleteRepeated>();
}

NotifyFriendDelete::NotifyFriendDelete()
    : QProtobufMessage(&NotifyFriendDelete::staticMetaObject),
      dptr(new NotifyFriendDelete_QtProtobufData)
{
}

NotifyFriendDelete::NotifyFriendDelete(const NotifyFriendDelete &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyFriendDelete &NotifyFriendDelete::operator =(const NotifyFriendDelete &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyFriendDelete::NotifyFriendDelete(NotifyFriendDelete &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyFriendDelete &NotifyFriendDelete::operator =(NotifyFriendDelete &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyFriendDelete::operator ==(const NotifyFriendDelete &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_userId == other.dptr->m_userId;
}

bool NotifyFriendDelete::operator !=(const NotifyFriendDelete &other) const
{
    return !this->operator ==(other);
}

QString NotifyFriendDelete::userId() const
{
    return dptr->m_userId;
}

void NotifyFriendDelete::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}


class NotifyNewChatSession_QtProtobufData : public QSharedData
{
public:
    NotifyNewChatSession_QtProtobufData()
        : QSharedData(),
          m_chatSessionInfo(nullptr)
    {
    }

    NotifyNewChatSession_QtProtobufData(const NotifyNewChatSession_QtProtobufData &other)
        : QSharedData(other),
          m_chatSessionInfo(other.m_chatSessionInfo
                                               ? new ChatSessionInfo(*other.m_chatSessionInfo)
                                               : nullptr)
    {
    }

    QtProtobufPrivate::QProtobufLazyMessagePointer<ChatSessionInfo> m_chatSessionInfo;
};

NotifyNewChatSession::~NotifyNewChatSession() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 5> qt_protobuf_NotifyNewChatSession_uint_data;
    const char qt_protobuf_NotifyNewChatSession_char_data[52];
} qt_protobuf_NotifyNewChatSession_metadata {
    // data
    {
        0, /* = version */
        1, /* = num fields */
        2, /* = field number offset */
        3, /* = property index offset */
        4, /* = field flags offset */
        34, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        35, /* = chatSessionInfo */
        51, /* = end-of-string-marker */
        // Field numbers:
        1, /* = chatSessionInfo */
        // Property indices:
        0, /* = chatSessionInfo */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = chatSessionInfo */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyNewChatSession\0" /* = full message name */
    /* field char_data: */
    "chatSessionInfo\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyNewChatSession::propertyOrdering = {
    &qt_protobuf_NotifyNewChatSession_metadata.data
};

void NotifyNewChatSession::registerTypes()
{
    qRegisterMetaType<NotifyNewChatSession>();
    qRegisterMetaType<NotifyNewChatSessionRepeated>();
}

NotifyNewChatSession::NotifyNewChatSession()
    : QProtobufMessage(&NotifyNewChatSession::staticMetaObject),
      dptr(new NotifyNewChatSession_QtProtobufData)
{
}

NotifyNewChatSession::NotifyNewChatSession(const NotifyNewChatSession &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyNewChatSession &NotifyNewChatSession::operator =(const NotifyNewChatSession &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyNewChatSession::NotifyNewChatSession(NotifyNewChatSession &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyNewChatSession &NotifyNewChatSession::operator =(NotifyNewChatSession &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyNewChatSession::operator ==(const NotifyNewChatSession &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && (dptr->m_chatSessionInfo == other.dptr->m_chatSessionInfo
            || *dptr->m_chatSessionInfo == *other.dptr->m_chatSessionInfo);
}

bool NotifyNewChatSession::operator !=(const NotifyNewChatSession &other) const
{
    return !this->operator ==(other);
}

ChatSessionInfo *NotifyNewChatSession::chatSessionInfo_p() const
{
    return dptr->m_chatSessionInfo ? dptr->m_chatSessionInfo.get() : nullptr;
}

ChatSessionInfo &NotifyNewChatSession::chatSessionInfo() const
{
    return *dptr->m_chatSessionInfo;
}

void NotifyNewChatSession::setChatSessionInfo_p(ChatSessionInfo *chatSessionInfo)
{
    if (dptr->m_chatSessionInfo.get() != chatSessionInfo) {
        dptr.detach();
        dptr->m_chatSessionInfo.reset(chatSessionInfo);
    }
}

void NotifyNewChatSession::setChatSessionInfo(const ChatSessionInfo &chatSessionInfo)
{
    if (*dptr->m_chatSessionInfo != chatSessionInfo) {
        dptr.detach();
        *dptr->m_chatSessionInfo = chatSessionInfo;
    }
}


class NotifyNewMessage_QtProtobufData : public QSharedData
{
public:
    NotifyNewMessage_QtProtobufData()
        : QSharedData(),
          m_messageInfo(nullptr)
    {
    }

    NotifyNewMessage_QtProtobufData(const NotifyNewMessage_QtProtobufData &other)
        : QSharedData(other),
          m_messageInfo(other.m_messageInfo
                                               ? new MessageInfo(*other.m_messageInfo)
                                               : nullptr)
    {
    }

    QtProtobufPrivate::QProtobufLazyMessagePointer<MessageInfo> m_messageInfo;
};

NotifyNewMessage::~NotifyNewMessage() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 5> qt_protobuf_NotifyNewMessage_uint_data;
    const char qt_protobuf_NotifyNewMessage_char_data[44];
} qt_protobuf_NotifyNewMessage_metadata {
    // data
    {
        0, /* = version */
        1, /* = num fields */
        2, /* = field number offset */
        3, /* = property index offset */
        4, /* = field flags offset */
        30, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        31, /* = messageInfo */
        43, /* = end-of-string-marker */
        // Field numbers:
        1, /* = messageInfo */
        // Property indices:
        0, /* = messageInfo */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = messageInfo */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyNewMessage\0" /* = full message name */
    /* field char_data: */
    "messageInfo\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyNewMessage::propertyOrdering = {
    &qt_protobuf_NotifyNewMessage_metadata.data
};

void NotifyNewMessage::registerTypes()
{
    qRegisterMetaType<NotifyNewMessage>();
    qRegisterMetaType<NotifyNewMessageRepeated>();
}

NotifyNewMessage::NotifyNewMessage()
    : QProtobufMessage(&NotifyNewMessage::staticMetaObject),
      dptr(new NotifyNewMessage_QtProtobufData)
{
}

NotifyNewMessage::NotifyNewMessage(const NotifyNewMessage &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyNewMessage &NotifyNewMessage::operator =(const NotifyNewMessage &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyNewMessage::NotifyNewMessage(NotifyNewMessage &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyNewMessage &NotifyNewMessage::operator =(NotifyNewMessage &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyNewMessage::operator ==(const NotifyNewMessage &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && (dptr->m_messageInfo == other.dptr->m_messageInfo
            || *dptr->m_messageInfo == *other.dptr->m_messageInfo);
}

bool NotifyNewMessage::operator !=(const NotifyNewMessage &other) const
{
    return !this->operator ==(other);
}

MessageInfo *NotifyNewMessage::messageInfo_p() const
{
    return dptr->m_messageInfo ? dptr->m_messageInfo.get() : nullptr;
}

MessageInfo &NotifyNewMessage::messageInfo() const
{
    return *dptr->m_messageInfo;
}

void NotifyNewMessage::setMessageInfo_p(MessageInfo *messageInfo)
{
    if (dptr->m_messageInfo.get() != messageInfo) {
        dptr.detach();
        dptr->m_messageInfo.reset(messageInfo);
    }
}

void NotifyNewMessage::setMessageInfo(const MessageInfo &messageInfo)
{
    if (*dptr->m_messageInfo != messageInfo) {
        dptr.detach();
        *dptr->m_messageInfo = messageInfo;
    }
}


class NotifyMessage_QtProtobufData : public QSharedData
{
public:
    NotifyMessage_QtProtobufData()
        : QSharedData(),
          m_notifyType(NotifyTypeGadget::NotifyType::FRIEND_ADD_APPLY_NOTIFY)
    {
    }

    NotifyMessage_QtProtobufData(const NotifyMessage_QtProtobufData &other)
        : QSharedData(other),
          m_notifyEventId(other.m_notifyEventId),
          m_notifyType(other.m_notifyType),
          m_notify_remarks(other.m_notify_remarks)
    {
    }

    QString m_notifyEventId;
    NotifyTypeGadget::NotifyType m_notifyType;
    QtProtobufPrivate::QProtobufOneof m_notify_remarks;
};

NotifyMessage::~NotifyMessage() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 29> qt_protobuf_NotifyMessage_uint_data;
    const char qt_protobuf_NotifyMessage_char_data[136];
} qt_protobuf_NotifyMessage_metadata {
    // data
    {
        0, /* = version */
        7, /* = num fields */
        8, /* = field number offset */
        15, /* = property index offset */
        22, /* = field flags offset */
        27, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        28, /* = notifyEventId */
        42, /* = notifyType */
        53, /* = friendAddApply */
        68, /* = friendProcessResult */
        88, /* = friendDelete */
        101, /* = newChatSessionInfo */
        120, /* = newMessageInfo */
        135, /* = end-of-string-marker */
        // Field numbers:
        1, /* = notifyEventId */
        2, /* = notifyType */
        3, /* = friendAddApply */
        4, /* = friendProcessResult */
        7, /* = friendDelete */
        5, /* = newChatSessionInfo */
        6, /* = newMessageInfo */
        // Property indices:
        0, /* = notifyEventId */
        1, /* = notifyType */
        2, /* = friendAddApply */
        4, /* = friendProcessResult */
        6, /* = friendDelete */
        8, /* = newChatSessionInfo */
        10, /* = newMessageInfo */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = notifyEventId */
        QtProtobufPrivate::NoFlags, /* = notifyType */
        QtProtobufPrivate::Oneof, /* = friendAddApply */
        QtProtobufPrivate::Oneof, /* = friendProcessResult */
        QtProtobufPrivate::Oneof, /* = friendDelete */
        QtProtobufPrivate::Oneof, /* = newChatSessionInfo */
        QtProtobufPrivate::Oneof, /* = newMessageInfo */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.NotifyMessage\0" /* = full message name */
    /* field char_data: */
    "notifyEventId\0notifyType\0friendAddApply\0friendProcessResult\0friendDelete\0"
    "newChatSessionInfo\0newMessageInfo\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering NotifyMessage::propertyOrdering = {
    &qt_protobuf_NotifyMessage_metadata.data
};

void NotifyMessage::registerTypes()
{
    qRegisterMetaType<NotifyMessage>();
    qRegisterMetaType<NotifyMessageRepeated>();
}

NotifyMessage::NotifyMessage()
    : QProtobufMessage(&NotifyMessage::staticMetaObject),
      dptr(new NotifyMessage_QtProtobufData)
{
}

NotifyMessage::NotifyMessage(const NotifyMessage &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
NotifyMessage &NotifyMessage::operator =(const NotifyMessage &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
NotifyMessage::NotifyMessage(NotifyMessage &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
NotifyMessage &NotifyMessage::operator =(NotifyMessage &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool NotifyMessage::operator ==(const NotifyMessage &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_notifyType == other.dptr->m_notifyType
        && dptr->m_notify_remarks == other.dptr->m_notify_remarks;
}

bool NotifyMessage::operator !=(const NotifyMessage &other) const
{
    return !this->operator ==(other);
}

QString NotifyMessage::notifyEventId() const
{
    return dptr->m_notifyEventId;
}

NotifyTypeGadget::NotifyType NotifyMessage::notifyType() const
{
    return dptr->m_notifyType;
}

NotifyFriendAddApply *NotifyMessage::friendAddApply_p() const
{
    return dptr->m_notify_remarks.holdsField(3) ?
        dptr->m_notify_remarks.value<NotifyFriendAddApply>() : nullptr;
}

bool NotifyMessage::hasFriendAddApply() const
{
    return dptr->m_notify_remarks.holdsField(3);
}
NotifyFriendAddApply &NotifyMessage::friendAddApply() const
{
    Q_ASSERT(dptr->m_notify_remarks.holdsField(3));
    return *(dptr->m_notify_remarks.value<NotifyFriendAddApply>());
}

NotifyFriendAddProcess *NotifyMessage::friendProcessResult_p() const
{
    return dptr->m_notify_remarks.holdsField(4) ?
        dptr->m_notify_remarks.value<NotifyFriendAddProcess>() : nullptr;
}

bool NotifyMessage::hasFriendProcessResult() const
{
    return dptr->m_notify_remarks.holdsField(4);
}
NotifyFriendAddProcess &NotifyMessage::friendProcessResult() const
{
    Q_ASSERT(dptr->m_notify_remarks.holdsField(4));
    return *(dptr->m_notify_remarks.value<NotifyFriendAddProcess>());
}

NotifyFriendDelete *NotifyMessage::friendDelete_p() const
{
    return dptr->m_notify_remarks.holdsField(7) ?
        dptr->m_notify_remarks.value<NotifyFriendDelete>() : nullptr;
}

bool NotifyMessage::hasFriendDelete() const
{
    return dptr->m_notify_remarks.holdsField(7);
}
NotifyFriendDelete &NotifyMessage::friendDelete() const
{
    Q_ASSERT(dptr->m_notify_remarks.holdsField(7));
    return *(dptr->m_notify_remarks.value<NotifyFriendDelete>());
}

NotifyNewChatSession *NotifyMessage::newChatSessionInfo_p() const
{
    return dptr->m_notify_remarks.holdsField(5) ?
        dptr->m_notify_remarks.value<NotifyNewChatSession>() : nullptr;
}

bool NotifyMessage::hasNewChatSessionInfo() const
{
    return dptr->m_notify_remarks.holdsField(5);
}
NotifyNewChatSession &NotifyMessage::newChatSessionInfo() const
{
    Q_ASSERT(dptr->m_notify_remarks.holdsField(5));
    return *(dptr->m_notify_remarks.value<NotifyNewChatSession>());
}

NotifyNewMessage *NotifyMessage::newMessageInfo_p() const
{
    return dptr->m_notify_remarks.holdsField(6) ?
        dptr->m_notify_remarks.value<NotifyNewMessage>() : nullptr;
}

bool NotifyMessage::hasNewMessageInfo() const
{
    return dptr->m_notify_remarks.holdsField(6);
}
NotifyNewMessage &NotifyMessage::newMessageInfo() const
{
    Q_ASSERT(dptr->m_notify_remarks.holdsField(6));
    return *(dptr->m_notify_remarks.value<NotifyNewMessage>());
}

void NotifyMessage::setNotifyEventId(const QString &notifyEventId)
{
    if (dptr->m_notifyEventId != notifyEventId) {
        dptr.detach();
        dptr->m_notifyEventId = notifyEventId;
    }
}

void NotifyMessage::setNotifyType(const NotifyTypeGadget::NotifyType &notifyType)
{
    if (dptr->m_notifyType != notifyType) {
        dptr.detach();
        dptr->m_notifyType = notifyType;
    }
}

void NotifyMessage::setFriendAddApply(const NotifyFriendAddApply &friendAddApply)
{
    if (!dptr->m_notify_remarks.isEqual(friendAddApply, 3)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(friendAddApply, 3);
    }
}

void NotifyMessage::setFriendAddApply_p(NotifyFriendAddApply *friendAddApply)
{
    const NotifyFriendAddApply &value = *friendAddApply;
    if (!dptr->m_notify_remarks.isEqual(value, 3)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(value, 3);
    }
    delete friendAddApply;
}

void NotifyMessage::setFriendProcessResult(const NotifyFriendAddProcess &friendProcessResult)
{
    if (!dptr->m_notify_remarks.isEqual(friendProcessResult, 4)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(friendProcessResult, 4);
    }
}

void NotifyMessage::setFriendProcessResult_p(NotifyFriendAddProcess *friendProcessResult)
{
    const NotifyFriendAddProcess &value = *friendProcessResult;
    if (!dptr->m_notify_remarks.isEqual(value, 4)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(value, 4);
    }
    delete friendProcessResult;
}

void NotifyMessage::setFriendDelete(const NotifyFriendDelete &friendDelete)
{
    if (!dptr->m_notify_remarks.isEqual(friendDelete, 7)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(friendDelete, 7);
    }
}

void NotifyMessage::setFriendDelete_p(NotifyFriendDelete *friendDelete)
{
    const NotifyFriendDelete &value = *friendDelete;
    if (!dptr->m_notify_remarks.isEqual(value, 7)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(value, 7);
    }
    delete friendDelete;
}

void NotifyMessage::setNewChatSessionInfo(const NotifyNewChatSession &newChatSessionInfo)
{
    if (!dptr->m_notify_remarks.isEqual(newChatSessionInfo, 5)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(newChatSessionInfo, 5);
    }
}

void NotifyMessage::setNewChatSessionInfo_p(NotifyNewChatSession *newChatSessionInfo)
{
    const NotifyNewChatSession &value = *newChatSessionInfo;
    if (!dptr->m_notify_remarks.isEqual(value, 5)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(value, 5);
    }
    delete newChatSessionInfo;
}

void NotifyMessage::setNewMessageInfo(const NotifyNewMessage &newMessageInfo)
{
    if (!dptr->m_notify_remarks.isEqual(newMessageInfo, 6)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(newMessageInfo, 6);
    }
}

void NotifyMessage::setNewMessageInfo_p(NotifyNewMessage *newMessageInfo)
{
    const NotifyNewMessage &value = *newMessageInfo;
    if (!dptr->m_notify_remarks.isEqual(value, 6)) {
        dptr.detach();
        dptr->m_notify_remarks.setValue(value, 6);
    }
    delete newMessageInfo;
}

NotifyMessage::Notify_remarksFields NotifyMessage::notify_remarksField() const
{
    return static_cast<Notify_remarksFields>(dptr->m_notify_remarks.fieldNumber());
}
void NotifyMessage::clearNotify_remarks()
{
    if (dptr->m_notify_remarks.fieldNumber() != QtProtobuf::InvalidFieldNumber) {
        dptr.detach();
        dptr->m_notify_remarks = QtProtobufPrivate::QProtobufOneof();
    }
}
} // namespace my_chat_proto

#include "moc_notify.qpb.cpp"
