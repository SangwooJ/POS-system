#pragma once
#include <stdio.h>
int getMenuTouchInput(void)  //�޴����ù�ư ��ǲ ������ ����
{
	int menu_selection;
	scanf("%d", &menu_selection);
	getchar();
	return menu_selection;
}

int getQuantityTouchInput(void)  //������ư ��ǲ ������ ����
{
	int upDown;
	scanf("%d", &upDown);
	return upDown;
}