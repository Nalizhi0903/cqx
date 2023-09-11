#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 1000

typedef struct ListNode
{
	int data;//�������
	struct ListNode* pre;//ǰ���
	struct ListNode* next;//����
}Node,*NewList;

int Check(char a[], int m)
{
	if (a[0] == '+' || a[0] == '-')//����һ����λ
	{
		for (int i = 1; i < m; i++)
		{
			if ((int(a[i]) <= 57 && int(a[i]) >= 48) || a[i] == ',')//�������������Ƿ�Ϊ0-9
			{
				if (i == m - 1)
				{
					return 1;
				}
			}
			else return -1;
		}
	}
	else return -1;
}

int Input(NewList& LongInt)
{
	LongInt = (Node*)malloc(sizeof(Node));
	LongInt->pre = LongInt;//��ʼ��
	LongInt->next = LongInt;
	ListNode* New, * rear;
	rear = LongInt;
	int flag = 0;
	int num = 0;
	int length = 0;
	char str[Max];
	int i = 0;

	printf("�������ʽΪ+****$������");
	while (str[i - 1] != '$')
	{
		str[i] = getchar();
		i++;
	}
	getchar();
	str[i - 1] = '\0';
	length = strlen(str);
	if (str[0] == '+')
	{
		LongInt->data = 43;
	}
	else if (str[0] == '-')
	{
		LongInt->data = 45;
	}
	flag = Check(str, length);
	if (flag == -1)			//��������ʽ
		printf("��������");
	else
	{
		for (int i = 1; i < length; i++)		//����ѭ�������棬ͷ�巨
		{
			New = (ListNode*)malloc(sizeof(ListNode));
			New->data = str[i];
			New->next = rear->next;
			rear->next = New;
		}
		LongInt = rear->next;// ����ַ��Ϊ��һ��Ԫ�صĵ�ַ
	}
}

int Sum(ListNode* L1,ListNode *L2)
{
	ListNode* pResult,*New,*End;
	End = (ListNode*)malloc(sizeof(ListNode));
	End->next = NULL;
	End->pre = NULL;
	pResult = End;
	int carry=0;

	while (L1->data!=43 || L2->data != 43)//������ ͷ�巨
	{
		if (L1->data == 43)
		{
			while (L2->data != 43)
			{
				New = (ListNode*)malloc(sizeof(ListNode));
				New->data = L2->data;
				New->next = pResult->next;
				pResult->next = New;
				L2 = L2->next;
			}
			break;
		}
		if (L2->data == 43)
		{
			while (L1->data != 43)
			{
				New = (ListNode*)malloc(sizeof(ListNode));
				New->data = L1->data;
				New->next = pResult->next;
				pResult->next = New;
				L1 = L1->next;
			}
			break;
		}
		New = (ListNode*)malloc(sizeof(ListNode));
		New->data =  (char)(((int)(L1->data + L2->data)-96) % 10 + carry +48);
		carry = ((int)(L1->data) + (int)(L2->data)-96) / 10;
		if (((int)(New->data)-48) / 10 != 0)		//�жϼ������Ƿ����10��������carry��һλ
			carry++;
		L1 = L1->next;
		L2 = L2->next;
		New->next = pResult->next;
		pResult->next = New;
	}
	if (carry == 1)
	{
		New = (ListNode*)malloc(sizeof(ListNode));
		New->data =	'1';
		New->next = pResult->next;
		pResult->next = New;
	}
	End = pResult->next;

	int i = 0;
	while (End!=NULL)
	{
		printf("%c", End->data);
		if (i == 3)
		{
			i = -1;
			printf(",");
		}
		i++;
		End = End->next;
	}
	printf("\n");

	return 0;
}

void main()
{
	Node* L1,*L2;
	Input(L1);
	Input(L2);
	Sum(L1, L2);
	/*��������ѭ���б���������*/
}