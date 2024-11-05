#pragma once
#include <string>
#include <cstddef>
#include <odb/core.hxx>

// 好友申请表的ODB辅助类
namespace my_chat
{
// 创建表
#pragma db object table("friend_apply")
  class FriendApply
  {
  public:
    FriendApply() {}
    FriendApply(const std::string &eid,
                const std::string &uid, const std::string &pid) : _user_id(uid), _friend_id(pid), _event_id(eid) {}

    std::string event_id() const { return _event_id; }
    void event_id(std::string &eid) { _event_id = eid; }

    std::string user_id() const { return _user_id; }
    void user_id(std::string &uid) { _user_id = uid; }

    std::string friend_id() const { return _friend_id; }
    void friend_id(std::string &uid) { _friend_id = uid; }

  private:
    friend class odb::access;
#pragma db id auto
    unsigned long _id;
#pragma db type("varchar(64)") index unique
    std::string _event_id;
#pragma db type("varchar(64)") index
    std::string _user_id;
#pragma db type("varchar(64)") index
    std::string _friend_id;
  };
}  // end of namespace my_chat