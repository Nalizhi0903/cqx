#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class CGoods
{
	//���ַ������Ʒ���public��private��protect
public:
	//��Ա�������������ڿռ䷶Χ�ڣ����ڹ���������
	void RegisterGoods(char* name, int count, float price)
	{
		strcpy(m_name,name);
		m_count = count;
		m_price = price;
	}
	//void showName(CGood*const this)this����ǰ���󣬲��ܱ��޸�this��ָ�򣬺��������ֶ����ԭ��
	char* showName()
	{
		return m_name;
	}
	int showCount()const //������
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
	//��Ա����
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
	//���캯��
	Test()
	{
		m_data = 1;
		cout << "Test()" << endl;
	}
	Test(int a)
	{
		cout << "Test(int)" << endl;
	}

	//��������
	Test(const Test& t)
	{
		m_data = t.m_data;
		cout << "Copy Create Test obj" << endl;
	}

	//��ֵ���
	Test& operator=(const Test& t)
	{
		cout << "Assign" << this << "=" << &t << endl;
		if (this != &t) 
		{
			m_data = t.m_data;
		}
		return *this;
	}
	//��������
	~Test()
	{
		cout << "This class is freed" << endl;
	}
private:
	int m_data;
};

void main()
{
	CGoods c1;//ʵ�����������ڴ�ռ� C���Բ�֧�ֿսṹ�壬C++֧�ֿսṹ�塢���࣬��СΪ1
	c1.RegisterGoods("C++", 10, 1000);
	cout << c1.showName() << endl;//c1.showName(&c1)
	cout << c1.showCount() << endl;
	cout << c1.showPrice() << endl;
	cout << c1.showTotalPrice() << endl;
	cout << sizeof(A) << endl;

	//�������������
	const A a1;
	a1.fun();
	
	A a2;
	a2.fun();

	Test t1;//�����޲ι��캯��
	Test t2(1);//����һ���������캯��
	Test t3();//��������
	Test t4 = t2;//�ö����ʼ������ʱ���ÿ������캯��
	t2 = t1;//��ֵ
}