#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS_

typedef struct Node
{
	int data,Lnote,Rnote;
	struct Node* LChild;
	struct Node* RChild;
}BiTNode,*BiTree;

BiTNode *Bt;

BiTNode *InistTree()
{
	int data=0,x;
	BiTNode *root;
	root = (BiTNode*)malloc(sizeof(BiTNode));//����ռ�
	scanf_s("%d", &x);
	if (x == -1)
	{
		return NULL;
	}
	root->data = x;
	printf("������%d��������",x);
	root->LChild = (InistTree());
	printf("������%d��������",x);
	root->RChild = (InistTree());
	return root;
}

void PreOrder(BiTree root)//�������
{
	if (root!=NULL)
	{
		printf("%d ", root->data);
		PreOrder(root->LChild);
		PreOrder(root->RChild);
	}
}

void InOrder(BiTree root)//�������
{
	if (root != NULL)
	{
		InOrder(root->LChild);
		printf("%d ", root->data);
		InOrder(root->RChild);
	}
}

void PostOrder(BiTree root)//�������
{
	if (root != NULL)
	{
		PostOrder(root->LChild);
		PostOrder(root->RChild);
		printf("%d ", root->data);
	}
}

void Inoreder(BiTree root)//����ǵݹ����
{
	int top = 0;
	BiTNode *p = root,*s[100];
	do {
			while (p != NULL)
			{
				top = top + 1;
				s[top] = p;
				p = p->LChild;
			}
			if (top != 0)
			{
				p = s[top];
				top = top - 1;
				printf("%d ", p->data);
				p = p->RChild;
			}
	} while (top!=0);
	do {
			while (p != NULL)
			{
				top = top + 1;
				s[top] = p;
				p = p->LChild;
			}
			if (top != 0)
			{
				p = s[top];
				top = top - 1;
				printf("%d ", p->data);
				p = p->RChild;
			}
	} while (top != 0);
	if(p!=NULL)
	printf("%d ", p->data);
}

void Preoreder(BiTree root)//����ǵݹ����
{
	int top = 0;
	BiTNode* p = root, * s[100];
	do {
		while (p != NULL)
		{
			printf("%d ", p->data);
			top = top + 1;
			s[top] = p;
			p = p->LChild;
		}
		if (top!=0)
		{
			p = s[top];
			top = top - 1;
			p = p->RChild;
		}
	} while (top != 0); 
	do {
		while (p != NULL)
		{
			top = top + 1;
			s[top] = p;
			p = p->LChild;
		}
		if (top != 0)
		{
			p = s[top];
			top = top - 1;
			printf("%d ", p->data);
			p = p->RChild;
		}
	} while (top != 0);
	if (p != NULL)
		printf("%d ", p->data);
}

void main()
{
	Bt=InistTree();
	PreOrder(Bt);
	printf("\n");
	InOrder(Bt);
	printf("\n");
	PostOrder(Bt);
	printf("\n");
	Preoreder(Bt);
	printf("\n");
	Inoreder(Bt);
	printf("\n");
}