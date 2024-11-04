#include <QtProtobuf/qprotobufserializer.h>
#include "message_transmit.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNewMessageReq(qRegisterProtobufType<NewMessageReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarNewMessageRsp(qRegisterProtobufType<NewMessageRsp>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarGetTransmitTargetRsp(qRegisterProtobufType<GetTransmitTargetRsp>);
static bool RegisterMessage_transmitProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

