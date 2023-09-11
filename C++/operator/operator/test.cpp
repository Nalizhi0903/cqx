#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>

using namespace std;

class MyInt
{
	friend ostream& operator<<(ostream& out, MyInt& i);
	friend istream& operator>>(istream& in, MyInt& i);
	friend MyInt operator+(int num, MyInt& i);
public:
	MyInt(int num = 0) :m_i(num)
	{}
	~MyInt()	
	{}
	MyInt operator+(const MyInt& i)
	{
		MyInt tmp(m_i + i.m_i);
		return tmp;
	}
	MyInt operator-(const MyInt& i)
	{
		MyInt tmp(m_i - i.m_i);
		return tmp;
	}
	MyInt operator*(const MyInt& i)
	{
		MyInt tmp(m_i * i.m_i);
		return tmp;
	}
	MyInt& operator++()//++a
	{
		m_i++;
		return *this;
	}
	MyInt operator++(int)//a++
	{
		MyInt tmp = *this;
		m_i++;
		return tmp;
	}
	MyInt& operator--()//--a
	{
		m_i--;
		return *this;
	}
	MyInt operator--(int)//a--
	{
		MyInt tmp = *this;
		m_i--;
		return tmp;
	}
	void showNum()
	{
		cout << m_i << endl;
	}
private:
	int m_i;
};
//友元函数访问内部私有数据
MyInt operator+(int num, MyInt& i)
{
	MyInt tmp(num + i.m_i);
	return tmp;
}

ostream& operator<<(ostream& out, MyInt& i)
{
	out << i.m_i;
	return out;
}

istream& operator>>(istream& in, MyInt& i)
{
	in >> i.m_i;
	return in;
}

void main()
{
	MyInt a = 1;
	MyInt b = 2;
	MyInt c = a + b;
	c.showNum();
	++c;
	c.showNum();
	MyInt d = 10 + c;
	cout << d << endl;
	cin >> d;
	cout << d << endl;
}



/*class String
{
public:
	String(const char* str="")
	{
		m_data = (char*)malloc(strlen(str) + 1);
		assert(m_data != nullptr);
		strcpy(m_data, str);
	}

	String(const String &str)
	{
		//m_data = str.m_data;浅拷贝
		m_data = (char*)malloc(strlen(str.m_data) + 1);
		assert(m_data != nullptr);
		strcpy(m_data, str.m_data);
		//深拷贝
	}

	String operator=(String &str)
	{
		free(m_data);
		m_data = (char*)malloc(strlen(str.m_data) + 1);
		assert(m_data != nullptr);
		strcpy(m_data, str.m_data);
	}

	void ShowStrings()
	{
		cout << m_data << endl;
	}

	~String()
	{
		free(m_data);
		m_data = nullptr;
	}
private:
	char* m_data;
};

void main()
{
	String s1("abc");
	String s2 = s1;
}*/