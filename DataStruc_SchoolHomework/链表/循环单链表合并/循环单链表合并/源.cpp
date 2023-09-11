#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char value;
	struct Node* next;
}Link, * Linklist;

Link* CreatLink()
{
	char c;
	Link* r, * p, * Head;
	printf("ÇëÊäÈë×Ö·û,ÊäÈë$½áÊø");
	Head = (Link*)malloc(sizeof(struct Node));
	Head->next = Head;
	r = Head;
	c = getchar();
	Head->value = c;
	while (c != '$')
	{
		p = (Link*)malloc(sizeof(struct Node));
		p->value = c;
		r->next = p;
		r = p;
		c = getchar();
	}
	r->next = Head;
	return Head;
}

Linklist merge_1(Linklist L1,Linklist L2)
{
	Node* p, * q;
	p = L1->next;
	q = L2->next;
	while (p->next != L1) p = p->next;
	while (q->next != L2) q = q->next;
	q->next = L1;
	p->next = L2->next;
	free (L2);
	return L1;
}

void Printf(Link* Head)
{
	Head = Head->next;
	while (Head != NULL)
	{
		printf("%c", Head->value);
		Head = Head->next;
	}
	printf("\n");
}


int main()
{
	Linklist L1, L2;
	L1 = CreatLink();
	getchar();
	L2 = CreatLink();
	Printf(merge_1(L1, L2));
	return 0;
}