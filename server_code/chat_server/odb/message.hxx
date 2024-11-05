#pragma once
#include <string>
#include <cstddef>
#include <odb/nullable.hxx>
#include <odb/core.hxx>
#include <boost/date_time/posix_time/posix_time.hpp>

// 消息表的ODB辅助类
namespace my_chat
{
// 创建表
#pragma db object table("message")
  class Message
  {
  public:
    Message() {}
    Message(const std::string &mid,
            const std::string &ssid,
            const std::string &uid,
            const unsigned char mtype,
            const boost::posix_time::ptime &ctime) : _message_id(mid), _session_id(ssid),
                                                     _user_id(uid), _message_type(mtype),
                                                     _create_time(ctime) {}

    std::string message_id() const { return _message_id; }
    void message_id(const std::string &val) { _message_id = val; }

    std::string session_id() const { return _session_id; }
    void session_id(const std::string &val) { _session_id = val; }

    std::string user_id() const { return _user_id; }
    void user_id(const std::string &val) { _user_id = val; }

    unsigned char message_type() const { return _message_type; }
    void message_type(unsigned char val) { _message_type = val; }

    boost::posix_time::ptime create_time() const { return _create_time; }
    void create_time(const boost::posix_time::ptime &val) { _create_time = val; }

    std::string content() const
    {
      if (!_content)
        return std::string();
      return *_content;
    }
    void content(const std::string &val) { _content = val; }

    std::string file_id() const
    {
      if (!_file_id)
        return std::string();
      return *_file_id;
    }
    void file_id(const std::string &val) { _file_id = val; }

    std::string file_name() const
    {
      if (!_file_name)
        return std::string();
      return *_file_name;
    }
    void file_name(const std::string &val) { _file_name = val; }

    unsigned int file_size() const
    {
      if (!_file_size)
        return 0;
      return *_file_size;
    }
    void file_size(unsigned int val) { _file_size = val; }

  private:
    friend class odb::access;
#pragma db id auto
    unsigned long _id;
#pragma db type("varchar(64)") index unique
    std::string _message_id;
#pragma db type("varchar(64)") index
    // 所属会话ID
    std::string _session_id; 
#pragma db type("varchar(64)")
    // 发送者用户ID
    std::string _user_id;        
    // 消息类型 0-文本；1-图片；2-文件；3-语音
    unsigned char _message_type; 
#pragma db type("TIMESTAMP")
    // 消息的产生时间
    boost::posix_time::ptime _create_time; 
    // 文本消息内容--非文本消息可以忽略
    odb::nullable<std::string> _content; 
#pragma db type("varchar(64)")
    // 文件消息的文件ID -- 文本消息忽略
    odb::nullable<std::string> _file_id; 
#pragma db type("varchar(128)")
    // 文件消息的文件名称 -- 只针对文件消息有效
    odb::nullable<std::string> _file_name;  
    // 文件消息的文件大小 -- 只针对文件消息有效
    odb::nullable<unsigned int> _file_size; 
  };
}   // end of namespace my_chat