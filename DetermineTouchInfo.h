#pragma once
#include <stdio.h>
#include "TouchInterface.h"

int menuTouchData()  // �޴���ư ������  ����
{
	int menu_selection;
	menu_selection = getMenuTouchInput();
	if (menu_selection != 1 && menu_selection != 2 && menu_selection != 3 && menu_selection != 4) //1,2,3 �ܸ̿� �Է��ϸ�
	{
		printf("input error . retype : \n");
		printf("Select menu 1.sell 2.refund 3.checkstock 4.poweroff( 1 , 2 , 3, 4 ) \n");
		
		menu_selection = getMenuTouchInput(); //�ٽ��Է¹޴´�
		
		return 0;
	}
	else
		return menu_selection;
}