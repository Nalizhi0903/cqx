#include "Game.h"

int main()
{
	int select = 1;
	while (select)
	{
		printf("******************************************\n");
		printf("*             �� �� ɨ �� �� Ϸ          *\n");
		printf("******************************************\n");
		printf("*                 [1] Play               *\n");
		printf("*                 [0] Exit               *\n");
		printf("******************************************\n");
		printf("��ѡ��:>");
		scanf("%d", &select);

		if (select == 0)
			break;

		if (select != 1)
		{
			printf("������������������......\n");
			continue;
		}

		//��ʼ��Ϸ
		StartGame();
		return 0;
	}

}