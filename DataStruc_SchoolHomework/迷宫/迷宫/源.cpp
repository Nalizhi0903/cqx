#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#define m 6
#define n 10

void Printf(int a[][n])
{
	int i, j;
	for (j = 0; j < m; j++)
	{
		for (i = 0;i< n;i++)
			printf(" %d ", a[j][i]);
		printf("\n");
	}
}

typedef struct node
{
	int j,i;//j为行,i为列
	struct node* next;
}LinkStact;

LinkStact* InistStack()//建立栈
{
	LinkStact* top;
	top = (LinkStact*)malloc(sizeof(struct node));//申请空间
	top->next = NULL;
	return top;
}

bool PushStack(LinkStact*top,int i,int j)//入栈
{
	LinkStact* temp;
	temp = (LinkStact*)malloc(sizeof(struct node));//申请空间
	if (temp == NULL)
	{
		printf("FALSE");
		return false;
	}
	temp->i = i;
	temp->j = j;
	temp->next = top->next;
	top->next = temp;
	return true;
}

bool PopStack(LinkStact*top)//出栈
{
	LinkStact* temp;
	temp = top->next;
	if (temp == NULL)
	{
		printf("FALSE\n\n");
		return false;
	}
	top->next = temp->next;
	free(temp);
	return true;
}

void Print(LinkStact* top)
{
	LinkStact* temp;
	temp = top->next;
	while (temp!=NULL)
	{
		printf("列%d行%d\n", temp->i, temp->j);
		temp = temp->next;
	}
	printf("\n");
}

void FindWay(LinkStact* top, int a[][n])
{
	int j, i, flag = 1,q=1;
	LinkStact* temp=NULL;
	PushStack(top,3,2);
	j = 1, i = 2;
	while (flag)
	{	
		if (a[j - 1][i] == 0)//检查上方
		{
			PushStack(top, i + 1, j);
			a[j][i] = -1;
			j = j - 1;
			q = 1;
		}
		else if (a[j][i + 1] == 0)//检查右方
		{
			PushStack(top, i + 2, j + 1);
			a[j][i] = -1;
			i = i + 1;
			q = 1;
		}
		else if (a[j + 1][i] == 0)//检查下方
		{
			PushStack(top, i + 1, j + 2);
			a[j][i] = -1;
			j = j + 1;
			q = 1;
		}
		else if (a[j][i - 1] == 0)//检查左方
		{
			PushStack(top, i, j + 1);
			a[j][i] = -1;
			i = i - 1;
			q = 1;
		}
		else if (j == 4 && i == 1)
		{
			flag = 0;
		}
		else
		{
			if (q == 1)
			{
				PopStack(top);//难点
			}
			j = (top->next->next->j)-1;//难点
			i = (top->next->next->i)-1;//难点
			if (q != 1)
				PopStack(top);//难点
			q++;
		}
	}
	Print(top);
}

int main()
{
	LinkStact* top;
	top=InistStack();
	int i,j,flag=1,x=0;
	int a[m][n] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,1,1,1},
		{1,0,0,0,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,0,0,0,1,1,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
	Printf(a);
	while (flag)
	{
		//printf("1、入栈\n");
		//printf("2、出栈\n");
		printf("1、迷宫\n");
		printf("请输入序号");
		scanf_s("%d",&x);
		printf("\n");
		switch (x)
		{
		case 1:
			FindWay(top,a);
			break;
		default:
			printf("WRONG\n");
			break;
		}
	}
}