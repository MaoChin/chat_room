#pragma once
#include <elasticlient/client.h>
#include <cpr/cpr.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <memory>
#include "logger.hpp"

// elasticsearch的client封装
namespace my_chat
{
  // Json序列化与反序列化
  bool Serialize(const Json::Value &val, std::string &dst)
  {
    // 先定义Json::StreamWriter 工厂类 Json::StreamWriterBuilder
    Json::StreamWriterBuilder swb;
    swb.settings_["emitUTF8"] = true;
    std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
    // 通过Json::StreamWriter中的write接口进行序列化
    std::stringstream ss;
    int ret = sw->write(val, &ss);
    if (ret != 0)
    {
      std::cout << "Json反序列化失败！\n";
      return false;
    }
    dst = ss.str();
    return true;
  }
  bool UnSerialize(const std::string &src, Json::Value &val)
  {
    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
    std::string err;
    bool ret = cr->parse(src.c_str(), src.c_str() + src.size(), &val, &err);
    if (ret == false)
    {
      std::cout << "json反序列化失败: " << err << std::endl;
      return false;
    }
    return true;
  }

  // elasticSearch的索引封装
  class ESIndex
  {
  public:
    ESIndex(std::shared_ptr<elasticlient::Client> &client,
            const std::string &name,
            const std::string &type = "_doc") : _name(name), _type(type), _client(client)
    {
      Json::Value analysis;
      Json::Value analyzer;
      Json::Value ik;
      Json::Value tokenizer;
      tokenizer["tokenizer"] = "ik_max_word";
      ik["ik"] = tokenizer;
      analyzer["analyzer"] = ik;
      analysis["analysis"] = analyzer;
      _index["settings"] = analysis;
    }

    // 添加索引字段
    ESIndex &append(const std::string &key,
                    const std::string &type = "text",
                    const std::string &analyzer = "ik_max_word",
                    bool enabled = true)
    {
      Json::Value fields;
      fields["type"] = type;
      fields["analyzer"] = analyzer;
      if (enabled == false)
        fields["enabled"] = enabled;
      _properties[key] = fields;
      return *this;
    }

    // 创建索引
    bool create(const std::string &index_id = "default_index_id")
    {
      Json::Value mappings;
      mappings["dynamic"] = true;
      mappings["properties"] = _properties;
      _index["mappings"] = mappings;

      std::string body;
      bool ret = Serialize(_index, body);
      if (ret == false)
      {
        LOG_ERROR("索引序列化失败！");
        return false;
      }
      LOG_DEBUG("{}", body);
      // 2. 发起搜索请求
      try
      {
        auto rsp = _client->index(_name, _type, index_id, body);
        if (rsp.status_code < 200 || rsp.status_code >= 300)
        {
          LOG_ERROR("创建ES索引 {} 失败，响应状态码异常: {}", _name, rsp.status_code);
          return false;
        }
      }
      catch (std::exception &e)
      {
        LOG_ERROR("创建ES索引 {} 失败: {}", _name, e.what());
        return false;
      }
      return true;
    }

  private:
    std::string _name;
    std::string _type;
    Json::Value _properties;
    Json::Value _index;
    std::shared_ptr<elasticlient::Client> _client;
  };

  // elasticSearch的数据插入封装
  class ESInsert
  {
  public:
    ESInsert(std::shared_ptr<elasticlient::Client> &client,
             const std::string &name, const std::string &type = "_doc")
     : _name(name), _type(type), _client(client) {}

    // 泛型
    template <typename T>
    ESInsert &append(const std::string &key, const T &val)
    {
      _item[key] = val;
      return *this;
    }
    bool insert(const std::string id = "")
    {
      std::string body;
      bool ret = Serialize(_item, body);
      if (ret == false)
      {
        LOG_ERROR("索引序列化失败！");
        return false;
      }
      LOG_DEBUG("{}", body);
      // 2. 发起搜索请求
      try
      {
        auto rsp = _client->index(_name, _type, id, body);
        if (rsp.status_code < 200 || rsp.status_code >= 300)
        {
          LOG_ERROR("新增数据 {} 失败，响应状态码异常: {}", body, rsp.status_code);
          return false;
        }
      }
      catch (std::exception &e)
      {
        LOG_ERROR("新增数据 {} 失败: {}", body, e.what());
        return false;
      }
      return true;
    }

  private:
    std::string _name;
    std::string _type;
    Json::Value _item;
    std::shared_ptr<elasticlient::Client> _client;
  };

  // elasticSearch的数据删除封装
  class ESRemove
  {
  public:
    ESRemove(std::shared_ptr<elasticlient::Client> &client,
             const std::string &name, const std::string &type = "_doc")
             : _name(name), _type(type), _client(client) {}

    // 删除数据
    bool remove(const std::string &id)
    {
      try
      {
        auto rsp = _client->remove(_name, _type, id);
        if (rsp.status_code < 200 || rsp.status_code >= 300)
        {
          LOG_ERROR("删除数据 {} 失败，响应状态码异常: {}", id, rsp.status_code);
          return false;
        }
      }
      catch (std::exception &e)
      {
        LOG_ERROR("删除数据 {} 失败: {}", id, e.what());
        return false;
      }
      return true;
    }

  private:
    std::string _name;
    std::string _type;
    std::shared_ptr<elasticlient::Client> _client;
  };

  // elasticSearch的数据检索封装
  class ESSearch
  {
  public:
    ESSearch(std::shared_ptr<elasticlient::Client> &client,
             const std::string &name, const std::string &type = "_doc")
            : _name(name), _type(type), _client(client) {}

    // 添加检索条件：term匹配方式(反向)
    ESSearch &append_must_not_terms(const std::string &key, const std::vector<std::string> &vals)
    {
      Json::Value fields;
      for (const auto &val : vals)
      {
        fields[key].append(val);
      }
      Json::Value terms;
      terms["terms"] = fields;
      _must_not.append(terms);
      return *this;
    }

    // 添加检索条件：term匹配方式
    ESSearch &append_must_term(const std::string &key, const std::string &val)
    {
      Json::Value field;
      field[key] = val;
      Json::Value term;
      term["term"] = field;
      _must.append(term);
      return *this;
    }

    // 添加检索条件：match匹配方式
    ESSearch &append_should_match(const std::string &key, const std::string &val)
    {
      Json::Value field;
      field[key] = val;
      Json::Value match;
      match["match"] = field;
      _should.append(match);
      return *this;
    }

    // 添加检索条件：match匹配方式
    ESSearch &append_must_match(const std::string &key, const std::string &val)
    {
      Json::Value field;
      field[key] = val;
      Json::Value match;
      match["match"] = field;
      _must.append(match);
      return *this;
    }

    // 进行搜索
    Json::Value search()
    {
      Json::Value cond;
      if (_must_not.empty() == false)
        cond["must_not"] = _must_not;
      if (_should.empty() == false)
        cond["should"] = _should;
      if (_must.empty() == false)
        cond["must"] = _must;
      Json::Value query;
      query["bool"] = cond;
      Json::Value root;
      root["query"] = query;

      std::string body;
      bool ret = Serialize(root, body);
      if (ret == false)
      {
        LOG_ERROR("索引序列化失败！");
        return Json::Value();
      }
      LOG_DEBUG("{}", body);
      // 2. 发起搜索请求
      cpr::Response rsp;
      try
      {
        rsp = _client->search(_name, _type, body);
        if (rsp.status_code < 200 || rsp.status_code >= 300)
        {
          LOG_ERROR("检索数据 {} 失败，响应状态码异常: {}", body, rsp.status_code);
          return Json::Value();
        }
      }
      catch (std::exception &e)
      {
        LOG_ERROR("检索数据 {} 失败: {}", body, e.what());
        return Json::Value();
      }
      // 3. 需要对响应正文进行反序列化
      LOG_DEBUG("检索响应正文: [{}]", rsp.text);
      Json::Value json_res;
      ret = UnSerialize(rsp.text, json_res);
      if (ret == false)
      {
        LOG_ERROR("检索数据 {} 结果反序列化失败", rsp.text);
        return Json::Value();
      }
      return json_res["hits"]["hits"];
    }

  private:
    std::string _name;
    std::string _type;
    Json::Value _must_not;
    Json::Value _should;
    Json::Value _must;
    std::shared_ptr<elasticlient::Client> _client;
  };
}   // end of namespace my_chat