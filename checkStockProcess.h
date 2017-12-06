#pragma once
#include "menu.h"

#include "printReceipts.h"
void DisplayStock(stockE list[]);

void checkStockProcess() 
{
	
	printStockCheckMenu();
//	UpdateTime(1);
	DisplayStock(getStockFromDB()); //DB에서 재고를 가져와 출력
	printStockReceipt(getStockFromDB()); //DB에서 재고를 프린터로넘겨줌
}

void DisplayStock(stockE list[])
{
	int date = getDate();
	char dateC[15];
	sprintf(dateC, "%d", date);
	printf("*******CASHER DISPLAY******* : \n"); //cashier Display
	printf("date : %s \n",dateC);
	for (int i = 0; i < 7; i++) //리스트
	{
		printf("%s %d %d \n", list[i].name, list[i].price, list[i].quantity);
	}
	printf("*******CASHER DISPLAY END******* : \n"); //cashier Display end
	printf("\n");
	printf("\n");

}