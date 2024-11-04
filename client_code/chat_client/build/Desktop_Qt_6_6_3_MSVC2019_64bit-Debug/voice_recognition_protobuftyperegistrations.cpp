#include <QtProtobuf/qprotobufserializer.h>
#include "voice_recognition.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarVoiceRecognitionReq(qRegisterProtobufType<VoiceRecognitionReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarVoiceRecognitionRsp(qRegisterProtobufType<VoiceRecognitionRsp>);
static bool RegisterVoice_recognitionProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

