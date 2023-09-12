#include <iostream>
#include <time.h>
#include <assert.h>
using namespace std;

class Date
{
    friend ostream& operator<<(ostream& out,Date& d);
public:
    Date(int year, int month, int day):m_year(year), m_month(month), m_day(day)
    {

    }

    Date(const Date & d)
    {
        
    }

    ~Date()
    {

    }
private:
    int m_year;
    int m_month;
    int m_day;
};

int main()
{
    
}int m_year;
    int m_month;
    int m_day;
