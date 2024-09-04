#include <QtProtobuf/qprotobufserializer.h>
#include "speech_recognition.qpb.h"

namespace my_chat_proto {
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarSpeechRecognitionReq(qRegisterProtobufType<SpeechRecognitionReq>);
static QtProtobuf::ProtoTypeRegistrar ProtoTypeRegistrarSpeechRecognitionRsp(qRegisterProtobufType<SpeechRecognitionRsp>);
static bool RegisterSpeech_recognitionProtobufTypes = [](){ qRegisterProtobufTypes(); return true; }();
} // namespace my_chat_proto

