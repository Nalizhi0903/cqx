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
			p.Elem[p.last++] = c;//����p.last�����ӱ���±�
		}
	}
	return p;
}

void Find(SeqList P)
{
	int i=0;
	int Num;
	printf("1.����Ų���  ");
	printf("2.�����ݲ���\n");
	printf("��������");
	scanf_s("%d", &Num);
	if (Num == 1)
	{
		int n;
		printf("��������ҵ��������");
		scanf_s("%d", &n);
		if (n >= P.last || n < 0)
			printf("Error!!!\n");
		while (i != n - 1)
		{
			i++;
		}
		printf("��%d��������%c\n", n, P.Elem[i]);
	}
	else if (Num == 2)
	{
		char data;
		printf("����������");
		getchar();
		scanf_s("%c", &data);
		while (P.Elem[i] != data)
		{
			i++;
			if (i >= P.last)
			{
				printf("�޲�Ѱ���");
				break;
			}
		}
		if(i<P.last)
		printf("%c�������%d\n",P.Elem[i],i+1);
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
		printf("1.�����б�  ");
		printf("2.��ӡ�б�  ");
		printf("3.�����б�\n");
		printf("\n");
		printf("4.�����б�  ");
		printf("5.ɾ���б�  ");
		printf("9.��������\n");
		printf("\n");
		printf("���������\n");
		scanf_s("%d", &n);
		getchar();
		switch (n)
		{
		case 1:
			printf("������");
			P = CrtList();
			break;

		case 2:
			if (P.last == 0)
				printf("Error!!!\n");
			else
			{
				printf("�б�Ϊ");
				Print(P);
				printf("\n");
			}
			break;

		case 3:
			Find(P);
			break;

		case 4:
			printf("���������������Լ�λ��\n");
			int num;
			char data;
			printf("������λ��:");
			scanf_s("%d",&num);
			getchar();
			printf("����������:");
			scanf_s("%c", &data);
			P=InsList(P, num-1, data);
			break;

		case 5:
			printf("������Ҫɾ�����������");
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