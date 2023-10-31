#pragma once 
#include "DataBaseServer.hpp"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
using namespace std;

enum 
{
  OFFLINE = 0,
  ONLINE
};
class UserManager;
class UserInfo 
{
  friend class UserManager;
  public:
    UserInfo()
    {}
    UserInfo(const string& nickname, const string& school, const string& telnum, const string& passwd, int userid):_nickname(nickname), _school(school), _telnum(telnum), _passwd(passwd), _userid(userid), _user_status(OFFLINE), _tcp_socket(-1), _friend_list(10)
    {}
    ~UserInfo()
    {}
  private:
    string _nickname;
    string _school;
    string _telnum;
    string _passwd;
    int _userid;
    //用户状态
    int _user_status;
    //该用户对应的tcp的新连接套接字
    int _tcp_socket;
    //好友列表
    vector<int> _friend_list;
};

//用户信息管理类：管理多个用户的信息，提供注册、登入、校验等功能
class UserManager
{
  public:
    UserManager():_user_map(0), _pre_id(0), _dbs(nullptr)
    {}
    ~UserManager(){}

  public:
    bool InitUserManager()
    {
      //1.获取数据库管理模块的实例化指针
      _dbs = new DataBaseServer();
      //2.获取数据库管理模块进行初始化
      if(_dbs->MySqlInit() == false)
      {
        return false;
      }
      //3.查询用户信息，并维护
      //_pre_id:用户注册的时候，给用户的id
      //        1、数据库已有的用户id不能重复
      //        2、数据库已有的最大的用户id+1
      Json::Value all_user;
      _dbs->GetAllUser(&all_user);
      cout << all_user << endl;
      return true;
    }
  private:
    //key(int):用户id
    //value(UserInfo):用户信息类
    //_user_map维护的数据来源：1、从数据库的user表当中读取出来的内容 2、用户注册产生的数据
    unordered_map<int, UserInfo> _user_map;
    mutex _lock;
    //预分配的用户id，当有注册请求的时候，给新用户分配的id
    int _pre_id;
    //数据库管理模块实例化指针：1、获取用户信息2、插入数据3、查询好友
    DataBaseServer* _dbs;
};
