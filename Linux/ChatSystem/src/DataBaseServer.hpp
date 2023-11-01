/*
 *ChatSystem程序的数据库管理模块的代码
 提供操作数据库的函数给上层（用户管理模块||业务模块）
 */
#pragma once
#include <stdio.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <vector>
#include <mysql/mysql.h>
#include <string>
#include <pthread.h>
#include <mutex>
#include <unistd.h>

#define HOST "192.168.163.132"
#define USER "cqx"
#define PASSWORD "cqxctz123"
#define PORT 3306
#define DB "ChatSystem"
using namespace std;

class DataBaseServer 
{
    public: 
        DataBaseServer():_mysql(nullptr)
        {

        }

        ~DataBaseServer()
        {
          if(_mysql != nullptr)
          {
              mysql_close(_mysql);
          }
        }
    public:
        /*  1、初始化mysql操作句柄
         *  2、连接mysql的服务端
         *  3、设置连接的字符集
         */
        bool MySqlInit()
        {
          _mysql = mysql_init(NULL);
          if(_mysql == NULL)
          {
              cout << "mysql init faild" << endl;
              return false;
          }
          if(mysql_real_connect(_mysql, HOST, USER, PASSWORD, DB, PORT, NULL, 0) == NULL)
          {
              cout << "mysql connect failed" << endl;
              return false;
          }
          mysql_set_character_set(_mysql, "utf8");
          return true;
        }

#define GETALLUSER "select * from user_info;"
        bool GetAllUser(Json::Value* all_user)
        {
          //执行sql
          _lock.lock();
          if(MySqlQuery(GETALLUSER) == false)
          {
            _lock.unlock();
            return false;
          }
          MYSQL_RES* res = mysql_store_result(_mysql);
          if(res == NULL)
          {
            _lock.unlock();
            return false;
          }
          size_t rows = mysql_num_rows(res);
          for(size_t i = 0; i < rows; i++)
          {
            MYSQL_ROW row = mysql_fetch_row(res);
            //cout << row[0] << " "
            //     << row[1] << " " 
            //     << row[2] << " " 
            //     << row[3] << " " 
            //     << row[4] << endl;
            Json::Value tmp;
            tmp["userid"] = atoi(row[0]);
            tmp["nickname"] = row[1];
            tmp["school"] = row[2];
            tmp["telnum"] = row[3];
            tmp["passwd"] = row[4];
            all_user->append(tmp);
          }
          _lock.unlock();
          return false;
        }
        
#define GETFRIEND "select friend from friendinfo where userid=%d;"
        bool GetFriend(int userid, vector<int>* f_id)
        {
          //1.格式化sql语句
          char sql[1024] = {0};
          sprintf(sql, GETFRIEND, userid);
          //2.查询
          _lock.lock();
          if(MySqlQuery(sql) == false)
          {
            _lock.unlock();
            return false;
          }
          //3.获取查询结果集
          MYSQL_RES* res = mysql_store_result(_mysql);
          if(res == NULL)
          {
            _lock.unlock();
            return false;
          }
          //4.遍历获取结果集的结果
          int rows = mysql_num_rows(res);
          for(int i = 0; i < rows; i++)
          {
            MYSQL_ROW row = mysql_fetch_row(res); 
            f_id->push_back(atoi(row[0]));
          }
          _lock.unlock();
          return true;
        }

#define INSERTUSER "insert into user_info(userid, nickname, school, telnum, passwd) values(%d, '%s', '%s', '%s', '%s');"
        bool InsertUser(int userid, const string& nickname, const string& school, const string& telnum, const string& passwd)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTUSER, userid, nickname.c_str(), school.c_str(), telnum.c_str(),passwd.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTFRIEND "insert friendinfo(userid, friend) values(%d, %d);"
        bool InsertFriend(int userid, int friendid)
        {
          //格式化sql
          char sql[1024] = {0};
          sprintf(sql, INSERTFRIEND, userid, friendid);
          //执行sql
          if(MySqlQuery(sql) == false)
          {
            return false;
          }
          return true;
        }

        //向上提供接口
    private:
        bool MySqlQuery(const string& sql)
        {
          if(mysql_query(_mysql, sql.c_str()) != 0)
          {
              cout << "exec sql faild:" << sql << endl;
              return false;
          }
          return true;
        }
    private:
        //mysql的操作句柄
        MYSQL* _mysql;
        mutex _lock;
};
