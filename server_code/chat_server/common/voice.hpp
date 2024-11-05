#pragma once
#include "aip-cpp-sdk/speech.h"
#include "logger.hpp"

// 调用百度SDK进行语音识别
namespace my_chat
{
  class ASRClient
  {
  public:
    using ptr = std::shared_ptr<ASRClient>;
    ASRClient(const std::string &app_id, const std::string &api_key,
              const std::string &secret_key) : _client(app_id, api_key, secret_key) {}
    std::string recognize(const std::string &voice_data, std::string &err)
    {
      Json::Value result = _client.recognize(voice_data, "pcm", 16000, aip::null);
      if (result["err_no"].asInt() != 0)
      {
        LOG_ERROR("语音识别失败：{}", result["err_msg"].asString());
        err = result["err_msg"].asString();
        return std::string();
      }
      return result["result"][0].asString();
    }

  private:
    aip::Speech _client;
  };
} // end of namespace my_chat