#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

typedef struct node
{
	int weight;
	int parent;
	int LChild;
	int RChild;
}HTNode,HuffmanTree[MaxSize];

typedef struct Code
{
	char cd[20];
	int start;
}HCode;

void CrtHuffmanTree(HuffmanTree ht, int w[], int n)
{
	int lnode, rnode, i, k, s1, s2;
	for (i=0;i<n;i++)
	{
		scanf_s("%d", &ht[i].weight);
	}
	for (i = 0; i < 2 * n - 1; i++)
	{
		ht[i].parent = -1;
		ht[i].LChild = -1;
		ht[i].RChild = -1;
	}
	for (i=n;i<2*n-1;i++)
	{
		s1 = s2 = 99999;
		lnode = rnode = -1;
		for (k = 0; k < i; k++)
		{
			if (ht[k].parent == -1)
			{
				if (ht[k].weight < s1)
				{
					s2 = s1;
					s1 = ht[k].weight;
					rnode = lnode;
					lnode = k;
				}
				else if (ht[k].weight < s2)
				{
					s2 = ht[k].weight;
					rnode = k;
				}
			}
		}
		ht[i].LChild = lnode;
		ht[i].RChild = rnode;
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[lnode].parent = i;
		ht[rnode].parent = i;
	}
}

void CrtHuffmanCode(HuffmanTree ht,HCode hcd[],int n)
{
	int f, c, i;
	for (i = 0; i < n; i++)
	{
		hcd[i].start = n;
		c = i;
		f = ht[i].parent;
		while (f!=-1)
		{
			if (ht[f].LChild == c)
			{
				hcd[i].cd[hcd[i].start--] = '0';
			}
			else
				hcd[i].cd[hcd[i].start--] = '1';
			c = f;
			f = ht[f].parent;
		}
		hcd[i].start++;
	}
}

void main()
{
	HuffmanTree ht;
	HCode hcd[100];
	int w[MaxSize];
	int n;
	printf("请输入数据个数");
	scanf_s("%d", &n);
	CrtHuffmanTree(ht, w, n);
	for (int i=0;i<2*n-1;i++)
	{
		printf("%-3d%-3d%-3d%-3d\n", ht[i].weight, ht[i].parent+1, ht[i].LChild+1, ht[i].RChild+1);
	}
	CrtHuffmanCode(ht, hcd, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", ht[i].weight);
		for (int j = hcd[i].start; j <= n; j++)
		{
			printf("%c", hcd[i].cd[j]);
		}
		printf("\n");
	}	
}