#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <etcd/Value.hpp>
#include <etcd/Watcher.hpp>
#include <string>
#include <memory>

// 获取etcd中的key-value，以及对key进行监控


void callback(const etcd::Response& resp){
  const std::vector<etcd::Event>& events = resp.events();
  for(etcd::Event event : events){
    if(event.event_type() == etcd::Event::EventType::PUT){
      std::cout << "数据发生改变" << std::endl;
      std::cout << "原来的值： "  << event.prev_kv().key() << " - " << event.prev_kv().as_string() << std::endl;
      std::cout << "现在的值： "  << event.kv().key() << " - " << event.kv().as_string() << std::endl;
    }
    else if(event.event_type() == etcd::Event::EventType::DELETE_){
      std::cout << "数据被删除" << std::endl;
      std::cout << "原来的值： "  << event.prev_kv().key() << " - " << event.prev_kv().as_string() << std::endl;
      std::cout << "现在的值： "  << event.kv().key() << " - " << event.kv().as_string() << std::endl;
    }
    else{
      std::cout << "invalid" << std::endl;
    }
  }
}

int main(){
  // 先搞一个clinet对象
  std::string etcd_host = "http://127.0.0.1:2379";
  etcd::Client client(etcd_host);

  etcd::Response resp = client.ls("/service").get();
  if(!resp.is_ok()){
    std::cout << "ls error: " << resp.error_message() << std::endl;
    return -1;
  }

  // 遍历当前已经注册的服务
  int sz = resp.keys().size();
  for(int i = 0; i < sz; ++i){
    std::cout << resp.value(i).as_string() << " 提供 " << resp.key(i) << " 服务" << std::endl;
  }

  // 对指定的服务进行监控
  etcd::Watcher watcher = etcd::Watcher(client, "/service", callback, true);
  watcher.Wait();

  return 0;
}
