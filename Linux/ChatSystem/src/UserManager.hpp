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
  public:
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
    ~UserManager()
    {
      if(_dbs != nullptr)
      {
        delete _dbs;
      }
    }

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
      //cout << all_user.size() << endl;
      //cout << all_user << endl;
      for(int i = 0; i < (int)all_user.size(); i++)
      {
        UserInfo ui;
        ui._nickname = all_user[i]["nickname"].asString(); 
        ui._school= all_user[i]["school"].asString(); 
        ui._telnum= all_user[i]["telnum"].asString(); 
        ui._passwd= all_user[i]["passwd"].asString(); 
        ui._userid= all_user[i]["userid"].asInt(); 

        ui._user_status = OFFLINE;
        ui._tcp_socket = -1;
        _dbs->GetFriend(ui._userid, &ui._friend_list);

        _lock.lock();
        _user_map[ui._userid] = ui;
        if(ui._userid >= _pre_id)
        {
         _pre_id = ui._userid + 1; 
        }
        _lock.unlock();
      }
      //检验
      /*auto iter = _user_map.begin();
      while(iter != _user_map.end())
      {
        cout << iter->second._nickname << endl;
        iter++;
      }*/
      return true;
    }
    
    //userid：出参，用户管理模块给新用户分配的用户id，返还给上层调用者
    int DealRegister(const string& nickname, const string& school, const string& telnum, const string& passwd, int* userid)
    {
      //1.判断参数有效性
      if(nickname.size() == 0 || school.size() == 0 || passwd.size() == 0 || telnum.size() == 0)
      {
        *userid = -2;
        return -1;
      }
      //2.通过电话号码判断用户是否已经注册过
      _lock.lock();
      auto iter = _user_map.begin();
      while(iter != _user_map.end())
      {
        if(iter->second._telnum == telnum)
        {
          _lock.unlock();
          *userid = -2;
          return -2;
        }
        iter++;
      }
      _lock.unlock();
      //3.创建UserInfo，让_user_map维护起来
      _lock.lock();
      UserInfo ui(nickname, school, telnum, passwd, _pre_id);
      _user_map[ui._userid] = ui;
      *userid = _pre_id;
      _pre_id++;
      _lock.unlock();
      //4.插入用户信息到数据库
      _dbs->InsertUser(ui._userid, ui._nickname, ui._school, ui._telnum, ui._passwd);
      return 0;
    }

    int DealLogin(const string& telnum, const string& passwd, int cli_socketfd)
    {
      //1.判断参数的有效性
      if(telnum.size() == 0 || passwd.size() == 0 || cli_socketfd < 0)
      {
        return -1;
      }
      //2.判断用户是否存在
      _lock.lock();
      auto iter = _user_map.begin();
      while(iter != _user_map.end())
      {
        if(iter->second._telnum == telnum)
        {
          break;
        } 
        iter++;
      }
      if(iter == _user_map.end())
      {
        _lock.unlock();
        return -2;
      }
      //3.判断密码是否正确
      if(iter->second._passwd != passwd)
      {
        _lock.unlock();
        return -3;
      }
      //4.更改用户状态，保存新连接套接字
      iter->second._user_status = ONLINE;
      iter->second._tcp_socket = cli_socketfd;
      int userid = iter->second._userid;
      _lock.unlock();
      return userid;
  }

    int IsLogin(int userid)
    {
      _lock.lock();
      auto iter = _user_map.find(userid);
      if(iter == _user_map.end())
      {
        return -1;
      }
      if(iter->second._user_status == OFFLINE)
      {
        return -2;
      }
      _lock.unlock();
      return 0;
    }

    //添加好友接口
    void SetFriend(int user_id1, int user_id2)
    {
      //1.判断两个用户是否存在
      _lock.lock();
      auto iter1 = _user_map.find(user_id1);
      if(iter1 == _user_map.end())
      {
        _lock.unlock();
        return;
      }
      auto iter2 = _user_map.find(user_id1);
      if(iter2 == _user_map.end())
      {
        _lock.unlock();
        return;
      }
      //2.设置好友信息
      iter1->second._friend_list.push_back(user_id2);
      iter2->second._friend_list.push_back(user_id1);
      _lock.unlock();
      //3.插入数据库
      _dbs->InsertFriend(user_id1, user_id2);
      _dbs->InsertFriend(user_id2, user_id1);
    }

    int GetFriend(int userid, std::vector<int>* vt)
    {
      _lock.lock();
      auto iter = _user_map.find(userid);
      if(iter == _user_map.end())
      {
        _lock.unlock();
        return -1;
      }
      _lock.unlock();
      *vt = iter->second._friend_list;
      return 0;
    }

    int GetUserInfo(int userid, UserInfo* ui)
    {
      _lock.lock();
      auto iter = _user_map.find(userid);
      if(iter == _user_map.end())
      {
        _lock.unlock();
        return -1;
      }
      *ui = iter->second;
      _lock.unlock();
      return 0;
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
