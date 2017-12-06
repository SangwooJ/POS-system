#pragma once
#include <stdio.h>
#include "DetermineBarcodeInfo.h"
#include "menu.h"

#include "printReceipts.h"

//void barcodeDataToProduct(productNow productList[],int i);
int isProductInTheList();
void salesProcess();
void printProductInTheList(productNow productList[], int b[7]);
void resetList(productNow productList[]);
void printReceipt(int b[7]);
void Display(productNow productList[], int b[7]);




void salesProcess()
{
	productNow productList[7]; // 판매중리스트
	int i=0,j = 0;
	int k = i + j;
	int a[7] = { -1,-1,-1,-1,-1,-1,-1};//판매중리스트의 각 상품별 리스트위치
	int b[7] = { 0,0,0,0,0,0,0 }; //결제예정중인 물품갯수
	resetList(productList); //reset currentList


	//추후함수로분리
	for (i = 0; i < 8; i++)
	{
		int k = i + j;
		int payment = 0;
		int selection = 0;
		int type = 10;
		printSaleMenu();
		//barcodeDataToProduct(productList,i);
		
		char barcodeData[5];

		strcpy(barcodeData, barcodeScannerData());
		if (strcmp(barcodeData, "001") == 0)  
		{
			if (a[0] == -1) //판매중리스트에 없다면 리스트에 새로추가
			{
				strcpy(productList[k].name, "chip");
				productList[k].price = 1000;
				productList[k].quantity = 1;
				a[0] = k; //추가 되었으니 다음번 부터는 중복임이고 리스트위치기억..
				b[0] ++; //제품갯수 추후 업데이트에서 b만큼 마이너스된다.. 
			}
			else //판매중리스트에 있다면 수량추가
			{
				productList[a[0]].quantity += 1;
				j -= 1;
				b[0] ++;
			}
		}
		else if (strcmp(barcodeData, "010") == 0)
		{
			if (a[1] == -1)
			{
				strcpy(productList[k].name, "icecream");
				productList[k].price = 1500;
				productList[k].quantity = 1;
				a[1] = k;
				b[1] ++;
			}
			else
			{
				productList[a[1]].quantity += 1;
				j -= 1;
				b[1] ++;
			}
		}
		else if (strcmp(barcodeData, "011") == 0)
		{
			if (a[2] == -1)
			{
				strcpy(productList[k].name, "fruit");
				productList[k].price = 3000;
				productList[k].quantity = 1;
				a[2] = k;
				b[2] ++;
			}
			else
			{
				productList[a[2]].quantity += 1;
				j -= 1;
				b[2] ++;
			}
		}
		else if (strcmp(barcodeData, "100") == 0)
		{
			if (a[3] == -1)
			{
				strcpy(productList[k].name, "water");
				productList[k].price = 500;
				productList[k].quantity = 1;
				a[3] = k;
				b[3] ++;
			}
			else
			{
				productList[a[3]].quantity += 1;
				j -= 1;
				b[3] ++;
			}
		}
		else if (strcmp(barcodeData, "101") == 0)
		{
			if (a[4] == -1)
			{
				strcpy(productList[k].name, "ramen");
				productList[k].price = 800;
				productList[k].quantity = 1;
				a[4] = k;
				b[4] ++;
			}
			else
			{
				productList[a[4]].quantity += 1;
				j -= 1;
				b[4] ++;
			}
		}
		else if (strcmp(barcodeData, "110") == 0)
		{
			if (a[5] == -1)
			{
				strcpy(productList[k].name, "drink");
				productList[k].price = 1200;
				productList[k].quantity = 1;
				a[5] = k;
				b[5] ++;
			}
			else
			{
				productList[a[5]].quantity += 1;
				j -= 1;
				b[5] ++;
			}
		}
		else if (strcmp(barcodeData, "111") == 0)
		{
			if (a[6] == -1)
			{
				strcpy(productList[k].name, "coffee");
				productList[k].price = 2000;
				productList[k].quantity = 1;
				a[6] = k;
				b[6] ++;
			}
			else
			{
				productList[a[6]].quantity += 1;
				j -= 1;
				b[6] ++;
			}
		}
		else 
			printf("wrong barcode \n");

		printf("*********PRODUCT LIST*********\n");
		printProductInTheList(productList, b);
		
		printf("enter 1 to proceed Payment. enter 2 to continue scanning enter 3 to add/delete \n");
		scanf("%d", &payment);
		if (payment == 1)
		{
			break; //for문 탈출
		}
		else if (payment == 3)
		{
			printf("select 1.add  2.reduce 3.delete \n");
			scanf("%d", &selection);
			if (selection == 1)
			{
				printf("select product 0 1 2 3 4 5 6 \n");
				scanf("%d", &type);
				if (b[type] != 0)
					b[type]++;
				else
					printf("invalid value \n");
				printProductInTheList(productList, b);
			}
			else if (selection == 2)
			{
				printf("select product 0 1 2 3 4 5 6 \n");
				scanf("%d", &type);
				if (b[type] != 0)
					b[type]--;
				else
					printf("invalid value \n");
				printProductInTheList(productList, b);
			}
			else if (selection == 3)
			{
				printf("select product 0 1 2 3 4 5 6 \n");
				scanf("%d", &type);
				if (b[type] != 0)
					b[type] = 0;
				else
					printf("invalid value \n");
				printProductInTheList(productList, b);
			}
			else
				printf("invalid value \n");
			
		}
		else if(payment !=2)
			printf("invalid value \n");
		
	}
	//for문 종료


	printf("*********PRODUCT LIST*********\n");
	printProductInTheList(productList,b);
	printf("**************************\n");
	printf("\n");
	printf("\n");
	printf("payment processing..\n");
	printf("\n");
	printf("\n");
	Display(productList,b);
	updateStockAfterSell(b);  //update stock
	printf("Stock Update Complete \n");
	printReceipt(b);
	updateSaleManage(b);
	printf("Sale mangement Update Complete \n");
	printf(" \n");
	printf(" \n");
	printf(" \n");
}

/*
void barcodeDataToProduct(productNow productList[],int i)
{
	int j = 0;
	int k = i+j;
	int a=-1, b=-1, c=-1, d=-1, e=-1, f=-1, g = -1;
	char barcodeData[5];

	strcpy(barcodeData, barcodeScannerData());
	if (strcmp(barcodeData, "100") == 0)
	{
		printf("%d", a);
		if (a == -1)
		{
			strcpy(productList[k].name, "과자");
			productList[k].price = 1000;
			productList[k].quantity = 1;
			a = k;
			printf("%d", a);
		}
		else
		{
			productList[a].quantity += 1;
			j -= 1;
		}
	}
	else if (strcmp(barcodeData, "010") == 0)
	{
		strcpy(productList[k].name, "아이스크림");
		productList[k].price = 1500;
		productList[k].quantity = 1;
	}
	else if (strcmp(barcodeData, "011") == 0)
	{
		strcpy(productList[i].name, "아이스크림");
		productList[i].price = 1500;
		productList[i].quantity = 1;
	}
	else if (strcmp(barcodeData, "100") == 0)
	{
		strcpy(productList[i].name, "과자");
		productList[i].price = 1000;
		productList[i].quantity = 1;
	}
	else if (strcmp(barcodeData, "101") == 0)
	{
		strcpy(productList[i].name, "과자");
		productList[i].price = 1000;
		productList[i].quantity = 1;
	}
	else if (strcmp(barcodeData, "110") == 0)
	{
		strcpy(productList[i].name, "과자");
		productList[i].price = 1000;
		productList[i].quantity = 1;
	}
	else if (strcmp(barcodeData, "111") == 0)
	{
		strcpy(productList[i].name, "과자");
		productList[i].price = 1000;
		productList[i].quantity = 1;
	}

}
*/

int isProductInTheList() 
{
	return 0;
}

void printProductInTheList(productNow productList[], int b[7]) //판매중리스트 출력
{
	for (int i = 0; i < 7; i++)
	{
		printf("%s %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, b[i]);
	}
}

void resetList(productNow productList[]) //판매중리스트 초기화
{
	for (int i = 0; i < 7; i++)
	{
		strcpy(productList[i].name, "0");
		productList[i].price=0;
		productList[i].quantity=0;
	}
}



void Display(productNow productList[],int b[7])
{
	int total=0;
	int cash;
	int leftCash;
	printf("*******CASHER DISPLAY******* : \n"); //cashier Display
	
	
	for (int i = 0; i < 7; i++) //판매총액계산
	{
		total = total + (getStockFromDB()[i].price *b[i]);
		
	}
	printf(" total : %d ", total);
	while (1)
	{
		printf("PayWith cash. Insert Cash  : not enough money \n");
		scanf("%d", &cash);
		if (cash >= total)
			break;
	}
	leftCash = cash - total;
	printf("Total amount: %d \n", total);
	printf("Cash input : %d \n", cash);
	printf("Leftmoney: %d \n", leftCash);
	for (int i = 0; i < 7; i++)
	{
		printf("%s %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, b[i]);
	}
	printf("*******CASHER DISPLAY END******* : \n");  //cashier Display End
	printf("\n");
	printf("\n");
	printf("*******CUSTOMER DISPLAY******* : \n"); //cu Display
	printf("Total amount: %d \n", total);
	printf("Cash input : %d \n", cash);
	printf("Leftmoney: %d \n", leftCash);
	printf("*******CUSTOMER DISPLAY END******* : \n"); //cu display end
	printf("\n");
	printf("\n");
}

