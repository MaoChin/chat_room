#pragma once
#include <string>
#include <cstddef>
#include <odb/nullable.hxx>
#include <odb/core.hxx>

// 关系表的ODB辅助类
namespace my_chat
{
#pragma db object table("relation")
  class Relation
  {
  public:
    Relation() {}
    Relation(const std::string &uid, const std::string &pid) : _user_id(uid), _friend_id(pid) {}

    std::string user_id() const { return _user_id; }
    void user_id(std::string &uid) { _user_id = uid; }

    std::string friend_id() const { return _friend_id; }
    void friend_id(std::string &uid) { _friend_id = uid; }

  private:
    friend class odb::access;
#pragma db id auto
    unsigned long _id;
#pragma db type("varchar(64)") index
    std::string _user_id;
#pragma db type("varchar(64)")
    std::string _friend_id;
  };
}  // end of namespace my_chat