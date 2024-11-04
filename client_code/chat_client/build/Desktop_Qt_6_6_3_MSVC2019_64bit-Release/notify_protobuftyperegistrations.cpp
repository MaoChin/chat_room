#include <QtProtobuf/qprotobufserializer.h>
#include "notify.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyFriendAddApply(qRegisterProtobufType<NotifyFriendAddApply>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyFriendAddProcess(qRegisterProtobufType<NotifyFriendAddProcess>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyFriendDelete(qRegisterProtobufType<NotifyFriendDelete>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyNewChatSession(qRegisterProtobufType<NotifyNewChatSession>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyNewMessage(qRegisterProtobufType<NotifyNewMessage>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNotifyMessage(qRegisterProtobufType<NotifyMessage>);
static bool RegisterNotifyProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

