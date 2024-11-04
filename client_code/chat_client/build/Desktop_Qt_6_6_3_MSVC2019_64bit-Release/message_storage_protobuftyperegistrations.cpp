#include <QtProtobuf/qprotobufserializer.h>
#include "message_storage.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMsgSearchByTimeReq(qRegisterProtobufType<MsgSearchByTimeReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMsgSearchByTimeRsp(qRegisterProtobufType<MsgSearchByTimeRsp>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarGetRecentMsgReq(qRegisterProtobufType<GetRecentMsgReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarGetRecentMsgRsp(qRegisterProtobufType<GetRecentMsgRsp>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMsgSearchBySearchKeyReq(qRegisterProtobufType<MsgSearchBySearchKeyReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarMsgSearchBySearchKeyRsp(qRegisterProtobufType<MsgSearchBySearchKeyRsp>);
static bool RegisterMessage_storageProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

