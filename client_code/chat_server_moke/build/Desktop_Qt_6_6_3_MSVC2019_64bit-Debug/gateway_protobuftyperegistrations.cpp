#include <QtProtobuf/qprotobufserializer.h>
#include "gateway.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarClientAuthenticationReq(qRegisterProtobufType<ClientAuthenticationReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarClientAuthenticationRsp(qRegisterProtobufType<ClientAuthenticationRsp>);
static bool RegisterGatewayProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

