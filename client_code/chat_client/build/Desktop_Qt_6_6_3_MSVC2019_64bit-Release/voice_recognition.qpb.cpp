/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#include "voice_recognition.qpb.h"
#include <QtProtobuf/qprotobufserializer.h>

namespace my_chat_proto {

class VoiceRecognitionReq_QtProtobufData : public QSharedData
{
public:
    VoiceRecognitionReq_QtProtobufData()
        : QSharedData()
    {
    }

    VoiceRecognitionReq_QtProtobufData(const VoiceRecognitionReq_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_voiceContent(other.m_voiceContent),
          m_userId(other.m_userId),
          m_sessionId(other.m_sessionId)
    {
    }

    QString m_requestId;
    QByteArray m_voiceContent;
    QString m_userId;
    QString m_sessionId;
};

VoiceRecognitionReq::~VoiceRecognitionReq() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_VoiceRecognitionReq_uint_data;
    const char qt_protobuf_VoiceRecognitionReq_char_data[75];
} qt_protobuf_VoiceRecognitionReq_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        33, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        34, /* = requestId */
        44, /* = voiceContent */
        57, /* = userId */
        64, /* = sessionId */
        74, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = voiceContent */
        3, /* = userId */
        4, /* = sessionId */
        // Property indices:
        0, /* = requestId */
        1, /* = voiceContent */
        2, /* = userId */
        3, /* = sessionId */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = voiceContent */
        QtProtobufPrivate::NoFlags, /* = userId */
        QtProtobufPrivate::NoFlags, /* = sessionId */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.VoiceRecognitionReq\0" /* = full message name */
    /* field char_data: */
    "requestId\0voiceContent\0userId\0sessionId\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering VoiceRecognitionReq::propertyOrdering = {
    &qt_protobuf_VoiceRecognitionReq_metadata.data
};

void VoiceRecognitionReq::registerTypes()
{
    qRegisterMetaType<VoiceRecognitionReq>();
    qRegisterMetaType<VoiceRecognitionReqRepeated>();
}

VoiceRecognitionReq::VoiceRecognitionReq()
    : QProtobufMessage(&VoiceRecognitionReq::staticMetaObject),
      dptr(new VoiceRecognitionReq_QtProtobufData)
{
}

VoiceRecognitionReq::VoiceRecognitionReq(const VoiceRecognitionReq &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
VoiceRecognitionReq &VoiceRecognitionReq::operator =(const VoiceRecognitionReq &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
VoiceRecognitionReq::VoiceRecognitionReq(VoiceRecognitionReq &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
VoiceRecognitionReq &VoiceRecognitionReq::operator =(VoiceRecognitionReq &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool VoiceRecognitionReq::operator ==(const VoiceRecognitionReq &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_voiceContent == other.dptr->m_voiceContent;
}

bool VoiceRecognitionReq::operator !=(const VoiceRecognitionReq &other) const
{
    return !this->operator ==(other);
}

QString VoiceRecognitionReq::requestId() const
{
    return dptr->m_requestId;
}

QByteArray VoiceRecognitionReq::voiceContent() const
{
    return dptr->m_voiceContent;
}

QString VoiceRecognitionReq::userId() const
{
    return dptr->m_userId;
}

QString VoiceRecognitionReq::sessionId() const
{
    return dptr->m_sessionId;
}

void VoiceRecognitionReq::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void VoiceRecognitionReq::setVoiceContent(const QByteArray &voiceContent)
{
    if (dptr->m_voiceContent != voiceContent) {
        dptr.detach();
        dptr->m_voiceContent = voiceContent;
    }
}

void VoiceRecognitionReq::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}

void VoiceRecognitionReq::setSessionId(const QString &sessionId)
{
    if (dptr->m_sessionId != sessionId) {
        dptr.detach();
        dptr->m_sessionId = sessionId;
    }
}


class VoiceRecognitionRsp_QtProtobufData : public QSharedData
{
public:
    VoiceRecognitionRsp_QtProtobufData()
        : QSharedData(),
          m_success(false)
    {
    }

    VoiceRecognitionRsp_QtProtobufData(const VoiceRecognitionRsp_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_success(other.m_success),
          m_errmsg(other.m_errmsg),
          m_recognitionResult(other.m_recognitionResult)
    {
    }

    QString m_requestId;
    bool m_success;
    QString m_errmsg;
    QString m_recognitionResult;
};

VoiceRecognitionRsp::~VoiceRecognitionRsp() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_VoiceRecognitionRsp_uint_data;
    const char qt_protobuf_VoiceRecognitionRsp_char_data[78];
} qt_protobuf_VoiceRecognitionRsp_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        33, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        34, /* = requestId */
        44, /* = success */
        52, /* = errmsg */
        59, /* = recognitionResult */
        77, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = success */
        3, /* = errmsg */
        4, /* = recognitionResult */
        // Property indices:
        0, /* = requestId */
        1, /* = success */
        2, /* = errmsg */
        3, /* = recognitionResult */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = success */
        QtProtobufPrivate::NoFlags, /* = errmsg */
        QtProtobufPrivate::NoFlags, /* = recognitionResult */
    },
    // char_data
    /* metadata char_data: */
    "my_chat_proto.VoiceRecognitionRsp\0" /* = full message name */
    /* field char_data: */
    "requestId\0success\0errmsg\0recognitionResult\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering VoiceRecognitionRsp::propertyOrdering = {
    &qt_protobuf_VoiceRecognitionRsp_metadata.data
};

void VoiceRecognitionRsp::registerTypes()
{
    qRegisterMetaType<VoiceRecognitionRsp>();
    qRegisterMetaType<VoiceRecognitionRspRepeated>();
}

VoiceRecognitionRsp::VoiceRecognitionRsp()
    : QProtobufMessage(&VoiceRecognitionRsp::staticMetaObject),
      dptr(new VoiceRecognitionRsp_QtProtobufData)
{
}

VoiceRecognitionRsp::VoiceRecognitionRsp(const VoiceRecognitionRsp &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
VoiceRecognitionRsp &VoiceRecognitionRsp::operator =(const VoiceRecognitionRsp &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
VoiceRecognitionRsp::VoiceRecognitionRsp(VoiceRecognitionRsp &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
VoiceRecognitionRsp &VoiceRecognitionRsp::operator =(VoiceRecognitionRsp &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool VoiceRecognitionRsp::operator ==(const VoiceRecognitionRsp &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_success == other.dptr->m_success
        && dptr->m_errmsg == other.dptr->m_errmsg
        && dptr->m_recognitionResult == other.dptr->m_recognitionResult;
}

bool VoiceRecognitionRsp::operator !=(const VoiceRecognitionRsp &other) const
{
    return !this->operator ==(other);
}

QString VoiceRecognitionRsp::requestId() const
{
    return dptr->m_requestId;
}

bool VoiceRecognitionRsp::success() const
{
    return dptr->m_success;
}

QString VoiceRecognitionRsp::errmsg() const
{
    return dptr->m_errmsg;
}

QString VoiceRecognitionRsp::recognitionResult() const
{
    return dptr->m_recognitionResult;
}

void VoiceRecognitionRsp::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void VoiceRecognitionRsp::setSuccess(const bool &success)
{
    if (dptr->m_success != success) {
        dptr.detach();
        dptr->m_success = success;
    }
}

void VoiceRecognitionRsp::setErrmsg(const QString &errmsg)
{
    if (dptr->m_errmsg != errmsg) {
        dptr.detach();
        dptr->m_errmsg = errmsg;
    }
}

void VoiceRecognitionRsp::setRecognitionResult(const QString &recognitionResult)
{
    if (dptr->m_recognitionResult != recognitionResult) {
        dptr.detach();
        dptr->m_recognitionResult = recognitionResult;
    }
}

} // namespace my_chat_proto

#include "moc_voice_recognition.qpb.cpp"
