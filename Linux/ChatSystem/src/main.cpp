#include "DataBaseServer.hpp"
#include "UserManager.hpp"

int main()
{
  UserManager user;
  user.InitUserManager();
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
