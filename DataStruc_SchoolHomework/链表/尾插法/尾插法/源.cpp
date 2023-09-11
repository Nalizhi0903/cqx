#define _CRT_SECURES_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	struct node* next;
}Link,*Linklist;

Link* fun(int n)
{
	Link* rear, * head, * NewNode;
	int i;
	head = (Link*)malloc(sizeof(Link));
	head->next = NULL;
	rear = head;
	for (i = 0; i < n; i++)
	{
		NewNode = (Link*)malloc(sizeof(Link));
		scanf_s("%d", &NewNode->data);
		rear->next = NewNode;
		rear = NewNode;
	}
	rear->next = NULL;
	return head;
}

Link* Get(Linklist NewHead, int l)
{
	int j;
	Link* p;
	if (l <= 0) return NULL;
	p = NewHead; j = 0;
	while ((p->next != NULL) && (j < l))
	{
		p = p->next;
		j++;
	}
	return p;
}

Link* Locate(Linklist NewHead2, int x)
{
	Link* p;
	p = NewHead2->next;
	while (p != NULL)
		if (p->data != x)
			p = p->next;
		else break;
	return p;
}

int ListLength(Linklist Newhead3)
{
	int j;
	Link* p;
	p = Newhead3->next;
	j = 0;
	while (p!=NULL)
	{
		p = p->next;
		j++;
	}
	return j;
}

int main()
{
	int n, i, l,x,o;
	Link* Head, * q, * m,*NewHead,* NewHead2,*y, * NewHead3;
	printf("请输入要输入多少个字");
	scanf_s("%d", &n);
	printf("请输入");
	Head = fun(n);
	NewHead = Head;
	NewHead2 = Head;
	NewHead3 = Head;
	for (i = 0; i < n; i++)
	{
		q = Head->next;
		printf("%d ", q->data);
		Head = Head->next;
	}
	printf("请输入要查询第几个的数");
	scanf_s("%d", &l);
	m = Get(NewHead, l);
	printf("%d\n", m->data);
	printf("请输入要查询的数");
	scanf_s("%d", &x);
	y=Locate(NewHead2, x);
	if (y->data!=NULL)
	printf("有%d\n",y->data);
	o = ListLength(NewHead3);
	printf("链表长度是%d\n",o);
	return 0;
}