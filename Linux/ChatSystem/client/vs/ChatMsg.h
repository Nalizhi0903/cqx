#pragma once
#include <iostream>
#include <json.h>
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
	ADDFriend_Resp,//添加好友应答 5
	PushAddFriendMsg,//推送好友请求
	PushAddFriendMsg_Resp,//推送添加好友应答
	SendMsg,//发送消息
	SendMsg_Resp,//发送消息应答
	PushMsg,//推送数据 10
	PushMsg_Resp,//推送数据应答
	GetFriend,//获取好友信息请求                                                     
	GetFriend_Resp//获取好友信息的应答
};

enum reply_statu
{
	REGISTER_SUCCESS = 0,
	REGISTER_FAILED,
	LOGIN_SUCCESS,
	LOGIN_FAILED,
	ADDFRIEND_SUCCESS,
	ADDFRIEND_FAILED,//5
	SENDMSG_SUCCESS,
	SENDMSG_FAILED,
	GETFRIEND_SUCCESS,
	GETFRIEND_FAILED
};

class JsonUtil
{
public:
	/*
	value : 待要序列化的json对象
	body : 序列化完毕产⽣的string对象 （出参）
	*/
    static bool Serialize(const Json::Value& value, std::string* body);
	/*
	body ： 待要反序列化的string对象
	value ： 序列化完毕产⽣的json对象 （出参）
	*/
    static bool UnSerialize(const std::string& body, Json::Value* value);
};

class ChatMsg
{
public:
	ChatMsg();
	~ChatMsg();
public:
    //提供一个序列化接口
    //  将成员变量的内存放到同一块连续的空间当中 
    //  send(sockfd, buf, strlen(buf), 0);
    //  msg:出参，保存序列化的内容
    bool GetMsg(string* msg);

    //提供一个反序列化的接口
    //将连续的内存放到ChatMsg对象的成员变量当中去

    int PraseChatMsg(const std::string& msg);

    std::string GetValue(const std::string& key);

	void Clear();

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