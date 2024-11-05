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

my_chat::ServiceManager::ptr _user_channels;

my_chat::UserInfo user_info;

std::string login_ssid;
std::string new_nickname = "亲爱的猪妈妈";

// TEST(用户子服务测试, 用户注册测试) {
//     auto channel = _user_channels->choose(FLAGS_user_service);//获取通信信道
//     ASSERT_TRUE(channel);
//     user_info.set_nickname("猪妈妈");

//     my_chat::UserRegisterReq req;
//     req.set_request_id(my_chat::uuid());
//     req.set_nickname(user_info.nickname());
//     req.set_password("123456");
//     my_chat::UserRegisterRsp rsp;
//     brpc::Controller cntl;
//     my_chat::UserService_Stub stub(channel.get());
//     stub.UserRegister(&cntl, &req, &rsp, nullptr);
//     ASSERT_FALSE(cntl.Failed());
//     ASSERT_TRUE(rsp.success());
// }
TEST(用户子服务测试, 用户登录测试)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::UserLoginReq req;
    req.set_request_id(my_chat::uuid());
    req.set_nickname("亲爱的猪妈妈");
    req.set_password("123456");
    my_chat::UserLoginRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.UserLogin(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
    login_ssid = rsp.login_session_id();
}
TEST(用户子服务测试, 用户头像设置测试)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::SetUserHeadPortraitReq req;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(user_info.user_id());
    req.set_session_id(login_ssid);
    req.set_head_portrait(user_info.head_portrait());
    my_chat::SetUserHeadPortraitRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.SetUserHeadPortrait(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}
TEST(用户子服务测试, 用户签名设置测试)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::SetUserSignatureReq req;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(user_info.user_id());
    req.set_session_id(login_ssid);
    req.set_signature(user_info.person_signature());
    my_chat::SetUserSignatureRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.SetUserSignature(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}
TEST(用户子服务测试, 用户昵称设置测试)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::SetUserNicknameReq req;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(user_info.user_id());
    req.set_session_id(login_ssid);
    req.set_nickname(new_nickname);
    my_chat::SetUserNicknameRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.SetUserNickname(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

TEST(用户子服务测试, 用户信息获取测试)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::GetUserInfoReq req;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(user_info.user_id());
    req.set_session_id(login_ssid);
    my_chat::GetUserInfoRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.GetUserInfo(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
    ASSERT_EQ(user_info.user_id(), rsp.user_info().user_id());
    ASSERT_EQ(new_nickname, rsp.user_info().nick_name());
    ASSERT_EQ(user_info.person_signature(), rsp.user_info().person_signature());
    ASSERT_EQ("", rsp.user_info().phone_number());
    ASSERT_EQ(user_info.head_portrait(), rsp.user_info().head_portrait());
}

void set_user_head_portrait(const std::string &uid, const std::string &head_portrait)
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);
    my_chat::SetUserHeadPortraitReq req;
    req.set_request_id(my_chat::uuid());
    req.set_user_id(uid);
    req.set_session_id(login_ssid);
    req.set_head_portrait(head_portrait);
    my_chat::SetUserHeadPortraitRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.SetUserHeadPortrait(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

TEST(用户子服务测试, 批量用户信息获取测试)
{
    set_user_head_portrait("用户ID1", "小猪佩奇的头像数据");
    set_user_head_portrait("用户ID2", "小猪乔治的头像数据");
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::GetMultiUserInfoReq req;
    req.set_request_id(my_chat::uuid());
    req.add_users_id("用户ID1");
    req.add_users_id("用户ID2");
    req.add_users_id("ee55-9043bfd7-0001");
    my_chat::GetMultiUserInfoRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.GetMultiUserInfo(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
    auto users_map = rsp.mutable_users_info();
    my_chat::UserInfo fuser = (*users_map)["ee55-9043bfd7-0001"];
    ASSERT_EQ(fuser.user_id(), "ee55-9043bfd7-0001");
    ASSERT_EQ(fuser.nick_name(), "猪爸爸");
    ASSERT_EQ(fuser.person_signature(), "");
    ASSERT_EQ(fuser.phone_number(), "");
    ASSERT_EQ(fuser.head_portrait(), "");

    my_chat::UserInfo puser = (*users_map)["用户ID1"];
    ASSERT_EQ(puser.user_id(), "用户ID1");
    ASSERT_EQ(puser.nick_name(), "小猪佩奇");
    ASSERT_EQ(puser.person_signature(), "这是一只小猪");
    ASSERT_EQ(puser.phone_number(), "手机号1");
    ASSERT_EQ(puser.head_portrait(), "小猪佩奇的头像数据");

    my_chat::UserInfo quser = (*users_map)["用户ID2"];
    ASSERT_EQ(quser.user_id(), "用户ID2");
    ASSERT_EQ(quser.nick_name(), "小猪乔治");
    ASSERT_EQ(quser.person_signature(), "这是一只小小猪");
    ASSERT_EQ(quser.phone_number(), "手机号2");
    ASSERT_EQ(quser.head_portrait(), "小猪乔治的头像数据");
}

std::string code_id;
void get_code()
{
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::PhoneVerifyCodeReq req;
    req.set_request_id(my_chat::uuid());
    req.set_phone_number(user_info.phone_number());
    my_chat::PhoneVerifyCodeRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.GetPhoneVerifyCode(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
    code_id = rsp.verify_code_id();
}

// TEST(用户子服务测试, 手机号注册) {
//     get_code();
//     auto channel = _user_channels->choose(FLAGS_user_service);//获取通信信道
//     ASSERT_TRUE(channel);

//     my_chat::PhoneRegisterReq req;
//     req.set_request_id(my_chat::uuid());
//     req.set_phone_number(user_info.phone_number());
//     req.set_verify_code_id(code_id);
//     std::cout << "手机号注册，输入验证码：" << std::endl;
//     std::string code;
//     std::cin >> code;
//     req.set_verify_code(code);
//     my_chat::PhoneRegisterRsp rsp;
//     brpc::Controller cntl;
//     my_chat::UserService_Stub stub(channel.get());
//     stub.PhoneRegister(&cntl, &req, &rsp, nullptr);
//     ASSERT_FALSE(cntl.Failed());
//     ASSERT_TRUE(rsp.success());
// }
TEST(用户子服务测试, 手机号登录)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    get_code();
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::PhoneLoginReq req;
    req.set_request_id(my_chat::uuid());
    req.set_phone_number(user_info.phone_number());
    req.set_verify_code_id(code_id);
    std::cout << "手机号登录，输入验证码：" << std::endl;
    std::string code;
    std::cin >> code;
    req.set_verify_code(code);
    my_chat::PhoneLoginRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.PhoneLogin(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
    std::cout << "手机登录会话ID：" << rsp.login_session_id() << std::endl;
}
TEST(用户子服务测试, 手机号设置)
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
    get_code();
    auto channel = _user_channels->choose(FLAGS_user_service); // 获取通信信道
    ASSERT_TRUE(channel);

    my_chat::SetUserPhoneNumberReq req;
    req.set_request_id(my_chat::uuid());
    std::cout << "手机号设置时，输入用户ID：" << std::endl;
    std::string user_id;
    std::cin >> user_id;
    req.set_user_id(user_id);
    req.set_phone_number("18888888888");
    req.set_phone_verify_code_id(code_id);
    std::cout << "手机号设置时，输入验证码：" << std::endl;
    std::string code;
    std::cin >> code;
    req.set_phone_verify_code(code);
    my_chat::SetUserPhoneNumberRsp rsp;
    brpc::Controller cntl;
    my_chat::UserService_Stub stub(channel.get());
    stub.SetUserPhoneNumber(&cntl, &req, &rsp, nullptr);
    ASSERT_FALSE(cntl.Failed());
    ASSERT_TRUE(rsp.success());
}

int main(int argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    my_chat::init_logger(FLAGS_run_mode, FLAGS_log_file, FLAGS_log_level);

    // 1. 先构造Rpc信道管理对象
    _user_channels = std::make_shared<my_chat::ServiceManager>();
    _user_channels->declared(FLAGS_user_service);
    auto put_cb = std::bind(&my_chat::ServiceManager::onServiceOnline, _user_channels.get(), std::placeholders::_1, std::placeholders::_2);
    auto del_cb = std::bind(&my_chat::ServiceManager::onServiceOffline, _user_channels.get(), std::placeholders::_1, std::placeholders::_2);

    // 2. 构造服务发现对象
    my_chat::Discovery::ptr dclient = std::make_shared<my_chat::Discovery>(FLAGS_etcd_host, FLAGS_base_service, put_cb, del_cb);

    user_info.set_nick_name("猪妈妈");
    user_info.set_user_id("1d56-513d8e49-0002");
    user_info.set_person_signature("这是一个美丽的猪妈妈");
    user_info.set_phone_number("15929917272");
    user_info.set_head_portrait("猪妈妈头像数据");
    testing::InitGoogleTest(&argc, argv);
    LOG_DEBUG("开始测试！");
    return RUN_ALL_TESTS();
}