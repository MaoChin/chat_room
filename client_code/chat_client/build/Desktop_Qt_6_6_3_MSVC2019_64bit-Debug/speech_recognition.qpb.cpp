/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#include "speech_recognition.qpb.h"
#include <QtProtobuf/qprotobufserializer.h>

namespace bite_im {

class SpeechRecognitionReq_QtProtobufData : public QSharedData
{
public:
    SpeechRecognitionReq_QtProtobufData()
        : QSharedData()
    {
    }

    SpeechRecognitionReq_QtProtobufData(const SpeechRecognitionReq_QtProtobufData &other)
        : QSharedData(other),
          m_requestId(other.m_requestId),
          m_speechContent(other.m_speechContent),
          m_userId(other.m_userId),
          m_sessionId(other.m_sessionId)
    {
    }

    QString m_requestId;
    QByteArray m_speechContent;
    QString m_userId;
    QString m_sessionId;
};

SpeechRecognitionReq::~SpeechRecognitionReq() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_SpeechRecognitionReq_uint_data;
    const char qt_protobuf_SpeechRecognitionReq_char_data[71];
} qt_protobuf_SpeechRecognitionReq_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        28, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        29, /* = requestId */
        39, /* = speechContent */
        53, /* = userId */
        60, /* = sessionId */
        70, /* = end-of-string-marker */
        // Field numbers:
        1, /* = requestId */
        2, /* = speechContent */
        3, /* = userId */
        4, /* = sessionId */
        // Property indices:
        0, /* = requestId */
        1, /* = speechContent */
        2, /* = userId */
        3, /* = sessionId */
        // Field flags:
        QtProtobufPrivate::NoFlags, /* = requestId */
        QtProtobufPrivate::NoFlags, /* = speechContent */
        QtProtobufPrivate::NoFlags, /* = userId */
        QtProtobufPrivate::NoFlags, /* = sessionId */
    },
    // char_data
    /* metadata char_data: */
    "bite_im.SpeechRecognitionReq\0" /* = full message name */
    /* field char_data: */
    "requestId\0speechContent\0userId\0sessionId\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering SpeechRecognitionReq::propertyOrdering = {
    &qt_protobuf_SpeechRecognitionReq_metadata.data
};

void SpeechRecognitionReq::registerTypes()
{
    qRegisterMetaType<SpeechRecognitionReq>();
    qRegisterMetaType<SpeechRecognitionReqRepeated>();
}

SpeechRecognitionReq::SpeechRecognitionReq()
    : QProtobufMessage(&SpeechRecognitionReq::staticMetaObject),
      dptr(new SpeechRecognitionReq_QtProtobufData)
{
}

SpeechRecognitionReq::SpeechRecognitionReq(const SpeechRecognitionReq &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
SpeechRecognitionReq &SpeechRecognitionReq::operator =(const SpeechRecognitionReq &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
SpeechRecognitionReq::SpeechRecognitionReq(SpeechRecognitionReq &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
SpeechRecognitionReq &SpeechRecognitionReq::operator =(SpeechRecognitionReq &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool SpeechRecognitionReq::operator ==(const SpeechRecognitionReq &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_speechContent == other.dptr->m_speechContent;
}

bool SpeechRecognitionReq::operator !=(const SpeechRecognitionReq &other) const
{
    return !this->operator ==(other);
}

QString SpeechRecognitionReq::requestId() const
{
    return dptr->m_requestId;
}

QByteArray SpeechRecognitionReq::speechContent() const
{
    return dptr->m_speechContent;
}

QString SpeechRecognitionReq::userId() const
{
    return dptr->m_userId;
}

QString SpeechRecognitionReq::sessionId() const
{
    return dptr->m_sessionId;
}

void SpeechRecognitionReq::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void SpeechRecognitionReq::setSpeechContent(const QByteArray &speechContent)
{
    if (dptr->m_speechContent != speechContent) {
        dptr.detach();
        dptr->m_speechContent = speechContent;
    }
}

void SpeechRecognitionReq::setUserId(const QString &userId)
{
    if (dptr->m_userId != userId) {
        dptr.detach();
        dptr->m_userId = userId;
    }
}

void SpeechRecognitionReq::setSessionId(const QString &sessionId)
{
    if (dptr->m_sessionId != sessionId) {
        dptr.detach();
        dptr->m_sessionId = sessionId;
    }
}


class SpeechRecognitionRsp_QtProtobufData : public QSharedData
{
public:
    SpeechRecognitionRsp_QtProtobufData()
        : QSharedData(),
          m_success(false)
    {
    }

    SpeechRecognitionRsp_QtProtobufData(const SpeechRecognitionRsp_QtProtobufData &other)
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

SpeechRecognitionRsp::~SpeechRecognitionRsp() = default;

static constexpr struct {
    QtProtobufPrivate::QProtobufPropertyOrdering::Data data;
    const std::array<uint, 17> qt_protobuf_SpeechRecognitionRsp_uint_data;
    const char qt_protobuf_SpeechRecognitionRsp_char_data[73];
} qt_protobuf_SpeechRecognitionRsp_metadata {
    // data
    {
        0, /* = version */
        4, /* = num fields */
        5, /* = field number offset */
        9, /* = property index offset */
        13, /* = field flags offset */
        28, /* = message full name length */
    },
    // uint_data
    {
        // JSON name offsets:
        29, /* = requestId */
        39, /* = success */
        47, /* = errmsg */
        54, /* = recognitionResult */
        72, /* = end-of-string-marker */
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
    "bite_im.SpeechRecognitionRsp\0" /* = full message name */
    /* field char_data: */
    "requestId\0success\0errmsg\0recognitionResult\0"
};

const QtProtobufPrivate::QProtobufPropertyOrdering SpeechRecognitionRsp::propertyOrdering = {
    &qt_protobuf_SpeechRecognitionRsp_metadata.data
};

void SpeechRecognitionRsp::registerTypes()
{
    qRegisterMetaType<SpeechRecognitionRsp>();
    qRegisterMetaType<SpeechRecognitionRspRepeated>();
}

SpeechRecognitionRsp::SpeechRecognitionRsp()
    : QProtobufMessage(&SpeechRecognitionRsp::staticMetaObject),
      dptr(new SpeechRecognitionRsp_QtProtobufData)
{
}

SpeechRecognitionRsp::SpeechRecognitionRsp(const SpeechRecognitionRsp &other)
    : QProtobufMessage(other),
      dptr(other.dptr)
{
}
SpeechRecognitionRsp &SpeechRecognitionRsp::operator =(const SpeechRecognitionRsp &other)
{
    QProtobufMessage::operator=(other);
    dptr = other.dptr;
    return *this;
}
SpeechRecognitionRsp::SpeechRecognitionRsp(SpeechRecognitionRsp &&other) noexcept
    : QProtobufMessage(std::move(other)),
      dptr(std::move(other.dptr))
{
}
SpeechRecognitionRsp &SpeechRecognitionRsp::operator =(SpeechRecognitionRsp &&other) noexcept
{
    QProtobufMessage::operator=(std::move(other));
    dptr.swap(other.dptr);
    return *this;
}
bool SpeechRecognitionRsp::operator ==(const SpeechRecognitionRsp &other) const
{
    return QProtobufMessage::isEqual(*this, other)
        && dptr->m_requestId == other.dptr->m_requestId
        && dptr->m_success == other.dptr->m_success
        && dptr->m_errmsg == other.dptr->m_errmsg
        && dptr->m_recognitionResult == other.dptr->m_recognitionResult;
}

bool SpeechRecognitionRsp::operator !=(const SpeechRecognitionRsp &other) const
{
    return !this->operator ==(other);
}

QString SpeechRecognitionRsp::requestId() const
{
    return dptr->m_requestId;
}

bool SpeechRecognitionRsp::success() const
{
    return dptr->m_success;
}

QString SpeechRecognitionRsp::errmsg() const
{
    return dptr->m_errmsg;
}

QString SpeechRecognitionRsp::recognitionResult() const
{
    return dptr->m_recognitionResult;
}

void SpeechRecognitionRsp::setRequestId(const QString &requestId)
{
    if (dptr->m_requestId != requestId) {
        dptr.detach();
        dptr->m_requestId = requestId;
    }
}

void SpeechRecognitionRsp::setSuccess(const bool &success)
{
    if (dptr->m_success != success) {
        dptr.detach();
        dptr->m_success = success;
    }
}

void SpeechRecognitionRsp::setErrmsg(const QString &errmsg)
{
    if (dptr->m_errmsg != errmsg) {
        dptr.detach();
        dptr->m_errmsg = errmsg;
    }
}

void SpeechRecognitionRsp::setRecognitionResult(const QString &recognitionResult)
{
    if (dptr->m_recognitionResult != recognitionResult) {
        dptr.detach();
        dptr->m_recognitionResult = recognitionResult;
    }
}

} // namespace bite_im

#include "moc_speech_recognition.qpb.cpp"
