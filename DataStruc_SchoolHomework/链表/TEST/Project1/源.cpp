#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	char value;
	struct Node* next;
}Link,*Linklist;

Link* CreatLink1()
{
	int  flag=1;
	char c;
	Linklist head, p;
	head = (Link*)malloc(sizeof(struct Node));
	head->next = NULL;
	printf("请输入字符,输入$结束");
	while (flag)
	{
		c = getchar();
		if (c != '$')
		{
			p = (Link*)malloc(sizeof(struct Node));
			p->value = c;
			p->next = head->next;
			head->next = p;
		}
		else flag = 0;
	}
	getchar();
	return head;
}

Link *CreatLink2()
{
	int flag = 1;
	char c;
	Link *r,*p,*Head;
	printf("请输入字符,输入$结束");
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

void Printf(Link *Head)
{
	Head = Head->next;
	while (Head != NULL)
	{
		printf("%c", Head->value);
		Head = Head->next;
	}
	printf("\n");
}

Link* Get(Linklist NewHead,int i)
{
	int j;
	Link* p;
	if (i <= 0) return NULL;
	p = NewHead; j = 0;
	while ((p->next != NULL) && (j < i))
	{
		p = p->next;
		j++;
	}
	return p;
}

void Locate(Link *NewHead, char x)
{
	int i=0;
	Link* p;
	p = NewHead->next;
	while (p->next != NULL)
	{
		if ( p->value != x)
		{
			p = p->next;
			i=i+1;
		}
		else break;
	}
	printf("%d\n",i+1);
}

void Locate2(Link* NewHead, char x)
{
	int i = 0;
	Link* p;
	p = NewHead->next;
	while (p->next != NULL)
	{
		if (p->value != x)
		{
			p = p->next;
			i = i + 1;
		}
		else break;
	}
	printf("%d\n", i);
}

void InsList(Linklist Head, int i, char c)
{
	Link* pre, * s;
	int k;
	if (i <= 0) printf("ERROR");
	pre = Head; k = 0;
	while (pre!=NULL&&k<i-1)
	{
		pre = pre->next;
		k = k + 1;
	}
	if (pre == NULL)
	{
		printf("插入的位置不合理");
	}
	s = (Link*)malloc(sizeof(struct Node));
	s->value = c;
	s->next = pre->next;
	pre->next = s;
}

void DelList(Linklist Head,int i)
{
	Link* pre, * r;
	int k;
	pre = Head; k = 0;
	while (pre->next != NULL && k < i - 1)
	{
		pre = pre->next;
		k = k + 1;
	}
	if (pre->next == NULL)
	{
		printf("删除节点的位置不合理");
	}
	r = pre->next;
	pre->next = r->next;
	free(r);
	Printf(Head);
}

void DelList2(Linklist Head, int i)
{
	Link* pre, * r;
	int k;
	pre = Head; k = 0;
	while (pre->next != NULL && k < i )
	{
		pre = pre->next;
		k = k + 1;
	}
	if (pre->next == NULL)
	{
		printf("删除节点的位置不合理");
	}
	r = pre->next;
	pre->next = r->next;
	free(r);
	Printf(Head);
}

int main()
{
	int a,b=0,n,i,q,j;
	char x,c;
	Link* Num1, * NewHead1 = NULL, * NewHead2 = NULL, * Value1=NULL, * Value2=NULL;
	printf("***********1.头插法建立链表  ***********\n");
	printf("***********2.尾插法建立链表  ***********\n");
	printf("***********3.按序查询头插法列表里值*****\n");
	printf("***********4.按序查询尾插法列表里值*****\n");
	printf("***********5.查询头插法列表里值的序号***\n");
	printf("***********6.查询尾插法列表里值的序号***\n");
	printf("***********7.在头插法列表里插入值*******\n");
	printf("***********8.在尾插法列表里插入值*******\n");
	printf("***********9.删除头插法列表里的值*******\n");
	printf("***********10.删除尾插法列表里的值******\n");
	while(1)
	{
		printf("请输入序号");
		scanf_s("%d", &a);
	switch (a)
		{
			case 1:
				NewHead1 = CreatLink1();
				Value1 = NewHead1;
				Printf(NewHead1);
				break;
			case 2:
				NewHead2 = CreatLink2();
				Value2 = NewHead2;
				Printf(NewHead2);
				break;
			case 3:
				printf("请输入查询第几个值");
				scanf_s("%d", &i);
				printf("第%d的符号是%c\n",i,Get(NewHead1, i)->value);
				break;
			case 4:
				printf("请输入查询第几个值");
				scanf_s("%d", &i);
				printf("第%d的符号是%c\n", i, Get(NewHead2, i)->value+1);
				break;
			case 5:
				printf("输入要查询的值");
				getchar();
				scanf_s("%c", &x);
				Locate(Value1,x);
				break;
			case 6:
				printf("输入要查询的值");
				getchar();
				scanf_s("%c", &x);
				Locate2(Value2, x);
				break;
			case 7:
				printf("请输入在第几个数前插入数，在输入位置后空格继续输入值");
				getchar();
				scanf_s("%d %c", &j,&c);
				InsList(Value1,j,c);
				Printf(Value1);
				break;
			case 8:
				printf("请输入在第几个数前插入数，在输入位置后空格继续输入值");
				getchar();
				scanf_s("%d %c", &j, &c);
				j = j + 1;
				InsList(Value2, j, c);
				Printf(Value2);
				break;
			case 9:
				printf("请输入删除头插法列表的第几个元素");
				getchar();
				scanf_s("%d",&j);
				DelList(Value1,j);
				break;
			case 10:
				printf("请输入删除头插法列表的第几个元素");
				getchar();
				scanf_s("%d", &j);
				DelList2(Value2, j);
				break;
		}
	}
	return 0;
}