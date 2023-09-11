#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	char data;
	struct Node* next;
}StackNode, * LinkStack;

int Empty_LinkStack(LinkStack top)//ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ
{
	if (top == NULL)
	{
		return 0;
	}
	else return 1;
}

LinkStack Push_LinkStack(LinkStack top)
{
	int flag = 1;
	char x;
	StackNode* s,*r;
	top = (LinkStack)malloc(sizeof(struct Node));
	top->next = NULL;
	r = top;
	while (flag)
	{
		x = getchar();
		if (x != '$')
		{
			s = (StackNode*)malloc(sizeof(StackNode));
			s->data = x;
			s->next = r->next;
			r->next = s;
		}
		else flag = 0;
	}
	return top;
}

LinkStack Pop_LinkStack(LinkStack top)
{
	LinkStack temp;
	temp = top->next;
	if (temp == NULL)
		return temp;
	else {
		top->next = temp->next;
		return top;
	}
}

int main()
{
	LinkStack top,L,L1,L2;
	int flag = 1;
	char x;
	top = NULL;
	printf("³õÊ¼»¯Õ»£¬ÈôÕ»Îª¿ÕÔòÏÔÊ¾0\n");
	printf("%d\n", Empty_LinkStack(top));
	printf("ÇëÊäÈë×Ö·ûÈëÕ»£¬ÊäÈë$½áÊø");
	L = Push_LinkStack(top);
	L1 = L;
	printf("Õ»Îª");
	L = L->next;
	while (L->next != NULL)
	{
		printf("%c", L->data);
		L = L->next;
	}
	printf("%c\n", L->data);
	L1 = L1->next;
	L2=Pop_LinkStack(L1);
	printf("%d\n", Empty_LinkStack(L2));
	while (L2->next != NULL)
	{
		printf("%c", L2->data);
		L2 = L2->next;
	}
	return 0;
}