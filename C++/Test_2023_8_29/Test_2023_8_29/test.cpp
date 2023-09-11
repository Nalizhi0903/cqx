#include <iostream>
#include <time.h>
using namespace std;

void Swap(int& a, int& b)//传递引用，而不是地址
{
	int tmp = a;
	a = b;
	b = tmp;
}

int count()
{
	int n = 0;
	n++;
	return n;//n是局部变量在return的刹那释放掉，创建临时变量，将n的值赋给临时变量，临时变量将值返回
}

//引用返回可以提升效率，但容易出错
int& Count()
{
	static int n = 0;
	n++;
	return n;//n是引用，不会开辟临时空间使得效率提高，用static可以保证n不被释放，没有static则会被释放
}

//传值和传递引用的区别
struct A { int a[100000]; };
void TestFunc1(A a) {}
void TestFunc2(A& a) {}
void TestRefAndValue()
{
	A a;
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000; i++)
		TestFunc1(a);
	size_t end1 = clock();

	size_t begin2 = clock();
	for (size_t i = 0; i < 1000; i++)
		TestFunc2;
	size_t end2 = clock();

	cout << "TestFunc1(A)-Time:" << end1 - begin1 << endl;
	cout << "TestFunc2(A)-Time:" << end2 - begin2 << endl;
}

void circle()
{
	int ar[] = { 1,2,3,4,5 };
	for (const auto& e : ar)
		cout << e << " ";
	cout << endl;	
}

void main()
{
	//引用
	int a = 10;
	int& b = a;
	cout << b << endl;
	b = 20;
	cout << a << endl;
	
	//指针的引用
	int* pa = &a;
	int*& pr = pa;
	cout << &pa << endl;
	cout << &pr << endl;

	//数组的引用
	int ar[] = { 1,2,3,4,5 };
	int(&br)[5] = ar;//数组的中括号优先级比引用符号高，所以用小括号包起来
	for (int i = 0; i < 5; i++)
	{
		cout << br[i] << endl;
	}

	/*
	不允许引用常量
	const int A = 10;
	int &B = A;
	*/
	//允许常引用引用变量或常量
	int A = 10;
	const int& B = A;
	
	/*
	double转换int损失精度，会创造临时变量赋值12，临时变量或对象都有一个特点，具有常性
	故不允许引用变量
	double C = 12.34;
	int& D = C;
	*/
	double C = 12.34;
	const int& D = C;

	int E = 12;
	int& F = E;

	TestRefAndValue();

	circle();

}