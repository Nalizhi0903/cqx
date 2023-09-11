#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MaxSize 100

typedef struct
{
	char Elem[MaxSize];
	int last;
}SeqList;

SeqList CrtList()
{
	SeqList p;
	int flag=1;
	char c;
	p.last = 0;
	while (flag)
	{
		c = getchar();
		if (c == '$')
		{
			flag = 0;
		}
		else
		{
			p.Elem[p.last++] = c;//随着p.last的增加标记下标
		}
	}
	return p;
}

void Find(SeqList P)
{
	int i=0;
	int Num;
	printf("1.按序号查找  ");
	printf("2.按内容查找\n");
	printf("请输入编号");
	scanf_s("%d", &Num);
	if (Num == 1)
	{
		int n;
		printf("请输入查找的数据序号");
		scanf_s("%d", &n);
		if (n >= P.last || n < 0)
			printf("Error!!!\n");
		while (i != n - 1)
		{
			i++;
		}
		printf("第%d个数据是%c\n", n, P.Elem[i]);
	}
	else if (Num == 2)
	{
		char data;
		printf("请输入内容");
		getchar();
		scanf_s("%c", &data);
		while (P.Elem[i] != data)
		{
			i++;
			if (i >= P.last)
			{
				printf("无查寻结果");
				break;
			}
		}
		if(i<P.last)
		printf("%c的序号是%d\n",P.Elem[i],i+1);
	}
	else {
		printf("WRONG!!!\n");
	}
}

SeqList InsList(SeqList P,int x,char data)
{
	P.last++;
	int j=P.last;
	while (x < j)
	{
		j--;
		P.Elem[j] = P.Elem[j - 1];
	}
	P.Elem[x] = data;
	return P;
}

SeqList Delet(SeqList P,int n)
{
	if (n >= P.last)
	{
		printf("Error\n");
	}
	else
	{
		P.last--;
		while (n < P.last)
		{
			P.Elem[n] = P.Elem[n + 1];
			n++;
		}
	}
	return P;
}

void Print(SeqList P)
{
	int i = 0;
	if (P.last == 0)
	{
		printf("Error!!!");
	}
	while (i!=P.last)
	{
		printf("%c", P.Elem[i]);
		i++;
	}
}

void main()
{
	SeqList P;
	int n,flag=1;
	while (flag)
	{
		printf("1.创建列表  ");
		printf("2.打印列表  ");
		printf("3.查找列表\n");
		printf("\n");
		printf("4.插入列表  ");
		printf("5.删除列表  ");
		printf("9.结束程序\n");
		printf("\n");
		printf("请输入序号\n");
		scanf_s("%d", &n);
		getchar();
		switch (n)
		{
		case 1:
			printf("请输入");
			P = CrtList();
			break;

		case 2:
			if (P.last == 0)
				printf("Error!!!\n");
			else
			{
				printf("列表为");
				Print(P);
				printf("\n");
			}
			break;

		case 3:
			Find(P);
			break;

		case 4:
			printf("请输入插入的数据以及位置\n");
			int num;
			char data;
			printf("请输入位置:");
			scanf_s("%d",&num);
			getchar();
			printf("请输入数据:");
			scanf_s("%c", &data);
			P=InsList(P, num-1, data);
			break;

		case 5:
			printf("请输入要删除的数据序号");
			int Delet_Num;
			scanf_s("%d", &Delet_Num);
			P=Delet(P, Delet_Num-1);
			printf("Success!!!\n");
			break;
			 
		case 9:
			flag = 0;
			break;
		default:
			printf("Error!!!\n");
			break;
		}
	}
}