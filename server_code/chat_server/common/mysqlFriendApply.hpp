#pragma once
#include "mysql.hpp"
#include "friendApply.hxx"
#include "friendApply-odb.hxx"

// 好友申请表---ODB映射类
namespace my_chat
{
  class FriendApplyTable
  {
  public:
    using ptr = std::shared_ptr<FriendApplyTable>;
    FriendApplyTable(const std::shared_ptr<odb::core::database> &db) : _db(db) {}

    // 插入数据
    bool insert(FriendApply &ev)
    {
      try
      {
        odb::transaction trans(_db->begin());
        _db->persist(ev);
        trans.commit();
      }
      catch (std::exception &e)
      {
        LOG_ERROR("新增好友申请事件失败 {}-{}:{}！", ev.user_id(), ev.friend_id(), e.what());
        return false;
      }
      return true;
    }

    // 判断是否存在
    bool exists(const std::string &uid, const std::string &pid)
    {
      bool flag = false;
      try
      {
        typedef odb::query<FriendApply> query;
        typedef odb::result<FriendApply> result;
        odb::transaction trans(_db->begin());
        result r(_db->query<FriendApply>(query::user_id == uid && query::friend_id == pid));
        LOG_DEBUG("{} - {} 好友事件数量：{}", uid, pid, r.size());
        flag = !r.empty();
        trans.commit();
      }
      catch (std::exception &e)
      {
        LOG_ERROR("获取好友申请事件失败:{}-{}-{}！", uid, pid, e.what());
      }
      return flag;
    }

    // 删除数据
    bool remove(const std::string &uid, const std::string &pid)
    {
      try
      {
        odb::transaction trans(_db->begin());
        typedef odb::query<FriendApply> query;
        typedef odb::result<FriendApply> result;
        _db->erase_query<FriendApply>(query::user_id == uid && query::friend_id == pid);
        trans.commit();
      }
      catch (std::exception &e)
      {
        LOG_ERROR("删除好友申请事件失败 {}-{}:{}！", uid, pid, e.what());
        return false;
      }
      return true;
    }

    // 获取当前指定用户的 所有好友申请者ID
    std::vector<std::string> applyUsers(const std::string &uid)
    {
      std::vector<std::string> res;
      try
      {
        odb::transaction trans(_db->begin());
        typedef odb::query<FriendApply> query;
        typedef odb::result<FriendApply> result;
        // 当前的uid是被申请者的用户ID
        result r(_db->query<FriendApply>(query::friend_id == uid));
        for (result::iterator i(r.begin()); i != r.end(); ++i)
        {
          res.push_back(i->user_id());
        }
        trans.commit();
      }
      catch (std::exception &e)
      {
        LOG_ERROR("通过用户{}的好友申请者失败:{}！", uid, e.what());
      }
      return res;
    }

  private:
    std::shared_ptr<odb::core::database> _db;
  };
}   // end of namespace my_chat