#pragma once
#include <stdio.h>
#include "TouchInterface.h"

int menuTouchData()  // 메뉴버튼 데이터  전달
{
	int menu_selection;
	menu_selection = getMenuTouchInput();
	if (menu_selection != 1 && menu_selection != 2 && menu_selection != 3 && menu_selection != 4) //1,2,3 이외를 입력하면
	{
		printf("input error . retype : \n");
		printf("Select menu 1.sell 2.refund 3.checkstock 4.poweroff( 1 , 2 , 3, 4 ) \n");
		
		menu_selection = getMenuTouchInput(); //다시입력받는다
		
		return 0;
	}
	else
		return menu_selection;
}