#include <iostream>
using namespace std;

//�κ��඼��Ĭ������6������
class Test
{
public:
	//���캯��������������ֻ����һ��,�е���ʼ������,��������������ͬ
	
	Test()
	{

	}

	Test(int data)
	{
		m_data = data;
		m_ptr = (int*)malloc(sizeof(int));
		*m_ptr = data;
	}
	
	//�������캯��,ֻ��һ���βΣ���������
	Test(const Test &t)
	{
		m_data = t.m_data;
	}

	//��ֵ����
	Test& operator=(const Test& t)//���÷��� �������ò���
	{
		if (this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}

	//������������������
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
		//�����Խ��ܿɸı�ĵ�ַ
	}

	void fun()
	{
		GetData();
		//���Խ��ܲ��ɸı�ĵ�ַ
	}

	void showData()
	{
		cout << m_data << endl;
	}

	Test* operator& ()
	{
		return this;
	}

	//�Գ�����ȡ��ַ�ĳ�����
	const Test* operator&()const
	{
		return this;
	}

private:
	int m_data;
	int* m_ptr;
};

Test Fun(Test x)//Ϊx������ʱ�ռ䣬����һ�ο�������
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;//����ʱ����һ�ο�������
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
	//�Գ�����ȡ��ַ�ĳ�����	
	const Test t5;
	const Test* t6 = &t5;
}