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
	printf("请输入序号\n");
	printf("1.建立栈\n");
	printf("2.判断栈是否为空，1为空，0不为空\n");
	printf("3.入栈\n");
	printf("4.出栈\n");
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
			printf("入栈成功\n");
			printf("%d",s->top);
			break;
		case 4:
			Pop_SeqStack(s);
			printf("出栈成功\n");
			break;
		default:
			printf("输入序号错误\n");
			break;
		}
	}
	return 0;
}