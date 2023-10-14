#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    map<int,string,greater<int>> ismap = {{2,"zeus"},{1,"faker"},{3,"chovy"},{4,"uzi"}};//降序
    ismap[20] = "Guma";//如果关键值不存在，只要访问了，会当作新值插入，默认值为空，而at()函数则会报错
    map<int,string>::iterator it = ismap.begin();
    while(it!=ismap.end())
    {
        cout << (*it).first<< ":" << (*it).second << endl;
        it++;
    }
    ismap[4] = "CJB";
    cout << ismap[4] << endl;
    cout << ismap.count(1) << endl;//统计关键字出现的次数
    return 0;
}
