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
	int flag = 1;
	char c;
	Link* r, * p, * Head;
	printf("�������ַ�,����$����");
	Head = (Link*)malloc(sizeof(struct Node));
	Head->next = NULL;
	r = Head;
	while (flag)
	{
		c = getchar();
		if (c != '$')
		{
			p = (Link*)malloc(sizeof(struct Node));
			p->value = c;
			r->next = p;
			r = p;
		}
		else flag = 0;
		r->next = NULL;
	}
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

Link *MergeLinkList(Linklist L1,Linklist L2)
{
	Linklist CL,r;
	Node* pa, * pb;
	pa = L1->next;
	pb = L2->next;
	CL = L1;
	CL->next=NULL;
	r = CL;
	while (pa->next != NULL&&pb!=NULL)
	{
		if (pa->value<=pb->value)
		{
			r->next = pa;
			r = pa;
			pa = pa->next;
		}
		else
		{
			r->next = pb;
			r = pb;
			pb = pb->next;
		}
	}
	if (L1)
		r->next = pa;
	else
		r->next = pb;
	free(L2);
	return CL;
}

int main()
{
	Linklist L1, L2,CL;

	printf("��������1");
	L1 = CreatLink();
	Printf(L1);
	printf("��������2");
	getchar();
	L2 = CreatLink();
	Printf(L2);
	CL=MergeLinkList(L1, L2);
	printf("�ϲ�������Ϊ");
	Printf(CL);
	return 0;
}