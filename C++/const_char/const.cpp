#include <iostream>
using namespace std;
int main()
{
	//字符指针可以修改，指针指向常量
	const char* str = "linux";
	str = "1234";
	//str[0] = 'a';不允许
	 
	
	//字符指针不可以修改
	const char* const str1 = "bite";
	//str1 = str; 不允许
    return 0;
}
