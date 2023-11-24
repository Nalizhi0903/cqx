#include <iostream>
using namespace std;
int main()
{
  int n = 536873151;
  try 
  {
    int* ptr = new int[n];
  }
  catch(bad_alloc& e)
  {
    cout << e.what() << endl;
  }
  cout << "succeess" << endl;
  return 0;
}
/*
//自定义抛出异常
class Exception
{
public:
  Exception(const char* str):_errmsg(str)
  {

  }
public:
 string _errmsg;
 int _id;
};
class SqlException : public Exception
{
public:
  SqlException(const char* msg):Exception(msg)
  {

  }
  void fun()
  {
    throw *this;
  }
};
class CacheException : public Exception
{
public:
  CacheException(const char* msg):Exception(msg)
  {

  }
  void fun()
  {
    throw *this;
  }
};
class HttpServerException : public Exception
{};
int main()
{
 try
 {
    //SqlException sql("This is a sql error");
    //sql.fun();
    CacheException cache("This is a cache error");
    cache.fun();
 }
 catch (const Exception& e) // 这里捕获父类对象就可以
 {
    cout << e._errmsg << endl;
 }
 catch (...)
 {
 cout << "Unkown Exception" << endl;
 }
 return 0;
}
*/
/*
void fun3()
{
  cout << "This is fun3." << endl;
  throw string("thisbit");
}
void fun2()
{
  try 
  {
    fun3();
  }
  catch(const string& e)
  {
    cout << "fun2 catch a error :" << e << endl;
    throw;
  }
}
void fun1()
{
  try 
  {
    fun2();
  }
  catch(const string& e)
  {
    cout << "fun1 catch a error :" << e << endl;
    throw;
  }
}

int main()
{
  try 
  {
    fun1();
  }
  catch(const string &e)
  {
    cout << "main catch Error" << endl;
  }
  return 0;
}
*/
/*
//int Div(int a, int b)表示可以抛出一切异常
//int Div(int a, int b) throw()表示不可以抛出异常
//int Div(int a, int b) throw(int ,char ,double)表示可以抛出指定类型异常
int Div(int a, int b)
{
  if(b == 0)
  {
    throw(b);
  }
  return a/b;
}

int main()
{
  int a = 10;
  int b = 0;
  try 
  {
    int result = Div(a, b);
    std::cout << result << std::endl;
  }
  catch(int)//按类型捕获
  {
    std::cout << "除法除数为零" << std::endl;
  }
  catch(...)//处理其余类型
  {
    std::cout << "Error all" << std::endl;
  }
  std::cout << "end main" << std::endl;
  return 0;
}
*/
