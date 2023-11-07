#include "DataBaseServer.hpp"
#include "UserManager.hpp"
#include "ChatServer.hpp"
#include "ChatMsg.hpp"
int main()
{

  //ChatMsg cm;
  //cm._msg_type = Register;
  //cm._sockfd = 5;
  //cm._user_id = -1;
  //cm._reply_statu= -1;
  //cm._json_msg["nickname"] = "cqx";
  //cm._json_msg["school"] = "bite";
  //cm._json_msg["passwd"] = "903602";
  //std::string msg;
  //cm.GetMsg(&msg);

  //std::cout << msg << std::endl;

  
  ChatServer cs;
  int ret = cs.InitChatServer();
  if(ret < 0)
  {
    cout << "init ChatServer failed" << endl;
    cout << ret << endl;
    return 0;
  }
  ret = cs.startChatSever();
  if(ret < 0)
  {
    cout << ret << endl;
    cout << "start server failed" << endl;
    return 0;
  }
  return 0;
  
  //UserManager user;
  //user.InitUserManager();
  //线程安全队列
  //MsgQueue<int> ms;
  //ms.Push(10);
  //int ret;
  //ms.Pop(&ret);
  //添加朋友
  //user.SetFriend(6,7);
  //登入
  //int ret = user.DealLogin("13672678168", "cqxctz123", 5);
  //if(ret < 0)
  //{
  //  cout << "login failed" << endl;
  //}
  //else 
  //{
  //  cout << "login successed" << endl;
  //}
  //注册用户测试
  //int user_id =-1;
  //int ret = user.DealRegister("DY", "bite", "1111111111", "88883333", &user_id);
  //if(ret < 0)
  //{
  //  cout << "DealRegister failed" << endl;
  //  if(ret == -1)
  //    cout << "Wrong Format" << endl;
  //  if(ret == -2)
  //    cout << "User Exist" <<endl;
  //}
  //else
  //  cout << ("DealRegister successed") << endl;  
  return 0;
}
#if 0
int main()
{
  DataBaseServer dbs;
  if(!dbs.MySqlInit())
  {
    cout << "MysqlInit failed" << endl;
    return 0;
  }
  vector<int> f_id;
  if(!dbs.GetFriend(2, &f_id))
  {
    cout << "GetFriend failed" << endl;
    return 0;
  }
  for(size_t i = 0; i <f_id.size(); i++)
  {
    cout << f_id[i] << " ";
  }
  cout << endl;
  /* 
   *插入用户信息
  if(!dbs.InsertUser(5, "djt", "xaufe", "13538829343", "djt3422"))
  {
    cout << "Insert User falied" << endl;
    return 0;
  }
  */
  /*添加好友
  if(!dbs.InsertFriend(5, 1))
  {
    cout << "Insert friend failed" << endl;
  }
  */
  dbs.GetAllUser();
  return 0;
}
#endif
