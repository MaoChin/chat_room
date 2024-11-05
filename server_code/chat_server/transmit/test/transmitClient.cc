#include "etcd.hpp"
#include "channel.hpp"
#include "util.hpp"
#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <thread>
#include "message_transmit.pb.h"

DEFINE_bool(run_mode, false, "程序的运行模式，false-调试； true-发布；");
DEFINE_string(log_file, "", "发布模式下，用于指定日志的输出文件");
DEFINE_int32(log_level, 0, "发布模式下，用于指定日志输出等级");

DEFINE_string(etcd_host, "http://127.0.0.1:2379", "服务注册中心地址");
DEFINE_string(base_service, "/service", "服务监控根目录");
DEFINE_string(transmit_service, "/service/transmit_service", "服务监控根目录");

my_chat::ServiceManager::ptr sm;

void string_message(const std::string &uid, const std::string &sid, const std::string &msg)
{
    auto channel = sm->choose(FLAGS_transmit_service);
    if (!channel)
    {
        std::cout << "获取通信信道失败！" << std::endl;
        return;
    }
    my_chat::MsgTransmitService_Stub stub(channel.get());
    my_chat::NewMessageReq req;
    my_chat::GetTransmitTargetRsp rsp;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(uid);
    req.set_chat_session_id(sid);
    req.mutable_message()->set_message_type(my_chat::MessageType::TEXT);
    req.mutable_message()->mutable_text_message()->set_text_content(msg);
    brpc::Controller cntl;
    stub.GetTransmitTarget(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}
void image_message(const std::string &uid, const std::string &sid, const std::string &msg)
{
    auto channel = sm->choose(FLAGS_transmit_service);
    if (!channel)
    {
        std::cout << "获取通信信道失败！" << std::endl;
        return;
    }
    my_chat::MsgTransmitService_Stub stub(channel.get());
    my_chat::NewMessageReq req;
    my_chat::GetTransmitTargetRsp rsp;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(uid);
    req.set_chat_session_id(sid);
    req.mutable_message()->set_message_type(my_chat::MessageType::IMAGE);
    req.mutable_message()->mutable_image_message()->set_image_content(msg);
    brpc::Controller cntl;
    stub.GetTransmitTarget(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

void voice_message(const std::string &uid, const std::string &sid, const std::string &msg)
{
    auto channel = sm->choose(FLAGS_transmit_service);
    if (!channel)
    {
        std::cout << "获取通信信道失败！" << std::endl;
        return;
    }
    my_chat::MsgTransmitService_Stub stub(channel.get());
    my_chat::NewMessageReq req;
    my_chat::GetTransmitTargetRsp rsp;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(uid);
    req.set_chat_session_id(sid);
    req.mutable_message()->set_message_type(my_chat::MessageType::VOICE);
    req.mutable_message()->mutable_voice_message()->set_voice_contents(msg);
    brpc::Controller cntl;
    stub.GetTransmitTarget(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

void file_message(const std::string &uid, const std::string &sid,
                  const std::string &filename, const std::string &content)
{
    auto channel = sm->choose(FLAGS_transmit_service);
    if (!channel)
    {
        std::cout << "获取通信信道失败！" << std::endl;
        return;
    }
    my_chat::MsgTransmitService_Stub stub(channel.get());
    my_chat::NewMessageReq req;
    my_chat::GetTransmitTargetRsp rsp;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(uid);
    req.set_chat_session_id(sid);
    req.mutable_message()->set_message_type(my_chat::MessageType::FILE);
    req.mutable_message()->mutable_file_message()->set_file_contents(content);
    req.mutable_message()->mutable_file_message()->set_file_name(filename);
    req.mutable_message()->mutable_file_message()->set_file_size(content.size());
    brpc::Controller cntl;
    stub.GetTransmitTarget(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

int main(int argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    my_chat::init_logger(FLAGS_run_mode, FLAGS_log_file, FLAGS_log_level);

    // 1. 先构造Rpc信道管理对象
    sm = std::make_shared<my_chat::ServiceManager>();
    sm->declared(FLAGS_transmit_service);
    auto put_cb = std::bind(&my_chat::ServiceManager::onServiceOnline, sm.get(), std::placeholders::_1, std::placeholders::_2);
    auto del_cb = std::bind(&my_chat::ServiceManager::onServiceOffline, sm.get(), std::placeholders::_1, std::placeholders::_2);
    // 2. 构造服务发现对象
    my_chat::Discovery::ptr dclient = std::make_shared<my_chat::Discovery>(FLAGS_etcd_host, FLAGS_base_service, put_cb, del_cb);

    // 3. 通过Rpc信道管理对象，获取提供Echo服务的信道
     string_message("731f-50086884-0000", "会话ID1", "吃饭了吗？");
    //  string_message("c4dc-68239a9a-0001", "会话ID1", "吃的盖浇饭！！");
    //  image_message("731f-50086884-0000", "会话ID1", "可爱表情图片数据");
    //  voice_message("731f-50086884-0000", "会话ID1", "动听猪叫声数据");
    file_message("731f-50086884-0000", "0d90-755571d8-0003", "猪爸爸的文件名称", "猪爸爸的文件数据");
    return 0;
}