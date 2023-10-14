#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;


//键值对
int main()
{
    set<int> is = {6,8,4,5,2,9,1};
    
    set<int>::iterator it = is.begin();
    auto Res = is.lower_bound(3);
    cout << "lower_bound:" << *Res << endl;//第一个不小于key的值
    Res = is.upper_bound(5);
    cout << "upper_bound:"<< *Res << endl;//第一个大于key的值
    
    auto start = is.find(2);
    auto end = is.find(5);
    is.erase(start, ++end);//左闭右开，[2,4,5),若要删除5要++或在寻找下一个元素
    while(it!=is.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    pair<set<int>::iterator, bool> res = is.insert(7);
    cout << *res.first << " : " << res.second << endl;
    if(res.second == true)
        cout << "Insert Succeessfully" << endl;
    else 
        cout << "Insert fail" << endl;
    
    set<int> is1{3,5,8};
    set<int> is2{7,8,9,10,32};
    is1.swap(is2);
    for(auto& e:is1)
        cout << e << endl;

    /*
    vector<int> iv = {5,9,3,2,1,7,8,4,0};
    set<int> is; 
    for(const auto& e:iv)
        is.insert(e);
    for(const auto& e:is)
        cout<< e << " ";
    cout << endl;



    pair<string,string> v[] = {{"10.1","国庆"},{"1.1","元旦"}};
    int n = sizeof(v) / sizeof(v[0]);
    for(int i = 0; i<n; ++i)
        cout << v[i].first << ":" << v[i].second << endl;
    */
    return 0;
}
