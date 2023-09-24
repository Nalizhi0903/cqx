#include <iostream>
#include <sstream>
using namespace std;



int main()
{
    //atoi字符串转换为整形
    const char* str = "12345";
    int value = atoi(str);
    //sprintf整形转换为字符串
    char buffer[20] = {0};
    sprintf(buffer, "value is %d", value);
    //stingstream可以把整数转换为字符串，多次转换用clear（）清空
    stringstream ss;
    int n = 123456;
    ss << n;
    string str_int;
    ss >> str_int;
    ss.clear();
    cout << ss.str() << endl;//clear并没有把底层string清空，可以使用s.str("")将底层的string对象
    ss.str("");
    cout << ss.str() << endl;
    //stringstream使用string类对象代替字符数组，可以避免缓冲区的危险，而且会对参数类型进行推演，不需要格式化控制，也不会出现格式化失败的风险，使用更方便安全。 
    return 0;
}
