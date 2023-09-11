#include <iostream>
#include <time.h>
using namespace std;

void Swap(int& a, int& b)//�������ã������ǵ�ַ
{
	int tmp = a;
	a = b;
	b = tmp;
}

int count()
{
	int n = 0;
	n++;
	return n;//n�Ǿֲ�������return��ɲ���ͷŵ���������ʱ��������n��ֵ������ʱ��������ʱ������ֵ����
}

//���÷��ؿ�������Ч�ʣ������׳���
int& Count()
{
	static int n = 0;
	n++;
	return n;//n�����ã����Ὺ����ʱ�ռ�ʹ��Ч����ߣ���static���Ա�֤n�����ͷţ�û��static��ᱻ�ͷ�
}

//��ֵ�ʹ������õ�����
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
	//����
	int a = 10;
	int& b = a;
	cout << b << endl;
	b = 20;
	cout << a << endl;
	
	//ָ�������
	int* pa = &a;
	int*& pr = pa;
	cout << &pa << endl;
	cout << &pr << endl;

	//���������
	int ar[] = { 1,2,3,4,5 };
	int(&br)[5] = ar;//��������������ȼ������÷��Ÿߣ�������С���Ű�����
	for (int i = 0; i < 5; i++)
	{
		cout << br[i] << endl;
	}

	/*
	���������ó���
	const int A = 10;
	int &B = A;
	*/
	//�����������ñ�������
	int A = 10;
	const int& B = A;
	
	/*
	doubleת��int��ʧ���ȣ��ᴴ����ʱ������ֵ12����ʱ�����������һ���ص㣬���г���
	�ʲ��������ñ���
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