#pragma once
#include <stdio.h>
#include "menu.h"
#include "DetermineTouchInfo.h"
#include "salesProcess.h"
#include "repaymentProcess.h"
#include "checkStockProcess.h"

void Controller(int power)  
{
	time_t ctime;
	int startTime = time(&ctime);
	UpdateTime(1,startTime);
	int date =getDate();
	while (power == 1)
	{
		printMenu();
		printSettle();
		int menu = menuTouchData();
		UpdateTime(1,startTime);
		if ((date + 1) == getDate())
		{
			UpdateTime(1,startTime);
			resetStock();
			resetSaleManage();
			printf("One day passed \n");
			
		}
		else {
			printf("One day nNOT passed \n");
			UpdateTime(1,startTime);
		}
		date=getDate();
		if (menu == 1)
		{
			printf("running sell \n"); //���ļ���
			salesProcess();
			UpdateTime(1, startTime);
		}
		else if (menu == 2)
		{
			printf("running refund \n"); //���ļ���
			repaymentProcess();
			UpdateTime(1, startTime);
		}
		else if (menu == 3)
		{
			printf("running stock check \n"); //���ļ���
			checkStockProcess();
			UpdateTime(1, startTime);
		}
		else if (menu == 4)
		{
			UpdateTime(2,startTime);
			break;
		}
	}
}