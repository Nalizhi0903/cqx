#include <iostream>
#include <stdlib.h>
using namespace std;
//定位new，构造一个对象
class Test
{
    friend void* operator new(size_t st, Test* t, int pos);
public:
    Test(int data)
    {
        m_data = data;
    }
private:
    int m_data;
};

void* operator new(size_t st, Test* t, int pos)
{
    return &t[pos];
}

int main()
{
    Test* t = (Test*)malloc(4*sizeof(Test));
    new(t, 2) Test(1);
    return 0;
}

/*
//new可以初始化
int main()
{
    int* a= new int[10]{1,2,3,4,5,6,7,8,9};
    return 0;
}
/*
void my_fun(void)
{
    cout<<"this is a bad alloc"<<endl;
    exit(1);
}

int main()
{
    set_new_handler(my_fun);

    int* p = new int[53687091111];

    cout << "Memory OK." << endl;
}

/*
int main()
{
    //抛出异常
    try
    {
        int* p = new int[511111111111111111];
        cout << "Memory Ok" << endl;
    }
    catch(bad_alloc &e)
    {
        cout << "Out of Memory" << endl;
    }
    return 0;
}


/*
class Test
{
    friend ostream& operator<<(ostream& out, Test &t);
public:
    Test(int data)
    {
        m_data=(int*)malloc(sizeof(int));
        *m_data = data;
    }
    ~Test()
    {
        free(m_data);
    }
private:
    int* m_data;
};

ostream& operator<<(ostream& out, Test &t)
{
    out<<*t.m_data;
    return out;
}

void* operator new(size_t sz, int* ar, int pos)
{
    return &ar[pos];
}

int main()
{
    
    Test* t = new Test(3);
    char* ptr = new (char);
    new(ptr)int(1);//定位new，对原有空间调用构造函数初始化一个对象

    int ar[10]= {1,2,3,4,5,6,7,8,9,10};
    new(ar, 8) int (99);

    return 0;
}


/*
int main()
{
     int* ptr = (int*)calloc(5,sizeof(int));
     int* tmp = (int*)realloc(ptr, sizeof(int)*10);//realloc会释放原来的空间
     if(tmp != NULL)//防止空间申请失败，又释放ptr
     {
         ptr = tmp;
     }
     cout << sizeof(ptr) << endl;
     return 0;
}
*/
