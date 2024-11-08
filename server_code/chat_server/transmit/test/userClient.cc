#include "etcd.hpp"
#include "channel.hpp"
#include "util.hpp"
#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <thread>
#include "user.pb.h"
#include "base.pb.h"

DEFINE_bool(run_mode, false, "程序的运行模式，false-调试； true-发布；");
DEFINE_string(log_file, "", "发布模式下，用于指定日志的输出文件");
DEFINE_int32(log_level, 0, "发布模式下，用于指定日志输出等级");

DEFINE_string(etcd_host, "http://127.0.0.1:2379", "服务注册中心地址");
DEFINE_string(base_service, "/service", "服务监控根目录");
DEFINE_string(user_service, "/service/user_service", "服务监控根目录");

my_chat::ServiceManager::ptr user_channels;
void reg_user(const std::string &nickname, const std::string &pswd)
{
  auto channel = user_channels->choose(FLAGS_user_service); // 获取通信信道
  ASSERT_TRUE(channel);

  my_chat::UserRegisterReq req;
  req.set_request_id(my_chat::uuid());
  req.set_nickname(nickname);
  req.set_password(pswd);

  my_chat::UserRegisterRsp rsp;
  brpc::Controller cntl;
  my_chat::UserService_Stub stub(channel.get());
  stub.UserRegister(&cntl, &req, &rsp, nullptr);
  ASSERT_FALSE(cntl.Failed());
  ASSERT_TRUE(rsp.success());
}

void set_user_head_portrait(const std::string &uid, const std::string &head_portrait)
{
  auto channel = user_channels->choose(FLAGS_user_service); // 获取通信信道
  ASSERT_TRUE(channel);
  my_chat::SetUserHeadPortraitReq req;
  req.set_request_id(my_chat::uuid());
  req.set_user_id(uid);
  req.set_session_id("测试登录会话ID");
  req.set_head_portrait(head_portrait);
  my_chat::SetUserHeadPortraitRsp rsp;
  brpc::Controller cntl;
  my_chat::UserService_Stub stub(channel.get());
  stub.SetUserHeadPortrait(&cntl, &req, &rsp, nullptr);
  ASSERT_FALSE(cntl.Failed());
  ASSERT_TRUE(rsp.success());
}

int main(int argc, char *argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  my_chat::init_logger(FLAGS_run_mode, FLAGS_log_file, FLAGS_log_level);

  user_channels = std::make_shared<my_chat::ServiceManager>();

  user_channels->declared(FLAGS_user_service);
  auto put_cb = std::bind(&my_chat::ServiceManager::onServiceOnline, user_channels.get(), std::placeholders::_1, std::placeholders::_2);
  auto del_cb = std::bind(&my_chat::ServiceManager::onServiceOffline, user_channels.get(), std::placeholders::_1, std::placeholders::_2);

  // 2. 构造服务发现对象
  my_chat::Discovery::ptr dclient = std::make_shared<my_chat::Discovery>(FLAGS_etcd_host, FLAGS_base_service, put_cb, del_cb);

  // reg_user("小猪佩奇", "123456");
  // reg_user("小猪乔治", "123456");
  // std::string uid1, uid2;
  // std::cout << "输入佩奇用户ID：";
  // std::fflush(stdout);
  // std::cin >> uid1;
  // std::cout << "输入乔治用户ID：";
  // std::fflush(stdout);
  // std::cin >> uid2;
  set_user_head_portrait("731f-50086884-0000", "猪爸爸头像数据");
  set_user_head_portrait("c4dc-68239a9a-0001", "猪妈妈头像数据");
  return 0;
}