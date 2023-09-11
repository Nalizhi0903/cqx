#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
#define m 5
#define n 5

void Print(int (*a)[5])
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf(" %d ", a[i][j]);
		printf("\n");
	}
}

int main()
{
	int a[m][n] =
	{
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5}
	};
	Print(a);
}
