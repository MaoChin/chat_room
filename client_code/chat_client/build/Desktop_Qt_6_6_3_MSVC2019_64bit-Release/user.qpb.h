/* This file is autogenerated. DO NOT CHANGE. All changes will be lost */

#ifndef QPROTOBUF_USER_H
#define QPROTOBUF_USER_H

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
class UserRegisterReq;
using UserRegisterReqRepeated = QList<UserRegisterReq>;
class UserRegisterRsp;
using UserRegisterRspRepeated = QList<UserRegisterRsp>;
class UserLoginReq;
using UserLoginReqRepeated = QList<UserLoginReq>;
class UserLoginRsp;
using UserLoginRspRepeated = QList<UserLoginRsp>;
class PhoneVerifyCodeReq;
using PhoneVerifyCodeReqRepeated = QList<PhoneVerifyCodeReq>;
class PhoneVerifyCodeRsp;
using PhoneVerifyCodeRspRepeated = QList<PhoneVerifyCodeRsp>;
class PhoneRegisterReq;
using PhoneRegisterReqRepeated = QList<PhoneRegisterReq>;
class PhoneRegisterRsp;
using PhoneRegisterRspRepeated = QList<PhoneRegisterRsp>;
class PhoneLoginReq;
using PhoneLoginReqRepeated = QList<PhoneLoginReq>;
class PhoneLoginRsp;
using PhoneLoginRspRepeated = QList<PhoneLoginRsp>;
class GetUserInfoReq;
using GetUserInfoReqRepeated = QList<GetUserInfoReq>;
class GetUserInfoRsp;
using GetUserInfoRspRepeated = QList<GetUserInfoRsp>;
class SetUserHeadPortraitReq;
using SetUserHeadPortraitReqRepeated = QList<SetUserHeadPortraitReq>;
class SetUserHeadPortraitRsp;
using SetUserHeadPortraitRspRepeated = QList<SetUserHeadPortraitRsp>;
class SetUserNicknameReq;
using SetUserNicknameReqRepeated = QList<SetUserNicknameReq>;
class SetUserNicknameRsp;
using SetUserNicknameRspRepeated = QList<SetUserNicknameRsp>;
class SetUserSignatureReq;
using SetUserSignatureReqRepeated = QList<SetUserSignatureReq>;
class SetUserSignatureRsp;
using SetUserSignatureRspRepeated = QList<SetUserSignatureRsp>;
class SetUserPhoneNumberReq;
using SetUserPhoneNumberReqRepeated = QList<SetUserPhoneNumberReq>;
class SetUserPhoneNumberRsp;
using SetUserPhoneNumberRspRepeated = QList<SetUserPhoneNumberRsp>;

class UserRegisterReq_QtProtobufData;
class UserRegisterReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(UserRegisterReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname SCRIPTABLE true)
    Q_PROPERTY(QString password READ password WRITE setPassword SCRIPTABLE true)
    Q_PROPERTY(QString verifyCodeId READ verifyCodeId WRITE setVerifyCodeId SCRIPTABLE true)
    Q_PROPERTY(QString verifyCode READ verifyCode WRITE setVerifyCode SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        NicknameProtoFieldNumber = 2,
        PasswordProtoFieldNumber = 3,
        VerifyCodeIdProtoFieldNumber = 4,
        VerifyCodeProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    UserRegisterReq();
    ~UserRegisterReq();
    UserRegisterReq(const UserRegisterReq &other);
    UserRegisterReq &operator =(const UserRegisterReq &other);
    UserRegisterReq(UserRegisterReq &&other) noexcept;
    UserRegisterReq &operator =(UserRegisterReq &&other) noexcept;
    bool operator ==(const UserRegisterReq &other) const;
    bool operator !=(const UserRegisterReq &other) const;

    QString requestId() const;

    QString nickname() const;

    QString password() const;

    QString verifyCodeId() const;

    QString verifyCode() const;
    void setRequestId(const QString &requestId);
    void setNickname(const QString &nickname);
    void setPassword(const QString &password);
    void setVerifyCodeId(const QString &verifyCodeId);
    void setVerifyCode(const QString &verifyCode);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<UserRegisterReq_QtProtobufData> dptr;
};

class UserRegisterRsp_QtProtobufData;
class UserRegisterRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(UserRegisterRsp)
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

    UserRegisterRsp();
    ~UserRegisterRsp();
    UserRegisterRsp(const UserRegisterRsp &other);
    UserRegisterRsp &operator =(const UserRegisterRsp &other);
    UserRegisterRsp(UserRegisterRsp &&other) noexcept;
    UserRegisterRsp &operator =(UserRegisterRsp &&other) noexcept;
    bool operator ==(const UserRegisterRsp &other) const;
    bool operator !=(const UserRegisterRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<UserRegisterRsp_QtProtobufData> dptr;
};

class UserLoginReq_QtProtobufData;
class UserLoginReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(UserLoginReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname SCRIPTABLE true)
    Q_PROPERTY(QString password READ password WRITE setPassword SCRIPTABLE true)
    Q_PROPERTY(QString verifyCodeId READ verifyCodeId WRITE setVerifyCodeId SCRIPTABLE true)
    Q_PROPERTY(QString verifyCode READ verifyCode WRITE setVerifyCode SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        NicknameProtoFieldNumber = 2,
        PasswordProtoFieldNumber = 3,
        VerifyCodeIdProtoFieldNumber = 4,
        VerifyCodeProtoFieldNumber = 5,
    };
    Q_ENUM(QtProtobufFieldEnum)

    UserLoginReq();
    ~UserLoginReq();
    UserLoginReq(const UserLoginReq &other);
    UserLoginReq &operator =(const UserLoginReq &other);
    UserLoginReq(UserLoginReq &&other) noexcept;
    UserLoginReq &operator =(UserLoginReq &&other) noexcept;
    bool operator ==(const UserLoginReq &other) const;
    bool operator !=(const UserLoginReq &other) const;

    QString requestId() const;

    QString nickname() const;

    QString password() const;

    QString verifyCodeId() const;

    QString verifyCode() const;
    void setRequestId(const QString &requestId);
    void setNickname(const QString &nickname);
    void setPassword(const QString &password);
    void setVerifyCodeId(const QString &verifyCodeId);
    void setVerifyCode(const QString &verifyCode);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<UserLoginReq_QtProtobufData> dptr;
};

class UserLoginRsp_QtProtobufData;
class UserLoginRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(UserLoginRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(QString loginSessionId READ loginSessionId WRITE setLoginSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        LoginSessionIdProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    UserLoginRsp();
    ~UserLoginRsp();
    UserLoginRsp(const UserLoginRsp &other);
    UserLoginRsp &operator =(const UserLoginRsp &other);
    UserLoginRsp(UserLoginRsp &&other) noexcept;
    UserLoginRsp &operator =(UserLoginRsp &&other) noexcept;
    bool operator ==(const UserLoginRsp &other) const;
    bool operator !=(const UserLoginRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    QString loginSessionId() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setLoginSessionId(const QString &loginSessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<UserLoginRsp_QtProtobufData> dptr;
};

class PhoneVerifyCodeReq_QtProtobufData;
class PhoneVerifyCodeReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneVerifyCodeReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        PhoneNumberProtoFieldNumber = 2,
    };
    Q_ENUM(QtProtobufFieldEnum)

    PhoneVerifyCodeReq();
    ~PhoneVerifyCodeReq();
    PhoneVerifyCodeReq(const PhoneVerifyCodeReq &other);
    PhoneVerifyCodeReq &operator =(const PhoneVerifyCodeReq &other);
    PhoneVerifyCodeReq(PhoneVerifyCodeReq &&other) noexcept;
    PhoneVerifyCodeReq &operator =(PhoneVerifyCodeReq &&other) noexcept;
    bool operator ==(const PhoneVerifyCodeReq &other) const;
    bool operator !=(const PhoneVerifyCodeReq &other) const;

    QString requestId() const;

    QString phoneNumber() const;
    void setRequestId(const QString &requestId);
    void setPhoneNumber(const QString &phoneNumber);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneVerifyCodeReq_QtProtobufData> dptr;
};

class PhoneVerifyCodeRsp_QtProtobufData;
class PhoneVerifyCodeRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneVerifyCodeRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(QString verifyCodeId READ verifyCodeId WRITE setVerifyCodeId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        VerifyCodeIdProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    PhoneVerifyCodeRsp();
    ~PhoneVerifyCodeRsp();
    PhoneVerifyCodeRsp(const PhoneVerifyCodeRsp &other);
    PhoneVerifyCodeRsp &operator =(const PhoneVerifyCodeRsp &other);
    PhoneVerifyCodeRsp(PhoneVerifyCodeRsp &&other) noexcept;
    PhoneVerifyCodeRsp &operator =(PhoneVerifyCodeRsp &&other) noexcept;
    bool operator ==(const PhoneVerifyCodeRsp &other) const;
    bool operator !=(const PhoneVerifyCodeRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    QString verifyCodeId() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setVerifyCodeId(const QString &verifyCodeId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneVerifyCodeRsp_QtProtobufData> dptr;
};

class PhoneRegisterReq_QtProtobufData;
class PhoneRegisterReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneRegisterReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber SCRIPTABLE true)
    Q_PROPERTY(QString verifyCodeId READ verifyCodeId WRITE setVerifyCodeId SCRIPTABLE true)
    Q_PROPERTY(QString verifyCode READ verifyCode WRITE setVerifyCode SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        PhoneNumberProtoFieldNumber = 2,
        VerifyCodeIdProtoFieldNumber = 3,
        VerifyCodeProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    PhoneRegisterReq();
    ~PhoneRegisterReq();
    PhoneRegisterReq(const PhoneRegisterReq &other);
    PhoneRegisterReq &operator =(const PhoneRegisterReq &other);
    PhoneRegisterReq(PhoneRegisterReq &&other) noexcept;
    PhoneRegisterReq &operator =(PhoneRegisterReq &&other) noexcept;
    bool operator ==(const PhoneRegisterReq &other) const;
    bool operator !=(const PhoneRegisterReq &other) const;

    QString requestId() const;

    QString phoneNumber() const;

    QString verifyCodeId() const;

    QString verifyCode() const;
    void setRequestId(const QString &requestId);
    void setPhoneNumber(const QString &phoneNumber);
    void setVerifyCodeId(const QString &verifyCodeId);
    void setVerifyCode(const QString &verifyCode);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneRegisterReq_QtProtobufData> dptr;
};

class PhoneRegisterRsp_QtProtobufData;
class PhoneRegisterRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneRegisterRsp)
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

    PhoneRegisterRsp();
    ~PhoneRegisterRsp();
    PhoneRegisterRsp(const PhoneRegisterRsp &other);
    PhoneRegisterRsp &operator =(const PhoneRegisterRsp &other);
    PhoneRegisterRsp(PhoneRegisterRsp &&other) noexcept;
    PhoneRegisterRsp &operator =(PhoneRegisterRsp &&other) noexcept;
    bool operator ==(const PhoneRegisterRsp &other) const;
    bool operator !=(const PhoneRegisterRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneRegisterRsp_QtProtobufData> dptr;
};

class PhoneLoginReq_QtProtobufData;
class PhoneLoginReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneLoginReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber SCRIPTABLE true)
    Q_PROPERTY(QString verifyCodeId READ verifyCodeId WRITE setVerifyCodeId SCRIPTABLE true)
    Q_PROPERTY(QString verifyCode READ verifyCode WRITE setVerifyCode SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        PhoneNumberProtoFieldNumber = 2,
        VerifyCodeIdProtoFieldNumber = 3,
        VerifyCodeProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    PhoneLoginReq();
    ~PhoneLoginReq();
    PhoneLoginReq(const PhoneLoginReq &other);
    PhoneLoginReq &operator =(const PhoneLoginReq &other);
    PhoneLoginReq(PhoneLoginReq &&other) noexcept;
    PhoneLoginReq &operator =(PhoneLoginReq &&other) noexcept;
    bool operator ==(const PhoneLoginReq &other) const;
    bool operator !=(const PhoneLoginReq &other) const;

    QString requestId() const;

    QString phoneNumber() const;

    QString verifyCodeId() const;

    QString verifyCode() const;
    void setRequestId(const QString &requestId);
    void setPhoneNumber(const QString &phoneNumber);
    void setVerifyCodeId(const QString &verifyCodeId);
    void setVerifyCode(const QString &verifyCode);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneLoginReq_QtProtobufData> dptr;
};

class PhoneLoginRsp_QtProtobufData;
class PhoneLoginRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(PhoneLoginRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(QString loginSessionId READ loginSessionId WRITE setLoginSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        LoginSessionIdProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    PhoneLoginRsp();
    ~PhoneLoginRsp();
    PhoneLoginRsp(const PhoneLoginRsp &other);
    PhoneLoginRsp &operator =(const PhoneLoginRsp &other);
    PhoneLoginRsp(PhoneLoginRsp &&other) noexcept;
    PhoneLoginRsp &operator =(PhoneLoginRsp &&other) noexcept;
    bool operator ==(const PhoneLoginRsp &other) const;
    bool operator !=(const PhoneLoginRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    QString loginSessionId() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setLoginSessionId(const QString &loginSessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<PhoneLoginRsp_QtProtobufData> dptr;
};

class GetUserInfoReq_QtProtobufData;
class GetUserInfoReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetUserInfoReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetUserInfoReq();
    ~GetUserInfoReq();
    GetUserInfoReq(const GetUserInfoReq &other);
    GetUserInfoReq &operator =(const GetUserInfoReq &other);
    GetUserInfoReq(GetUserInfoReq &&other) noexcept;
    GetUserInfoReq &operator =(GetUserInfoReq &&other) noexcept;
    bool operator ==(const GetUserInfoReq &other) const;
    bool operator !=(const GetUserInfoReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<GetUserInfoReq_QtProtobufData> dptr;
};

class GetUserInfoRsp_QtProtobufData;
class GetUserInfoRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(GetUserInfoRsp)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(bool success READ success WRITE setSuccess SCRIPTABLE true)
    Q_PROPERTY(QString errmsg READ errmsg WRITE setErrmsg SCRIPTABLE true)
    Q_PROPERTY(my_chat_proto::UserInfo *userInfo_p READ userInfo_p WRITE setUserInfo_p SCRIPTABLE false)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        SuccessProtoFieldNumber = 2,
        ErrmsgProtoFieldNumber = 3,
        UserInfoProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    GetUserInfoRsp();
    ~GetUserInfoRsp();
    GetUserInfoRsp(const GetUserInfoRsp &other);
    GetUserInfoRsp &operator =(const GetUserInfoRsp &other);
    GetUserInfoRsp(GetUserInfoRsp &&other) noexcept;
    GetUserInfoRsp &operator =(GetUserInfoRsp &&other) noexcept;
    bool operator ==(const GetUserInfoRsp &other) const;
    bool operator !=(const GetUserInfoRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;

    UserInfo &userInfo() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    void setUserInfo(const UserInfo &userInfo);
    static void registerTypes();

private:
    UserInfo *userInfo_p() const;
    void setUserInfo_p(UserInfo *userInfo);
    QExplicitlySharedDataPointer<GetUserInfoRsp_QtProtobufData> dptr;
};

class SetUserHeadPortraitReq_QtProtobufData;
class SetUserHeadPortraitReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserHeadPortraitReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QByteArray headPortrait READ headPortrait WRITE setHeadPortrait SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        HeadPortraitProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    SetUserHeadPortraitReq();
    ~SetUserHeadPortraitReq();
    SetUserHeadPortraitReq(const SetUserHeadPortraitReq &other);
    SetUserHeadPortraitReq &operator =(const SetUserHeadPortraitReq &other);
    SetUserHeadPortraitReq(SetUserHeadPortraitReq &&other) noexcept;
    SetUserHeadPortraitReq &operator =(SetUserHeadPortraitReq &&other) noexcept;
    bool operator ==(const SetUserHeadPortraitReq &other) const;
    bool operator !=(const SetUserHeadPortraitReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QByteArray headPortrait() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setHeadPortrait(const QByteArray &headPortrait);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserHeadPortraitReq_QtProtobufData> dptr;
};

class SetUserHeadPortraitRsp_QtProtobufData;
class SetUserHeadPortraitRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserHeadPortraitRsp)
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

    SetUserHeadPortraitRsp();
    ~SetUserHeadPortraitRsp();
    SetUserHeadPortraitRsp(const SetUserHeadPortraitRsp &other);
    SetUserHeadPortraitRsp &operator =(const SetUserHeadPortraitRsp &other);
    SetUserHeadPortraitRsp(SetUserHeadPortraitRsp &&other) noexcept;
    SetUserHeadPortraitRsp &operator =(SetUserHeadPortraitRsp &&other) noexcept;
    bool operator ==(const SetUserHeadPortraitRsp &other) const;
    bool operator !=(const SetUserHeadPortraitRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserHeadPortraitRsp_QtProtobufData> dptr;
};

class SetUserNicknameReq_QtProtobufData;
class SetUserNicknameReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserNicknameReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        NicknameProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    SetUserNicknameReq();
    ~SetUserNicknameReq();
    SetUserNicknameReq(const SetUserNicknameReq &other);
    SetUserNicknameReq &operator =(const SetUserNicknameReq &other);
    SetUserNicknameReq(SetUserNicknameReq &&other) noexcept;
    SetUserNicknameReq &operator =(SetUserNicknameReq &&other) noexcept;
    bool operator ==(const SetUserNicknameReq &other) const;
    bool operator !=(const SetUserNicknameReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QString nickname() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setNickname(const QString &nickname);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserNicknameReq_QtProtobufData> dptr;
};

class SetUserNicknameRsp_QtProtobufData;
class SetUserNicknameRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserNicknameRsp)
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

    SetUserNicknameRsp();
    ~SetUserNicknameRsp();
    SetUserNicknameRsp(const SetUserNicknameRsp &other);
    SetUserNicknameRsp &operator =(const SetUserNicknameRsp &other);
    SetUserNicknameRsp(SetUserNicknameRsp &&other) noexcept;
    SetUserNicknameRsp &operator =(SetUserNicknameRsp &&other) noexcept;
    bool operator ==(const SetUserNicknameRsp &other) const;
    bool operator !=(const SetUserNicknameRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserNicknameRsp_QtProtobufData> dptr;
};

class SetUserSignatureReq_QtProtobufData;
class SetUserSignatureReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserSignatureReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QString signature READ signature WRITE setSignature SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        SignatureProtoFieldNumber = 4,
    };
    Q_ENUM(QtProtobufFieldEnum)

    SetUserSignatureReq();
    ~SetUserSignatureReq();
    SetUserSignatureReq(const SetUserSignatureReq &other);
    SetUserSignatureReq &operator =(const SetUserSignatureReq &other);
    SetUserSignatureReq(SetUserSignatureReq &&other) noexcept;
    SetUserSignatureReq &operator =(SetUserSignatureReq &&other) noexcept;
    bool operator ==(const SetUserSignatureReq &other) const;
    bool operator !=(const SetUserSignatureReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QString signature() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setSignature(const QString &signature);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserSignatureReq_QtProtobufData> dptr;
};

class SetUserSignatureRsp_QtProtobufData;
class SetUserSignatureRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserSignatureRsp)
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

    SetUserSignatureRsp();
    ~SetUserSignatureRsp();
    SetUserSignatureRsp(const SetUserSignatureRsp &other);
    SetUserSignatureRsp &operator =(const SetUserSignatureRsp &other);
    SetUserSignatureRsp(SetUserSignatureRsp &&other) noexcept;
    SetUserSignatureRsp &operator =(SetUserSignatureRsp &&other) noexcept;
    bool operator ==(const SetUserSignatureRsp &other) const;
    bool operator !=(const SetUserSignatureRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserSignatureRsp_QtProtobufData> dptr;
};

class SetUserPhoneNumberReq_QtProtobufData;
class SetUserPhoneNumberReq : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserPhoneNumberReq)
    Q_PROPERTY(QString requestId READ requestId WRITE setRequestId SCRIPTABLE true)
    Q_PROPERTY(QString userId READ userId WRITE setUserId SCRIPTABLE true)
    Q_PROPERTY(QString sessionId READ sessionId WRITE setSessionId SCRIPTABLE true)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber SCRIPTABLE true)
    Q_PROPERTY(QString phoneVerifyCodeId READ phoneVerifyCodeId WRITE setPhoneVerifyCodeId SCRIPTABLE true)
    Q_PROPERTY(QString phoneVerifyCode READ phoneVerifyCode WRITE setPhoneVerifyCode SCRIPTABLE true)

public:
    enum QtProtobufFieldEnum {
        RequestIdProtoFieldNumber = 1,
        UserIdProtoFieldNumber = 2,
        SessionIdProtoFieldNumber = 3,
        PhoneNumberProtoFieldNumber = 4,
        PhoneVerifyCodeIdProtoFieldNumber = 5,
        PhoneVerifyCodeProtoFieldNumber = 6,
    };
    Q_ENUM(QtProtobufFieldEnum)

    SetUserPhoneNumberReq();
    ~SetUserPhoneNumberReq();
    SetUserPhoneNumberReq(const SetUserPhoneNumberReq &other);
    SetUserPhoneNumberReq &operator =(const SetUserPhoneNumberReq &other);
    SetUserPhoneNumberReq(SetUserPhoneNumberReq &&other) noexcept;
    SetUserPhoneNumberReq &operator =(SetUserPhoneNumberReq &&other) noexcept;
    bool operator ==(const SetUserPhoneNumberReq &other) const;
    bool operator !=(const SetUserPhoneNumberReq &other) const;

    QString requestId() const;

    QString userId() const;

    QString sessionId() const;

    QString phoneNumber() const;

    QString phoneVerifyCodeId() const;

    QString phoneVerifyCode() const;
    void setRequestId(const QString &requestId);
    void setUserId(const QString &userId);
    void setSessionId(const QString &sessionId);
    void setPhoneNumber(const QString &phoneNumber);
    void setPhoneVerifyCodeId(const QString &phoneVerifyCodeId);
    void setPhoneVerifyCode(const QString &phoneVerifyCode);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserPhoneNumberReq_QtProtobufData> dptr;
};

class SetUserPhoneNumberRsp_QtProtobufData;
class SetUserPhoneNumberRsp : public QProtobufMessage
{
    Q_GADGET
    Q_PROTOBUF_OBJECT
    Q_DECLARE_PROTOBUF_SERIALIZERS(SetUserPhoneNumberRsp)
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

    SetUserPhoneNumberRsp();
    ~SetUserPhoneNumberRsp();
    SetUserPhoneNumberRsp(const SetUserPhoneNumberRsp &other);
    SetUserPhoneNumberRsp &operator =(const SetUserPhoneNumberRsp &other);
    SetUserPhoneNumberRsp(SetUserPhoneNumberRsp &&other) noexcept;
    SetUserPhoneNumberRsp &operator =(SetUserPhoneNumberRsp &&other) noexcept;
    bool operator ==(const SetUserPhoneNumberRsp &other) const;
    bool operator !=(const SetUserPhoneNumberRsp &other) const;

    QString requestId() const;

    bool success() const;

    QString errmsg() const;
    void setRequestId(const QString &requestId);
    void setSuccess(const bool &success);
    void setErrmsg(const QString &errmsg);
    static void registerTypes();

private:
    QExplicitlySharedDataPointer<SetUserPhoneNumberRsp_QtProtobufData> dptr;
};
} // namespace my_chat_proto

Q_DECLARE_METATYPE(my_chat_proto::UserRegisterReq)
Q_DECLARE_METATYPE(my_chat_proto::UserRegisterRsp)
Q_DECLARE_METATYPE(my_chat_proto::UserLoginReq)
Q_DECLARE_METATYPE(my_chat_proto::UserLoginRsp)
Q_DECLARE_METATYPE(my_chat_proto::PhoneVerifyCodeReq)
Q_DECLARE_METATYPE(my_chat_proto::PhoneVerifyCodeRsp)
Q_DECLARE_METATYPE(my_chat_proto::PhoneRegisterReq)
Q_DECLARE_METATYPE(my_chat_proto::PhoneRegisterRsp)
Q_DECLARE_METATYPE(my_chat_proto::PhoneLoginReq)
Q_DECLARE_METATYPE(my_chat_proto::PhoneLoginRsp)
Q_DECLARE_METATYPE(my_chat_proto::GetUserInfoReq)
Q_DECLARE_METATYPE(my_chat_proto::GetUserInfoRsp)
Q_DECLARE_METATYPE(my_chat_proto::SetUserHeadPortraitReq)
Q_DECLARE_METATYPE(my_chat_proto::SetUserHeadPortraitRsp)
Q_DECLARE_METATYPE(my_chat_proto::SetUserNicknameReq)
Q_DECLARE_METATYPE(my_chat_proto::SetUserNicknameRsp)
Q_DECLARE_METATYPE(my_chat_proto::SetUserSignatureReq)
Q_DECLARE_METATYPE(my_chat_proto::SetUserSignatureRsp)
Q_DECLARE_METATYPE(my_chat_proto::SetUserPhoneNumberReq)
Q_DECLARE_METATYPE(my_chat_proto::SetUserPhoneNumberRsp)
#endif // QPROTOBUF_USER_H
