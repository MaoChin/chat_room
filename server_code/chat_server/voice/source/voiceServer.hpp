#include <brpc/server.h>
#include <butil/logging.h>

#include "voice.hpp"              // 语音识别模块封装
#include "etcd.hpp"               // 服务注册模块封装
#include "logger.hpp"             // 日志模块封装
#include "voice_recognition.pb.h" // protobuf框架代码

// 实现语音识别子服务
namespace my_chat
{
  class VoiceServiceImpl : public my_chat::VoiceService
  {
  public:
    VoiceServiceImpl(const ASRClient::ptr &asr_client) : _asr_client(asr_client) {}
    ~VoiceServiceImpl() {}

    void VoiceRecognition(google::protobuf::RpcController *controller,
                           const ::my_chat::VoiceRecognitionReq *request,
                           ::my_chat::VoiceRecognitionRsp *response,
                           ::google::protobuf::Closure *done)
    {
      LOG_DEBUG("收到语音转文字请求！");
      brpc::ClosureGuard rpc_guard(done);
      // 1. 取出请求中的语音数据
      // 2. 调用语音sdk模块进行语音识别，得到响应
      std::string err;
      std::string res = _asr_client->recognize(request->voice_content(), err);
      if (res.empty())
      {
        LOG_ERROR("{} 语音识别失败！", request->request_id());
        response->set_request_id(request->request_id());
        response->set_success(false);
        response->set_errmsg("语音识别失败:" + err);
        return;
      }
      // 3. 组织响应
      response->set_request_id(request->request_id());
      response->set_success(true);
      response->set_recognition_result(res);
    }

  private:
    ASRClient::ptr _asr_client;
  };

  class VoiceServer
  {
  public:
    using ptr = std::shared_ptr<VoiceServer>;
    VoiceServer(const ASRClient::ptr asr_client,
                 const Registry::ptr &reg_client,
                 const std::shared_ptr<brpc::Server> &server) : _asr_client(asr_client),
                                                                _reg_client(reg_client),
                                                                _rpc_server(server) {}
    ~VoiceServer() {}
    // 搭建RPC服务器，并启动服务器
    void start()
    {
      _rpc_server->RunUntilAskedToQuit();
    }

  private:
    ASRClient::ptr _asr_client;
    Registry::ptr _reg_client;
    std::shared_ptr<brpc::Server> _rpc_server;
  };

  // 有点类似工厂！
  class VoiceServerBuilder
  {
  public:
    // 构造语音识别客户端对象
    void make_asr_object(const std::string &app_id,
                         const std::string &api_key,
                         const std::string &secret_key)
    {
      _asr_client = std::make_shared<ASRClient>(app_id, api_key, secret_key);
    }

    // 用于构造服务注册客户端对象
    void make_reg_object(const std::string &reg_host,
                         const std::string &service_name,
                         const std::string &access_host)
    {
      _reg_client = std::make_shared<Registry>(reg_host);
      _reg_client->registry(service_name, access_host);
    }

    // 构造RPC服务器对象
    void make_rpc_server(uint16_t port, int32_t timeout, uint8_t num_threads)
    {
      if (!_asr_client)
      {
        LOG_ERROR("还未初始化语音识别模块！");
        abort();
      }
      _rpc_server = std::make_shared<brpc::Server>();
      VoiceServiceImpl *voice_service = new VoiceServiceImpl(_asr_client);
      int ret = _rpc_server->AddService(voice_service,
                                        brpc::ServiceOwnership::SERVER_OWNS_SERVICE);
      if (ret == -1)
      {
        LOG_ERROR("添加Rpc服务失败！");
        abort();
      }
      brpc::ServerOptions options;
      options.idle_timeout_sec = timeout;
      options.num_threads = num_threads;
      ret = _rpc_server->Start(port, &options);
      if (ret == -1)
      {
        LOG_ERROR("服务启动失败！");
        abort();
      }
    }

    VoiceServer::ptr build()
    {
      if (!_asr_client)
      {
        LOG_ERROR("还未初始化语音识别模块！");
        abort();
      }
      if (!_reg_client)
      {
        LOG_ERROR("还未初始化服务注册模块！");
        abort();
      }
      if (!_rpc_server)
      {
        LOG_ERROR("还未初始化RPC服务器模块！");
        abort();
      }
      VoiceServer::ptr server = std::make_shared<VoiceServer>(
          _asr_client, _reg_client, _rpc_server);
      return server;
    }

  private:
    ASRClient::ptr _asr_client;
    Registry::ptr _reg_client;
    std::shared_ptr<brpc::Server> _rpc_server;
  };
}   // end of namespace my_chat