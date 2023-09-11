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
	Printf(CreatLink());
}
