#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>

int Fact(int n)
{
	if (n == 1)
		return 1;
	else return n * (Fact(n - 1));
}



bool IsPrime(int value)
{
	int  i = 0;

	for (i = 2; i < value;i++)
	{
		if (value % i == 0)
		{
			return false;
		}
	}
	return true;
}

int BinaryFind(int ar[], int n,char x)
{
	int left = 0;
	int right = n - 1;
	while (left<=right)
	{
		int mid = (left + right) / 2;
		if (ar[mid] == x)
			return mid;
		if (ar[mid] < x)
			left = mid+1;
		else right = mid-1;
	}
}

bool IsLeap(int year)
{
	if ((year % 4 == 0 && year % !100)||(year %400==0))
		return true;
	else return false;
}

void main()
{
	int value,year;
	scanf_s("%d", &value);
	bool flag = IsPrime(value);
	if (flag)
		printf("素数");
	else printf("不是素数");
	scanf_s("%d", &year);
	bool Flag = IsLeap(year);
	if (Flag)
		printf("闰年");
	else printf("不是闰年");
}

//void swap(int* a, int* b)
//{
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//int main()
//{
//	int a,b;
//	a = 10, b = 20;
//	swap(&a, &b);
//	printf("%d\n%d", a, b);
//}