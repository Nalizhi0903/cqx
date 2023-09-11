#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Arcnode
{
	int tailvex, headvex,info;
	struct Arcnode* hlink, * tlink;
}Arcnode;//�߱�

typedef struct VertexNode
{
	char data;
	Arcnode* firstin, * firstout;
}VertexNode;//�����

typedef struct
{
	VertexNode vertex[20];
	int arcnum, vexnum;
}OrthList;//ʮ������

OrthList* Graph;

int Locate(char data)//��λλ��
{
	int i = 0;
	while (Graph->vertex[i].data != data)
	{
		i++;
	}
	return i;
}

void CrtList()
{
	Graph = (OrthList*)malloc(sizeof(OrthList));//���ٿռ�
	Arcnode* p;
	printf("�����붥����������\n");
	scanf_s("%d,%d", &Graph->vexnum, &Graph->arcnum);//���붥���������
	getchar();
	for (int i = 0; i < Graph->vexnum; i++)//��ʼ��ʮ������,���붥��
	{
		Graph->vertex[i].data = getchar();
		Graph->vertex[i].firstin = NULL;
		Graph->vertex[i].firstout = NULL;
	}
	getchar();
	for (int i = 0; i < Graph->arcnum; i++)//�����߱�
	{
		int j,k;
		char vt, vh;
		p = (Arcnode*)malloc(sizeof(Arcnode));
		printf("�������й�ϵ����������,�س��ָ�\n");
		scanf_s("%c", &vt);
		getchar();
		scanf_s("%c", &vh);
		getchar();
		j = Locate(vt);
		k = Locate(vh);
		p->tailvex = j;
		p->headvex = k;
		p->tlink = Graph->vertex[j].firstout;
		p->hlink = Graph->vertex[k].firstin;
		Graph->vertex[j].firstout = p;
		Graph->vertex[k].firstin = p;
	}
}

void Print()
{
	for (int i = 0; i < Graph->vexnum; i++)
	{
		int k = 1;
		printf("%c�ı߱�Ϊ", Graph->vertex[i].data);
		while (Graph->vertex[i].firstout!=NULL)
		{
			Graph->vertex[i].firstout->info = k;
			k++;
			printf("��%d������", Graph->vertex[i].firstout->info);
			printf("��β����Ϊ%d", Graph->vertex[i].firstout->tailvex);
			printf("��ͷ����Ϊ%d", Graph->vertex[i].firstout->headvex);
			Graph->vertex[i].firstout = Graph->vertex[i].firstout->tlink;
			printf("\n");
		}
	}
}

void main()
{
	CrtList();
	Print();
}