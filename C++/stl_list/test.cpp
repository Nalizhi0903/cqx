#include "test.h"

int main()
{
    SeqList<int> mylist;
    SeqList<int> yourlist(100);
    yourlist.show_size();
    yourlist.show_capacity();
    return 0;
}
