#pragma once
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <sstream>
#include <string>
using namespace std;
enum chat_msg_type 
{
  Register = 0,//注册请求
  Register_Resp, //注册应答
  Login,//登入
  Login_Resp,//登入应答
  AddFriend,//添加好友
  ADDFriend_Resp,//添加好友应答
  PushAddFriendMsg,//推送好友请求
  PushAddFriendMsg_Resp,//推送添加好友应答
  SendMsg,//发送消息
  SendMsg_Resp,//发送消息应答
  PushMsg,//推送数据
  PushMsg_Resp//推送数据应答
};

enum reply_statu
{
  REGISTER_SUCCESS = 0,
  REGISTER_FAILED,
  LOGIN_SUCCESS,
  LOGIN_FAILED,
  ADDFRIEND_SUCCESS,
  ADDFRIEND_FAILED,
  SENDMSG_SUCCESS,
  SENDMSG_FAILED
};

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

class ChatMsg
{
  public:
    ChatMsg():_msg_type(-1), _sockfd(-1), _user_id(-1), _reply_statu(-1)
    {
      _json_msg.clear();
    }
    ~ChatMsg()
    {

    }
  public:
    //提供一个序列化接口
    //  将成员变量的内存放到同一块连续的空间当中 
    //  send(sockfd, buf, strlen(buf), 0);
    //  msg:出参，保存序列化的内容
    bool GetMsg(string* msg)
    {
      Json::Value tmp;
      tmp["msg_type"] = _msg_type;
      tmp["user_id"] = _user_id;
      tmp["reply_statu"] = _reply_statu;
      tmp["json_msg"] = _json_msg;

      JsonUtil::Serialize(tmp, msg);
      return true;
    }

    //提供一个反序列化的接口
    //将连续的内存放到ChatMsg对象的成员变量当中去
    
    int PraseChatMsg(const std::string& msg)
    {
      Json::Value tmp;
      JsonUtil::UnSerialize(msg, &tmp);

      _msg_type = tmp["msg_type"].asInt();
      _msg_type = tmp["msg_type"].asInt();
      _user_id = tmp["user_id"].asInt();
      _reply_statu = tmp["reply_statu"].asInt();
      _json_msg = tmp["json_msg"];
      return true;
    }

    std::string GetValue(const std::string& key)
    {
      if(!_json_msg.isMember(key))
      {
        return "";
      }
      return _json_msg[key].asString();
    }

    void Clear()
    {
      _msg_type = -1;
      _user_id = -1;
      _reply_statu = -1;
      _json_msg.clear();
    }

  public:
    int _msg_type;
    //存放客户端的文件描述符，方便发送线程获取，发送数据
    int _sockfd;
    //用户ID
    int _user_id; 
    //应答状态
    int _reply_statu;
    //根据消息类型的不同，json_value的数据不一样
    Json::Value _json_msg;
};
/*    双方约定的消息内容
 *     Register:
 *      msg_type:Register 
 *      sockfd: (消息到达服务端之后， 由服务端接收之后， 再打上sockfd)
 *      json_msg:
 *      { 
 *        nickname: xxx
 *        scholl: xxx
 *        telnum: xxx 
 *        passwd: xxx
 *      }
 *
 *      Register_Resp：
 *        msg_type: Register_Resp 
 *        sockfd: 可以不要（因为这个sockfd，是服务端为客户端产生的线连接套接字，客户端没用，可以不用知道
 *        reply_statu: REGISTER_SUCCESS / REGISTER_FAILED 
 *        如果是REGISTER_SUCCESS: 应该打上user_id
 *        如果是REGISTER_FAILED: 不用打上user_id
 *
 *      Login:
 *        msg_typ = Login 
 *        sockfd:(消息到达服务端后有服务端接收后打上sockfd)
 *        json_msg: 
 *        {
 *          telnum:xxx
 *          passwd: xxx
 *        }
 *      Login_Resp:
 *        msg_type: Login_Resp 
 *        reply_statu: LOGIN_SUCCESS / LOGIN_FAILED 
 *          如果登入成功：返回user_id
 *
 *
 */
