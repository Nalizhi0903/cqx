#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;


//键值对
int main()
{
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
    return 0;
}
