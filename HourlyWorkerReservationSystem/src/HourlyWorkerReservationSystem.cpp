#include <iostream>
#include "DataBaseServer.hpp"
// 获取当前时间
//std::time_t t = std::time(0);
//std::tm *now = std::localtime(&t);
//char buffer[80];
//strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
//std::string currentDateTime(buffer);
  
int main()
{
  DataBaseServer* db = new DataBaseServer(); 
  cout << db->MySqlInit() << endl;
  std::time_t t = std::time(0);
  std::tm *now = std::localtime(&t);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
  std::string currentDateTime(buffer);

  db->InsertDemand(1,"裁缝", 100, "编织毛衣", "广东省珠海斯香洲区招商花园村一期一栋一单元1202", currentDateTime);
  return 0;
}
