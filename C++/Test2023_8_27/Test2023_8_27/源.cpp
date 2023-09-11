#include <iostream>
using namespace std;

//char Fun(char a, char b);

extern "C" void fun()
{
	printf("Extern C");
}

int Max(int a, int b) 
{
	return a > b ? a : b;
}

char Max(char a, char b)
{
	return a > b ? a : b;
}

const char* Max(const char *a, const char *b)
{
	int res = strcmp(a, b);
	if (res > 0)
		return a;
	return b;
}

void main()
{
	int a = 10;
	int b = 10;
	fun();
	//Fun(a, b);
	/*cout << Max('a', 'b') << endl;
	cout << Max(12, 32) << endl;
	cout << Max("abc","xyz") << endl;*/
}
/*
void main()
{
	char ch;
	int i;
	double d;
	printf("Hello world\n");

	//输出运算符 插入符
	cout << "Hello world" << endl;

	//输入运算符 提取符
	cin >> ch >> i >> d;
}
*/