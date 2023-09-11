#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class CGoods
{
	//三种访问限制符：public，private，protect
public:
	//成员函数，不包含在空间范围内，放在公共代码区
	void RegisterGoods(char* name, int count, float price)
	{
		strcpy(m_name,name);
		m_count = count;
		m_price = price;
	}
	//void showName(CGood*const this)this代表当前对象，不能被修改this的指向，函数能区分对象的原因
	char* showName()
	{
		return m_name;
	}
	int showCount()const //常方法
	{
		return m_count;
	}
	float showPrice()
	{
		return m_price;
	}
	float showTotalPrice()
	{
		m_totalprice = m_count * m_price;
		return m_totalprice;
	}
	//成员变量
private:
	char m_name[10];
	int m_count;
	float m_price;
	float m_totalprice;
};

class A
{
public:
	void fun()
	{
		cout << "This is const fun()" << endl;
	}
	void fun()const
	{
		cout << "This is fun()" << endl;
	}
};

class Test
{
public:
	//构造函数
	Test()
	{
		m_data = 1;
		cout << "Test()" << endl;
	}
	Test(int a)
	{
		cout << "Test(int)" << endl;
	}

	//拷贝构造
	Test(const Test& t)
	{
		m_data = t.m_data;
		cout << "Copy Create Test obj" << endl;
	}

	//赋值语句
	Test& operator=(const Test& t)
	{
		cout << "Assign" << this << "=" << &t << endl;
		if (this != &t) 
		{
			m_data = t.m_data;
		}
		return *this;
	}
	//析构函数
	~Test()
	{
		cout << "This class is freed" << endl;
	}
private:
	int m_data;
};

void main()
{
	CGoods c1;//实例化，开辟内存空间 C语言不支持空结构体，C++支持空结构体、空类，大小为1
	c1.RegisterGoods("C++", 10, 1000);
	cout << c1.showName() << endl;//c1.showName(&c1)
	cout << c1.showCount() << endl;
	cout << c1.showPrice() << endl;
	cout << c1.showTotalPrice() << endl;
	cout << sizeof(A) << endl;

	//常对象调常方法
	const A a1;
	a1.fun();
	
	A a2;
	a2.fun();

	Test t1;//调用无参构造函数
	Test t2(1);//调用一个参数构造函数
	Test t3();//函数申明
	Test t4 = t2;//用对象初始化对象时调用拷贝构造函数
	t2 = t1;//赋值
}