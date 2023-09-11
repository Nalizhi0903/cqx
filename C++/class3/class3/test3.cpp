#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>

using namespace std;
class String;
//引用计数器
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
		//写实拷贝
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
	Test(int a):m_data(5), m_a(20), ref(a)//参数列表初始化，引用成员和const类型只能用参数列表初始化
	{
		m_data = 10;//赋值
		count++;
	}

	static int GetCount()//静态方法调不动普通变量，因为没有*this指针,只能调用静态变量
	{
		return count;
	}
	~Test()
	{
		count--;
	}
private:
	int m_data = 10;//默认的缺省值
	const int m_a;
	int& ref;
	static int count;
	static int value;//静态成员节省空间，所有成员共享，静态成员改变所有类都改变,初始化放在类外
};

int Test::value = 100;
int Test::count = 0;

void main()
{
	Test t1(1);
	Test t2(2);

	{
		Test t3(3);
		cout << Test::GetCount() << endl;//t3在作用域结束后通过析构函数释放掉了
	}

	cout << Test::GetCount() << endl ;;//类名加函数直接访问
}
*/