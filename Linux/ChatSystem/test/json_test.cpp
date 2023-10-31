#include <jsoncpp/json/json.h>
#include <iostream>
using namespace std;
int main()
{
  Json::Value v;
  v["nickname"] = "wudu";
  v["schol"] = "bite";
  v["telnum"] = "7777777";
  v["passwd"] = "123456";
  cout << v << endl;
  Json::Value v1;
  v["nickname"] = "bss";
  v["schol"] = "bite";
  v["telnum"] = "6666666";
  v["passwd"] = "654321";
  cout << v << endl;
  Json::Value vv;
  vv.append(v);
  vv.append(v1);
  cout << vv << endl;
  return 0;
}
