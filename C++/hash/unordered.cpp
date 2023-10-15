#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_set<int> uset = {4,8,3,2,7,9,1};
    unordered_set<int>::iterator it = uset.begin();
    unordered_multimap<int,string> ump = {{3,"cqx"},{3,"cqx"},{3,"cqx"},{3,"cqx"}};
    
    cout << uset.size() << endl;
    cout << uset.bucket_count() << endl;
    cout << uset.bucket_size(5) << endl;
    while(it!=uset.end())
    {
        cout << *it << "  ";
        it++;
    }
    cout << endl;
    return 0;
}
