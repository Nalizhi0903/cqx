#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Link;

Link* fun(int n)
{
	Link* p, * head, * link;
	int i, a,x;
	head = (Link*)malloc(sizeof(Link));
	head->next = NULL;
	for (i = 0; i < n; i++)
	{
		p = (Link*)malloc(sizeof(Link));
		scanf_s("%d", &x);
		p->data =x ;
		p->next = head->next;
		head->next = p;
	}
	link = head->next;
	return link;
}

int main()
{
	int d;
	int n;
	Link* Head;
	scanf_s("%d", &d);
	switch (d)
	{
	case 1:
		scanf_s("%d", &n);
		Head = fun(n);
	while (n--)
	{
		printf("%d ", Head->data);
		Head = Head->next;	
	}
	break;
	}
	return 0;
}