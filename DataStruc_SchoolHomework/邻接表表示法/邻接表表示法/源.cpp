#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define Max_Vertex_Num 20

typedef struct ArcNode
{
	char data;
	struct ArcNode* nextarc;
}ArcNode;//�߱�

typedef struct VertexNode
{
	char data;
	ArcNode* firstarc;
}VertexNode;//�����

typedef struct
{
	VertexNode vertex[Max_Vertex_Num];
	int vexnum, arcnum;
}AdjList;//���������

AdjList* Graph;

int Locate(char Vex)
{
	int i = 0;
	while (Vex != Graph->vertex[i].data)
	{
		i++;
	}
	return i;
}

void CrtList()
{
	printf("�����붥�����ͱ���");
	scanf_s("%d,%d", &Graph->vexnum,&Graph->arcnum);
	getchar();
	for (int i = 0; i < Graph->vexnum; i++)
	{
		Graph->vertex[i].data = getchar();
		Graph->vertex[i].firstarc = NULL;	
	}//���붥��

	ArcNode* Vex;//�����߱�
	for (int k=0;k<Graph->arcnum;k++)
	{
		char i, j;
		printf("�������й�ϵ���������㣬�س��ָ�\n");
		getchar();
		scanf_s("%c", &i);
		getchar();
		scanf_s("%c", &j);
		Vex = (ArcNode*)malloc(sizeof(ArcNode));
		Vex->data=j;
		Vex->nextarc = Graph->vertex[Locate(i)].firstarc;
		Graph->vertex[Locate(i)].firstarc=Vex;
	}
}

void print()
{
	int i = 0;
	for (i = 0; i < Graph->vexnum; i++)
	{
		printf("%c�ı߱�", Graph->vertex[i].data);
		while (Graph->vertex[i].firstarc != NULL)
		{
			if (Graph->vertex[i].firstarc->data != NULL)
			{
				printf("%c", Graph->vertex[i].firstarc->data);
				Graph->vertex[i].firstarc = Graph->vertex[i].firstarc->nextarc;
			}
		}
		printf("\n");
	}
}

void main()
{
	Graph = (AdjList*)malloc(sizeof(AdjList));
	CrtList();
	print();
}