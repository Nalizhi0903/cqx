#include <iostream>
#include <time.h>
#include <assert.h>
#include <unistd.h>
using namespace std;

class Date

{
friend ostream& operator<<(ostream& out, Date& d);

public:

// 获取某年某月的天数

int GetMonthDay(int year, int month)
{
    static int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    int day = days[month];
    if(year % 4 == 0 && year % 100 != 0)
        day++;
    return day;
}



  // 全缺省的构造函数

Date(int year = 1900, int month = 1, int day = 1):_year(year), _month(month), _day(day)
{}


  // 拷贝构造函数

// d2(d1)

Date(const Date& d)
{
    this->_year = d._year;
    this->_month = d._month;
    this->_day = d._day;
}

   

  // 赋值运算符重载

// d2 = d3 -> d2.operator=(&d2, d3)

Date& operator=(const Date& d)
{
    this->_year = d._year;
    this->_month = d._month;
    this->_day= d._day;
    return *this;
}



  // 析构函数

~Date()
{}


  // 日期+=天数

Date& operator+=(int day)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    for(int i = 0; i < day; i++)
    {
        if(_year % 4 == 0 && _year % 100 != 0)
        {
            days[2] = 29;
        }
        else 
            days[2] = 28;
        if(_day % days[_month] == 0)
        {
            _day = 1;
            _month++;
            if(_month % 12 == 0)
            {
                _month = 1;
                _year++;
            }
        }
        else
            _day++;
    }
    return *this;
}


  // 日期+天数

Date operator+(int day) 
{
    Date tmpDate(_year, _month, _day);
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    for(int i = 0; i < day; i++)
    {
        if(tmpDate._year % 4 == 0 && tmpDate._year % 100 != 0)
        {
            days[2] = 29;
        }
        else 
            days[2] = 28;
        if(tmpDate._day % days[_month] == 0)
        {
            tmpDate._day = 1;
            tmpDate._month++;
            if(tmpDate._month % 12 == 0)
            {
                tmpDate._month = 1;
                tmpDate._year++;
            }
        }
        else
            tmpDate._day++;
    }
    return tmpDate;
}



  // 日期-天数

Date operator-(int day)
{
    Date tmpDate(_year, _month, _day);
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    for(int i = 0; i < day; i++)
    {
        tmpDate._day--;
        if(tmpDate._year % 4 == 0 && tmpDate._year % 100 != 0)
        {
            days[2] = 29;
        }
        else 
            days[2] = 28;
        if(tmpDate._day == 0)
        {
            tmpDate._day = days[_month - 1];
            tmpDate._month--;
            if(tmpDate._month == 0)
            {
                tmpDate._month = 12;
                tmpDate._year--;
            }
        }
    }
    return tmpDate;
}

   // 日期-=天数

Date& operator-=(int day)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    for(int i = 0; i < day; i++)
    {
        _day--;
        if(_year % 4 == 0 && _year % 100 != 0)
        {
            days[2] = 29;
        }
        else 
            days[2] = 28;
        if(_day == 0)
        {
            _day = days[_month - 1];
            _month--;
            if(_month == 0)
            {
                _month = 12;
                _year--;
            }
        }
    }
    return *this;
}



  // 前置++

Date& operator++()
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    if(_year % 4 == 0 && _year % 100 != 0)
        {
            days[2] = 29;
        }
        else 
            days[2] = 28;
        if(_day % days[_month] == 0)
        {
            _day = 1;
            _month++;
            if(_month % 12 == 0)
            {
                _month = 1;
                _year++;
            }
        }
        else
            _day++;
    return *this;
}


  // 后置++

Date operator++(int)
{
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    if(_year % 4 == 0 && _year % 100 != 0)
        {
            days[2] = 29;
        }
    else 
        days[2] = 28;
    if(_day % days[_month] == 0)
    {
        _day = 1;
        _month++;
        if(_month % 12 == 0)
        {
            _month = 1;
            _year++;
        }
    }
    else
        _day++;
    return *this;
}



  // 后置--

Date operator--(int)
{
    _day--;
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    if(_year % 4 == 0 && _year % 100 != 0)
    {
        days[2] = 29;
    }
    else 
        days[2] = 28;
    if(_day == 0)
    {
        _day = days[_month - 1];
        _month--;
        if(_month == 0)
        {
            _month = 12;
            _year--;
        }
    }
    return *this;
}



  // 前置--

Date& operator--()
{
    _day--;
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    if(_year % 4 == 0 && _year % 100 != 0)
    {
        days[2] = 29;
    }
    else 
        days[2] = 28;
    if(_day == 0)
    {
        _day = days[_month -1];
        _month--;
        if(_month == 0)
        {
            _month = 12;
            _year--;
        }
    }
    return *this;
}



  // >运算符重载

bool operator>(const Date& d)
{
    if(_year > d._year)
        return true;
    if(_year == d._year && _month > d._month)
        return true;
    if(_year == d._year && _month == d._month && _day > d._day)
        return true;
    return false;
}


  // ==运算符重载

bool operator==(const Date& d)
{
    if(_year == d._year && _month == d._month && _day == d._day)
        return true;
    return false;
}


  // >=运算符重载

bool operator >= (const Date& d)
{
    if(_year > d._year)
        return true;
    if(_year == d._year &&_month > d._month)
        return true;
    if(_year >= d._year && _month >= d._month && _day > d._day)
        return true;
    return false;
}

   

  // <运算符重载

bool operator < (const Date& d)
{
    if(_year < d._year)
        return true;
    if(_year == d._year && _month < d._month)
        return true;
    if(_year == d._year && _month == d._month && _day < d._day)
        return true;
    return false;
}



   // <=运算符重载

bool operator <= (const Date& d)
{
    if(_year < d._year)
        return true;
    if(_year == d._year &&_month < d._month)
        return true;
    if(_year <= d._year && _month <= d._month && _day < d._day)
        return true;
    return false;
}



  // !=运算符重载

bool operator != (const Date& d)
{
    if(_year == d._year && _month == d._month && _day == d._day)
        return false;
    return true;
}


  // 日期-日期 返回天数

int operator-(const Date& d)
{
    if(*this > d)
        return 0;
    Date tmpDate(_year, _month, _day);
    cout << tmpDate;
    int day = 0;
    int days[13] = {0, 31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 ,31};
    while(tmpDate._year != d._year || tmpDate._month != d._month || tmpDate._day != d._day)
    {
        day++;
        if(tmpDate._year % 4 == 0 && tmpDate._year % 100 != 0)  
            days[2] = 29;
        else 
            days[2] = 28;
        if(tmpDate._day % days[_month] == 0)
        {
            tmpDate._day = 1;
            tmpDate._month++;
            if(tmpDate._month % 12 == 0)
            {
                tmpDate._month = 1;
                tmpDate._year++;
            }
        }
        else
            tmpDate._day++;
    }
    return day;
}

private:

int _year;

int _month;

int _day;

};

ostream& operator<<(ostream& out, Date& d)
{
    out << d._year << "-" << d._month << "-" << d._day << endl;
    return out;
}

int main()
{
    Date d1;
    cout << d1;
    cout << d1.GetMonthDay(1900, 3) << endl;;
    Date d2(d1);
    cout << d2;
    Date d3;
    d3 = d2;
    cout << d3;
    Date d4(2012, 2, 28);
    cout << d4;
    d4+=5;
    cout << d4;
    Date d5 = d4 + 10;
    cout << d5;
    Date d6(2012, 3, 1);
    Date d7 = (d6 - 1000);
    cout << d7;
    Date d8(2012, 3, 1);
    d8 -= 1;
    cout << d8;
    ++d8;
    cout << d8;
    d8++;
    cout << d8;
    d8--;
    cout << d8;
    --d8;
    cout << d8;
    Date d9(2024, 9, 3);
    Date d10(2077, 10, 8);
    cout << (d9>d10) << endl;
    cout << (d10==d9) << endl;
    cout << (d10>d9) << endl;
    cout << (d10>=d9) << endl;
    cout << (d10!=d9) << endl;
    cout << d9 - d10 << endl;
    return 0;
}
