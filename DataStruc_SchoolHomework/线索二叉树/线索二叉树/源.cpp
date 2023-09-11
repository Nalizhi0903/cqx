#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	int Ltag;
	int Rtag;
	struct node* LChild;
	struct node* RChild;
}*BiTree,BiTNode;

BiTNode *pre;//preʹ��ȫ�ֱ����Ϻã��ֲ���������Ѱ�Һ�̽��ʱʼ��Ϊnull

BiTNode* InistTree()
{
	int x,data=0;
	BiTNode* root;
	root = (BiTNode*)malloc(sizeof(struct node));
	scanf_s("%d",&x);
	if (x == -1)
		return NULL;
	root->data = x;
	printf("������%d��������",root->data);
	root->LChild = InistTree();
	printf("������%d��������",root->data);
	root->RChild = InistTree();
	return root;
}

void InOrder(BiTree root)//�������
{
	if (root != NULL)
	{
		InOrder(root->LChild);
		printf("%d  ",root->data);
		InOrder(root->RChild);
	}
}

void Inthread(BiTree root)
{
	if (root != NULL)
	{
		Inthread(root->LChild);
		if (root->LChild == NULL)
		{
			root->Ltag = 1;
			root->LChild = pre;
			if (pre != NULL)
				printf("%d��ǰ�������%d\n",root->data,pre->data);
		}
		if (pre != NULL && pre->RChild==NULL)
		{
			pre->RChild = root;
			pre->Rtag = 1;
			if (pre != NULL)
				printf("%d�ĺ�̽����%d\n", pre->data, root->data);
		}
		pre = root;
		Inthread(root->RChild);
	}
}

BiTNode* InPre(BiTNode* p)//Ѱ��ǰ�����
{
	BiTNode* q,*Pre=NULL;
	q= (BiTNode*)malloc(sizeof(struct node));
	Pre= (BiTNode*)malloc(sizeof(struct node));
	if (p->Ltag == 1)
		pre = p->LChild;
	else
	{
		for (q=p->LChild; q->Rtag != 1; q = q->RChild);
		Pre = q;
		printf("%dǰ�������%d",p->data,Pre->data);
	}
	return Pre;
}

BiTNode* InNext(BiTNode* p)//Ѱ�Һ�̽��
{
	BiTNode* q, * Pre = NULL;
	q = (BiTNode*)malloc(sizeof(struct node));
	Pre = (BiTNode*)malloc(sizeof(struct node));
	if (p->Rtag == 1)
		Pre = p->LChild;
	else
	{
		for (q = p->RChild; q->Ltag != 1; q = q->LChild);
		Pre = q;
		printf("%d��̽����%d", p->data, Pre->data);
	}
	return Pre;
}

void main()
{
	pre = NULL;
	BiTNode* pre = NULL;
	BiTNode* root;
	root=InistTree();
	InOrder(root);
	printf("\n");
	Inthread(root);
	printf("\n");
	InPre(root);
	printf("\n");
	InNext(root);
}