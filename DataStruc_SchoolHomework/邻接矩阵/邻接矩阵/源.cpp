#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 10

typedef struct
{
	int arcnum;//弧数
	int vexnum;//顶点数
	char Vertex[MAX_VERTEX_NUM];//顶点
}Graph;

Graph* G;

int LocateVertex(char value)
{
	int j = -1,k;
	for (k = 0; k<G->vexnum; k++)
	{
		if (value == G->Vertex[k])
		{
			j = k;//寻找位置
		}
	}
	return j;
}

void main()
{
	int Arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	char value1, value2;
	G = (Graph*)malloc(sizeof(Graph));
	{printf("请输入图的弧数:"); scanf_s("%d", &G->arcnum); printf("请输入图的顶点数:"); scanf_s("%d", &G->vexnum); }//输入图的弧数和顶点数
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int k = 0; k < G->vexnum; k++)
		{
			Arcs[i][k] = 0;//初始化邻接矩阵
		}
	}
	getchar();
	for (int num = 0; num < G->vexnum; num++)
	{
		G->Vertex[num]=getchar();//输入图的顶点
	}
	getchar();
	for (int j = 0; j < G->arcnum; j++)
	{
		printf("请输入顶点A%d:",j);
		value1 = getchar();
		getchar();
		printf("请输入顶点B%d:",j);
		value2 = getchar();
		getchar();
		int i = LocateVertex(value1);
		int k = LocateVertex(value2);
		Arcs[i][k] = 1;
		printf("\n");
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		printf(" %c", G->Vertex[i]);
	}
	printf("\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int k = 0; k < G->vexnum; k++)
		{
			printf("%2d",Arcs[i][k]);
		}
		printf(" %c", G->Vertex[i]);
		printf("\n");
	}
}