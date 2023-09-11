#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS_
#define MAXSIZE 100
typedef struct Node
{
	int a[MAXSIZE];
	int top;
}SeqStack;

SeqStack* init_SeqStack()
{
	SeqStack* s;
	s = (SeqStack*)malloc(sizeof(SeqStack));
	s->top = -1;
	return s;
}

int Empty_SeqStack(SeqStack* s)
{
	if (s->top == -1) return 1;
	else return 0;
}

int Push_SeqStack(SeqStack* s, int x1)
{
	if (s->top == MAXSIZE - 1) return (0);
	else {
		s->top++; s->a[s->top] = x1; return 1;
	}
}

int Pop_SeqStack(SeqStack* s)
{
	if (s->top == MAXSIZE - 1) return (0);
	else {
		s->top--;
		return 1;
	}
}

int main()
{
	int x1=0,flag=1,a;
	SeqStack* s=NULL;
	printf("���������\n");
	printf("1.����ջ\n");
	printf("2.�ж�ջ�Ƿ�Ϊ�գ�1Ϊ�գ�0��Ϊ��\n");
	printf("3.��ջ\n");
	printf("4.��ջ\n");
	while (flag)
	{
		scanf_s("%d",&a);
		switch (a)
		{
		case 1:
			s= init_SeqStack();
			break;
		case 2:
			printf("reasult is ");
			printf("%d\n", Empty_SeqStack(s));
			break;
		case 3:
			printf("Please intput");
			scanf_s("%d", &x1);
			Push_SeqStack(s, x1);
			printf("��ջ�ɹ�\n");
			printf("%d",s->top);
			break;
		case 4:
			Pop_SeqStack(s);
			printf("��ջ�ɹ�\n");
			break;
		default:
			printf("������Ŵ���\n");
			break;
		}
	}
	return 0;
}