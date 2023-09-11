#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>

using namespace std;
class String;
//���ü�����
class String_rep
{
	friend ostream& operator<<(ostream& out, const String& s);
	friend class String;
public:
	String_rep(const char* str = "")
	{
		m_data = new char[strlen(str) + 1];
		strcpy(m_data, str);
		increment();
	}
	String_rep(const String_rep& rep);
	String_rep& operator=(const String_rep& s);
	~String_rep()
	{
		delete[]m_data;
		m_data = NULL;
	}

	void increment()
	{
		use_count++;
	}

	void decrement()
	{
		if (--use_count == 0)
		{
			delete this;
		}
	}

private:
	char* m_data;
	int use_count;
};

class String
{
	friend ostream& operator<<(ostream& out,const String &s);
public:
	String(const char* str = "")
	{
		rep = new String_rep(str);
	}
	String(const String& s)
	{
		rep = s.rep;
		rep->increment();
	}
	String& operator=(String& s)
	{
		rep->decrement();
		rep = s.rep;
		rep->increment();
		return *this;
	}
	~String()
	{
		rep->decrement();
	}

	void to_upper()
	{
		//дʵ����
		if (rep->use_count > 1)
		{
			String_rep* new_rep = new String_rep(rep->m_data);
			rep->decrement();
			rep = new_rep;
			rep->increment();
		}

		char* ch = rep->m_data;
		while( *ch != '\0')
		{
			if (*ch >= 'a' && *ch <= 'z')
			{
				*ch -= 32;
				ch++;
			}
		}
	}
private:
	String_rep* rep;
};

ostream& operator<<(ostream& out, const String& s)
{
	out << s.rep->m_data;
	return out;
}

void main()
{
	String s1("abc");
	String s2 = s1;
	String s3;
	s3 = s1;
	cout << s3;
	s3.to_upper();
	cout << s3;
}


/*
class Test
{
public:
	Test(int a):m_data(5), m_a(20), ref(a)//�����б��ʼ�������ó�Ա��const����ֻ���ò����б��ʼ��
	{
		m_data = 10;//��ֵ
		count++;
	}

	static int GetCount()//��̬������������ͨ��������Ϊû��*thisָ��,ֻ�ܵ��þ�̬����
	{
		return count;
	}
	~Test()
	{
		count--;
	}
private:
	int m_data = 10;//Ĭ�ϵ�ȱʡֵ
	const int m_a;
	int& ref;
	static int count;
	static int value;//��̬��Ա��ʡ�ռ䣬���г�Ա������̬��Ա�ı������඼�ı�,��ʼ����������
};

int Test::value = 100;
int Test::count = 0;

void main()
{
	Test t1(1);
	Test t2(2);

	{
		Test t3(3);
		cout << Test::GetCount() << endl;//t3�������������ͨ�����������ͷŵ���
	}

	cout << Test::GetCount() << endl ;;//�����Ӻ���ֱ�ӷ���
}
*/