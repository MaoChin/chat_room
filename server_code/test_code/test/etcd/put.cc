#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <etcd/Value.hpp>
#include <etcd/KeepAlive.hpp>
#include <string>
#include <thread>
#include <memory>

// 向etcd中添加key-value
int main(){
  // 先搞一个client对象
  std::string etcd_host = "http://127.0.0.1:2379";
  etcd::Client client(etcd_host);

  // 设置租期
  std::shared_ptr<etcd::KeepAlive> keep_alive = client.leasekeepalive(3).get();
  int64_t lease = keep_alive->Lease();

  // 注册服务
  etcd::Response resp1 = client.put("/service/user", "127.0.0.1:8080", lease).get();

  if(!resp1.is_ok()){
    std::cout << "put error: " << resp1.error_message() << std::endl;
    return -1;
  }

  // 注册服务
  etcd::Response resp2 = client.put("/service/friend", "127.0.0.1:9090").get();
  if(!resp2.is_ok()){
    std::cout << "put error: " << resp2.error_message() << std::endl;
    return -1;
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));
  return 0;
}
