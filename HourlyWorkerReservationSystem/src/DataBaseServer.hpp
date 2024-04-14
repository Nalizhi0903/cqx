/*
 * HourlyWorkerReservationSystem的数据库管理模块的代码
 * 提供操作数据库的函数给上层（用户管理模块||业务模块）
*/ 

#include <iostream>
#include <mutex>
#include <vector>
#include <mysql/mysql.h>
#include <unistd.h>
#include <string>
#include <jsoncpp/json/json.h>

#define HOST "192.168.163.132"
#define USER "root"
#define PASSWORD "cqxctz123"
#define PORT 3306
#define DB "HourlyWorkerReservationSystem"

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
#define INSERTCUSTOMER "insert into customer(username, password, phonenumber, sex, status) values('%s', '%s', '%s', '%s', '%s');"
        bool InsertCustomer(const string& username, const string& password, const string& phonenumber, const string& sex, const string& user_status)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTCUSTOMER, username.c_str(), password.c_str(), phonenumber.c_str(),sex.c_str(), user_status.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTHOURLYWORKER "insert into hourlyworker(username, password, phonenumber, sex, jobtype, status) values('%s', '%s', '%s', '%s', '%s', '%s');"
        bool InsertHourlyWorker(const string& username, const string& password, const string& phonenumber, const string& sex, const string& jobtype, const string& user_status)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTHOURLYWORKER, username.c_str(), password.c_str(), phonenumber.c_str(),sex.c_str(), jobtype.c_str(), user_status.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTJOB "insert into job(workerid, jobtype, price, jobcontent, time) values('%d', '%s', '%d', '%s', '%s');"
        bool InsertJob(int workerid, const string& jobtype, int price, const string& jobcontent, const string& time)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTJOB, workerid, jobtype.c_str(), price, jobcontent.c_str(), time.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTORDER "insert into orders(customerid, workerid, jobid, createtime, finishtime, worktime, status, place, jobcontent) values('%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%s');"
        bool InsertOrder(int customerid, int workerid, int jobid, const string& createtime, const string& finishtime, const string& worktime, const string& order_status, const string& place, const string& jobcontent)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTORDER, customerid, workerid, jobid, createtime.c_str(), finishtime.c_str(), worktime.c_str(), order_status.c_str(), place.c_str(), jobcontent.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTSUBSCRIBE "insert into subscribe(customerid, workerid)values('%d', '%d');"
        bool InsertSubScribe(int customerid, int workerid)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTSUBSCRIBE, customerid, workerid);
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTMESSAGE "insert into message(customerid, workerid, message, time)values('%d', '%d', '%s', '%s');"
        bool InsertMessage(int customerid, int workerid, const string& message, const string& time)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTMESSAGE, customerid, workerid, message.c_str(), time.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTCOMMENT "insert into comment(customerid, workerid, orderid, time, comment)values('%d', '%d', '%d', '%s', '%s');"
        bool InsertComment(int customerid, int workerid, int orderid, const string& time, const string& comment)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTCOMMENT, customerid, workerid, orderid, time.c_str(), comment.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTPOSTING "insert into posting(workerid, time, content, pictrue)values('%d', '%s', '%s', '%s');"
        bool InsertPosting(int workerid, const string& time, const string& content, const string& pictrue)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTPOSTING, workerid, time.c_str(), content.c_str(), pictrue.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
#define INSERTDEMAND "insert into demand(customerid, jobtype, price, jobcontent, place, worktime)values('%d', '%s', '%d', '%s', '%s', '%s');"
        bool InsertDemand(int customerid, const string& jobtype, int price, const string& jobcontent, const string& place, const string& worktime)
        {
          //格式化sql
          char sql[1024] = {0}; 
          sprintf(sql, INSERTDEMAND, customerid, jobtype.c_str(), price, jobcontent.c_str(), place.c_str(), worktime.c_str());
          //执行sql
          if(mysql_query(_mysql, sql) == false)
          {
            return false;
          }
          return true;
        }
  private:
  MYSQL* _mysql;
  mutex _lock;  
};
