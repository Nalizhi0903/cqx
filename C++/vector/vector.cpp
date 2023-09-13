#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //空间按照原码的倍数增长,一般扩容而不缩容
    vector<int> v;
    cout << v.size() << endl;
    cout << v.capacity() <<endl;
    
    v.push_back(1);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;

    v.push_back(2);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;
    
    v.push_back(3);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;

    v.push_back(4);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;

    v.push_back(5);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;
    
    v.push_back(6);
    cout << v.size() << endl;
    cout << v.capacity() <<endl;
    
    for(const auto &e : v)
    {
        cout<< e << endl;
    }
    
    vector<int> iv = {1,2,3,4,5,6,7,8,9,10};
    auto it1 = iv.begin();
    iv.push_back(20);//原来空间满了，为了插入新元素，释放原来的空间，开更大的新空间，导致迭代器失效
    it1 = iv.begin();//需重新赋值
    *it1= 100;
    cout << iv.size() << endl;
    cout << iv.capacity() <<endl;
    iv.erase(it1);//erase后，迭代器失效，为了防止删除的是最后一个元素导致迭代器指向未知的空间，一律统一失效,前面的迭代器不失效，处于元素后面的迭代器失效
    
    return 0;
}
