#include "Game.h"

int main()
{
	int select = 1;
	while (select)
	{
		printf("******************************************\n");
		printf("*             简 易 扫 雷 游 戏          *\n");
		printf("******************************************\n");
		printf("*                 [1] Play               *\n");
		printf("*                 [0] Exit               *\n");
		printf("******************************************\n");
		printf("请选择:>");
		scanf("%d", &select);

		if (select == 0)
			break;

		if (select != 1)
		{
			printf("输入有误，请重新输入......\n");
			continue;
		}

		//开始游戏
		StartGame();
		return 0;
	}

}