#pragma once
#include <stdio.h>
#include <string.h>
#include "sysTime.h"
typedef struct StockE
{
	char name[15];
	int price;
	char barcode[5];
	int quantity;

} stockE;
stockE *getStockFromDB();
void updateStockAfterRefund(int s[7]);
void resetStock();
char *generateDate();
void updateSaleManage(int s[7]);
void resetSaleManage();

void resetStock()
{
	char fileName[30];
	strcpy(fileName, generateDate());
	FILE * fp2 = fopen(fileName, "wt");
	fprintf(fp2, "chip 1000 001 100 \n");
	fprintf(fp2, "icecream 1500 010 100 \n");
	fprintf(fp2, "fruit 3000 011 100 \n");
	fprintf(fp2, "water 500 100 100 \n");
	fprintf(fp2, "ramen 800 101 100 \n");
	fprintf(fp2, "drink 1200 110 100 \n");
	fprintf(fp2, "coffee 2000 111 100 \n");
	fclose(fp2);
	/*
	stockE stockListUp[7];
	char fileName[30];
	for (int i = 0; i < 7; i++)  //update data
	{
		strcpy(stockListUp[i].name, getStockFromDB()[i].name);
		stockListUp[i].price = getStockFromDB()[i].price;
		strcpy(stockListUp[i].barcode, getStockFromDB()[i].barcode);
		stockListUp[i].quantity = 100;
	}
	strcpy(fileName, generateDate());

	FILE * fp2 = fopen(fileName, "wt");
	for (int i = 0; i < 7; i++) //write file
	{
		fprintf(fp2, "%s %d %s %d \n", stockListUp[i].name, stockListUp[i].price, stockListUp[i].barcode, stockListUp[i].quantity);
	}
	fclose(fp2); 
	*/
}


void updateStockAfterSell(int s[7])  //update stock after sell
{
	stockE stockListUp[7];
	char fileName[30];
	for (int i = 0; i < 7; i++)  //update data
	{
		strcpy(stockListUp[i].name, getStockFromDB()[i].name);
		stockListUp[i].price = getStockFromDB()[i].price;
		strcpy(stockListUp[i].barcode, getStockFromDB()[i].barcode);
		stockListUp[i].quantity = getStockFromDB()[i].quantity-s[i];
	}
	strcpy(fileName, generateDate());
	FILE * fp2 = fopen(fileName, "wt");
	for (int i = 0; i < 7; i++) //write file
	{
		fprintf(fp2, "%s %d %s %d \n", stockListUp[i].name, stockListUp[i].price, stockListUp[i].barcode, stockListUp[i].quantity);
	}
	fclose(fp2);
	
}

void updateStockAfterRefund(int s[7])  //update stock after sell
{
	stockE stockListUp2[7];
	char fileName[30];
	for (int i = 0; i < 7; i++)  //update data
	{
		strcpy(stockListUp2[i].name, getStockFromDB()[i].name);
		stockListUp2[i].price = getStockFromDB()[i].price;
		strcpy(stockListUp2[i].barcode, getStockFromDB()[i].barcode);
		stockListUp2[i].quantity = getStockFromDB()[i].quantity + s[i];
	}
	strcpy(fileName, generateDate());
	FILE * fp2 = fopen(fileName, "wt");
	for (int i = 0; i < 7; i++) //write file
	{
		fprintf(fp2, "%s %d %s %d \n", stockListUp2[i].name, stockListUp2[i].price, stockListUp2[i].barcode, stockListUp2[i].quantity);
	}
	fclose(fp2);

	printf("DB_stock Update Complete \n");

}

stockE *getStockFromDB() //getstockfrom File YYMMDD_product.txt
{
	static stockE stockList[7];
	char fileName[30];
	strcpy(fileName, generateDate());
	FILE *fp = fopen(fileName, "rt");
	int ret;
	for (int i = 0; i < 7; i++)
	{
		ret = fscanf(fp, "%s %d %s %d", stockList[i].name, &stockList[i].price, stockList[i].barcode, &stockList[i].quantity);

	}
	fclose(fp);
	return stockList;
}

char *generateDate()
{
	static char receiptFileName[30] = "_product.txt"; //파일이름생성
	static char receiptNum[30];
	int date=getDate();
	sprintf(receiptNum, "%d", date);
	//strcpy(receiptNum, getYMDhm());
	//int ReceiptnumInt = generateReceiptNum();
	//sprintf(receiptNum, "%d", ReceiptnumInt);
	strcat(receiptNum, receiptFileName); //파일이름생성완료
	return receiptNum;
}


void updateSaleManage(int s[7])  //update stock after sell
{
	stockE stockListUp2[7];
	int totalPrice[7];
	char fileName[30]="_sale_management.txt";
	char receiptNum[30];
	int date = getDate();
	//char garbage[20];
	sprintf(receiptNum, "%d", date);
	strcat(receiptNum, fileName);
	FILE * fp2 = fopen(receiptNum, "rt");
	//fscanf(fp2, "%s", garbage);
	for (int i = 0; i < 7; i++)
	{
		fscanf(fp2, "%s %d %d %d", stockListUp2[i].name, &stockListUp2[i].price, &stockListUp2[i].quantity , &totalPrice[i]);

	}
	fclose(fp2);
	FILE * fp4 = fopen(receiptNum, "wt");
	//dprintf(fp4, "Sale product \n");
	for (int i = 0; i < 7; i++) //write file
	{
		stockListUp2[i].quantity += s[i];
		totalPrice[i] = (stockListUp2[i].quantity)*(getStockFromDB()[i].price);
		fprintf(fp4, "%s %d %d %d \n", stockListUp2[i].name, stockListUp2[i].price, stockListUp2[i].quantity, totalPrice[i]);
	}
	fclose(fp4);
	printf("DB_stock Update Complete \n");

}

void resetSaleManage()
{
	stockE stockListUp2[7];
	int totalPrice[7] = { 0,0,0,0,0,0,0 };
	char fileName[30] = "_sale_management.txt";
	char receiptNum[30];
	int date = getDate();
	sprintf(receiptNum, "%d", date);
	strcat(receiptNum, fileName);
	for (int i = 0; i < 7; i++)  //update data
	{
		strcpy(stockListUp2[i].name, getStockFromDB()[i].name);
		stockListUp2[i].price = getStockFromDB()[i].price;
		stockListUp2[i].quantity = 0;
	}
	FILE * fp3 = fopen(receiptNum, "wt");
	//fprintf(fp3, "Sale product \n");
	for (int i = 0; i < 7; i++) //write file
	{
		fprintf(fp3, "%s %d %d %d \n", stockListUp2[i].name, stockListUp2[i].price, stockListUp2[i].quantity, totalPrice[i]);
	}
	fclose(fp3);
}