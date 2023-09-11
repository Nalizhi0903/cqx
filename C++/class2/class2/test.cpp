#include <iostream>
using namespace std;

//任何类都会默认生成6个函数
class Test
{
public:
	//构造函数，生命周期内只调用一次,承担初始化作用,函数名和类名相同
	
	Test()
	{

	}

	Test(int data)
	{
		m_data = data;
		m_ptr = (int*)malloc(sizeof(int));
		*m_ptr = data;
	}
	
	//拷贝构造函数,只有一个形参，且是引用
	Test(const Test &t)
	{
		m_data = t.m_data;
	}

	//赋值函数
	Test& operator=(const Test& t)//引用返回 传入引用参数
	{
		if (this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}

	//析构函数，不能重载
	~Test()
	{
		free(m_ptr);
		m_ptr = nullptr;
	}

	//Test const* this
	int GetData()
	{
		return m_data;
	}

	//const Test const* this
	int GetData()const
	{
		//fun();
		//不可以接受可改变的地址
	}

	void fun()
	{
		GetData();
		//可以接受不可改变的地址
	}

	void showData()
	{
		cout << m_data << endl;
	}

	Test* operator& ()
	{
		return this;
	}

	//对常对象取地址的常方法
	const Test* operator&()const
	{
		return this;
	}

private:
	int m_data;
	int* m_ptr;
};

Test Fun(Test x)//为x创建临时空间，调用一次拷贝函数
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;//返回时调用一次拷贝函数
}

void main()
{
	Test t1(10);
	Fun(t1);
	Test t2;
	t2 = t1;
	t2.showData();

	Test* t = &t1;

	Test t3;
	Test* t4 = &t3;
	//对常对象取地址的常方法	
	const Test t5;
	const Test* t6 = &t5;
}