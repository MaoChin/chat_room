#include <QtProtobuf/qprotobufserializer.h>
#include "base.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarUserInfo(qRegisterProtobufType<UserInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarChatSessionInfo(qRegisterProtobufType<ChatSessionInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarTextMessageInfo(qRegisterProtobufType<TextMessageInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarImageMessageInfo(qRegisterProtobufType<ImageMessageInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarFileMessageInfo(qRegisterProtobufType<FileMessageInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarVoiceMessageInfo(qRegisterProtobufType<VoiceMessageInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMessageContent(qRegisterProtobufType<MessageContent>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMessageInfo(qRegisterProtobufType<MessageInfo>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMessage(qRegisterProtobufType<Message>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarFileDownloadData(qRegisterProtobufType<FileDownloadData>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarFileUploadData(qRegisterProtobufType<FileUploadData>);
static bool RegisterBaseProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

