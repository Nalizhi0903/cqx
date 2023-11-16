#include "pch.h"
#include "ChatMsg.h"

bool JsonUtil::Serialize(const Json::Value& value, std::string* body)
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

bool JsonUtil::UnSerialize(const std::string& body, Json::Value* value)
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

ChatMsg::ChatMsg() :_msg_type(-1), _sockfd(-1), _user_id(-1), _reply_statu(-1)
{
    _json_msg.clear();
}

ChatMsg::~ChatMsg()
{

}

bool ChatMsg::GetMsg(string* msg)
{
    Json::Value tmp;
    tmp["msg_type"] = _msg_type;
    tmp["user_id"] = _user_id;
    tmp["reply_statu"] = _reply_statu;
    tmp["json_msg"] = _json_msg;

    JsonUtil::Serialize(tmp, msg);
    return true;
}

int ChatMsg::PraseChatMsg(const std::string& msg)
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

std::string ChatMsg::GetValue(const std::string& key)
{
    if (!_json_msg.isMember(key))
    {
        return "";
    }
    return _json_msg[key].asString();
}

void  ChatMsg::Clear()
{
    _msg_type = -1;
    _user_id = -1;
    _reply_statu = -1;
    _json_msg.clear();
}