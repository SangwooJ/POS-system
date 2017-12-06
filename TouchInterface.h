#pragma once
#include <stdio.h>
int getMenuTouchInput(void)  //메뉴선택버튼 인풋 데이터 전달
{
	int menu_selection;
	scanf("%d", &menu_selection);
	getchar();
	return menu_selection;
}

int getQuantityTouchInput(void)  //수량버튼 인풋 데이터 전달
{
	int upDown;
	scanf("%d", &upDown);
	return upDown;
}