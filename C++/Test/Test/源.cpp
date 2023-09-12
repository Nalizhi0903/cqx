#include <iostream>
#include <list>
using namespace std;
int main()
{
    int ar[] = { 1,2,3,4,5,6,7,8,9,10 };
    list<int> mylist(ar, ar + sizeof(ar));
    cout << "size = " << mylist.size() << endl;
    cout << "front = " << mylist.front() << endl;

    list<int>::iterator pos = find(mylist.begin(), mylist.end(), 5);

    return 0;
}