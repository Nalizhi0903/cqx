#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Arcnode
{
	int tailvex, headvex,info;
	struct Arcnode* hlink, * tlink;
}Arcnode;//边表

typedef struct VertexNode
{
	char data;
	Arcnode* firstin, * firstout;
}VertexNode;//顶点表

typedef struct
{
	VertexNode vertex[20];
	int arcnum, vexnum;
}OrthList;//十字链表

OrthList* Graph;

int Locate(char data)//定位位置
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
	Graph = (OrthList*)malloc(sizeof(OrthList));//开辟空间
	Arcnode* p;
	printf("请输入顶点数，边数\n");
	scanf_s("%d,%d", &Graph->vexnum, &Graph->arcnum);//输入顶点数与边数
	getchar();
	for (int i = 0; i < Graph->vexnum; i++)//初始化十字链表,输入顶点
	{
		Graph->vertex[i].data = getchar();
		Graph->vertex[i].firstin = NULL;
		Graph->vertex[i].firstout = NULL;
	}
	getchar();
	for (int i = 0; i < Graph->arcnum; i++)//建立边表
	{
		int j,k;
		char vt, vh;
		p = (Arcnode*)malloc(sizeof(Arcnode));
		printf("请输入有关系的两个顶点,回车分割\n");
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
		printf("%c的边表为", Graph->vertex[i].data);
		while (Graph->vertex[i].firstout!=NULL)
		{
			Graph->vertex[i].firstout->info = k;
			k++;
			printf("第%d个顶点", Graph->vertex[i].firstout->info);
			printf("弧尾顶点为%d", Graph->vertex[i].firstout->tailvex);
			printf("弧头顶点为%d", Graph->vertex[i].firstout->headvex);
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