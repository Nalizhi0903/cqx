#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <sstream>
class JsonUtil 
{
public:
/*
value : 待要序列化的json对象
body : 序列化完毕产⽣的string对象 （出参）
*/
  static bool Serialize(const Json::Value& value, std::string* body) 
  {
    Json::StreamWriterBuilder swb;
    std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
    std::stringstream ss;
    int ret = sw->write(value, &ss);
    if (ret != 0) 
    {
      return false;
    }
    *body = ss.str();
    return true;
  }
  /*
  body ： 待要反序列化的string对象
  value ： 序列化完毕产⽣的json对象 （出参）
  */
  static bool UnSerialize(const std::string& body, Json::Value* value)
  {
    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
    std::string err;
    bool ret = cr->parse(body.c_str(), body.c_str() + body.size(), value, &err);
    if (ret == false) 
    {
      return false;
    }
      return true;
  }
};
int main()
{
  Json::Value v1;
  v1["nickname"] = "wudu";
  v1["school"] = "bite";
  v1["telnum"] = "123456";
  v1["passwd"] = "123";

  Json::Value _json_msg;
  _json_msg["telnum"] = "12121212";

  v1["_json_msg"] = _json_msg;

  std::string msg;
  JsonUtil::Serialize(v1, &msg);
  std::cout << msg << std::endl;
  std::cout << v1 << std::endl;

  return 0;
}
