#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include "UpdateDB.h"
#include "sysTime.h"

int generateReceiptNum(void);
void updateReceiptList(char s[15]);
void clearReceiptList();
void printSettle();

typedef struct productNow
{
	char name[15];
	int price;
	int quantity;

} productNow;

typedef struct productR
{
	char name[15];
	int price;
	int quantity;
	int salePrice;

} productR;



void printReceipt(int b[7])
{
	char receiptFileName[30] = "sale_"; //파일이름생성
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total=0; 
	strcpy(receiptNum, getYMDhm());
	//sprintf(receiptNum, "%d", ReceiptnumInt);
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //파일이름생성완료

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "receipt number : %s \n", receiptNum);
	fprintf(fp, "Date : %d \n",getDate());
	fprintf(fp, "Sale Product \n");
	for (int i = 0; i < 7; i++) //write file 판매리스트
	{
		fprintf(fp, "%s %d %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, b[i], b[i] *(getStockFromDB()[i].price));
	}
	for (int i = 0; i < 7; i++) //판매총액계산
	{
		total += (getStockFromDB()[i].price * b[i]);
	}
	fprintf(fp, "total : %d \n", total); //total 판매액 writefile
	fclose(fp);
	updateReceiptList(receiptNum); // 영수증 리스트 :환불할때 영수증있나확인할때 필요
	printf("PRINT RECEIPT Complete\n");
}


void printRefundReceipt(productR productList[])
{
	char receiptFileName[30] = "refund_"; //파일이름생성
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	strcpy(receiptNum, getYMDhm());
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //파일이름생성완료

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "receipt number : %s \n", receiptNum);
	fprintf(fp, "Date : %d \n", getDate());
	fprintf(fp, "Refund Product \n");
	for (int i = 0; i < 7; i++) //write file 판매리스트
	{
		fprintf(fp, "%s %d %d %d \n", productList[i].name, productList[i].price, productList[i].quantity, productList[i].salePrice);
	}
	for (int i = 0; i < 7; i++) //판매총액계산
	{
		total += (productList[i].price *  productList[i].quantity);
	}
	fprintf(fp, "refund total : %d \n", total); //total 판매액 writefile
	fclose(fp);
	printf("PRINT REFUND RECEIPT Complete\n");
}

void printStockReceipt(stockE productList[])
{
	char receiptFileName[30] = "stock_"; //파일이름생성
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	strcpy(receiptNum, getYMDhm());
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //파일이름생성완료

	FILE * fp = fopen(receiptFileName, "wt");

	fprintf(fp, "Date : %d \n", getDate());
	
	for (int i = 0; i < 7; i++) //write file 판매리스트
	{
		fprintf(fp, "%s %d %d \n", productList[i].name, productList[i].price, productList[i].quantity);
	}
	
	fclose(fp);
	printf("PRINT STOCK RECEIPT Complete\n");
}

void printSettle()
{
	char receiptFileName[30] = "settle_"; //파일이름생성
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	sprintf(receiptNum, "%d", getDate());
	//sprintf(receiptNum, "%d", ReceiptnumInt);
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //파일이름생성완료

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "Date : %d \n", getDate());
	fprintf(fp, "Sale Product \n");
	for (int i = 0; i < 7; i++) //write file 판매리스트
	{
		fprintf(fp, "%s %d %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, (100 - getStockFromDB()[i].quantity), (100 - getStockFromDB()[i].quantity) * (getStockFromDB()[i].price));
	}
	for (int i = 0; i < 7; i++) //판매총액계산
	{
		total += (100 - getStockFromDB()[i].quantity) * (getStockFromDB()[i].price);
	}
	fprintf(fp, "total Sale : %d \n", total); //total 판매액 writefile
	fclose(fp);
}


int generateReceiptNum(void) //추후수정
{
	int receiptNum = clock()/100;
	return receiptNum;
}

void updateReceiptList(char s[15]) // 영수증 리스트 :환불할때 영수증있나확인할때 필요
{
	FILE * fp = fopen("receiptList.txt", "at");
	fprintf(fp, "%s \n", s);
	fclose(fp);
}

void clearReceiptList() // 영수증리스트 초기화 : 나중에 날짜 변경시 필요
{
	FILE * fp = fopen("receiptList.txt", "wt");
	fprintf(fp, "\n");
	fclose(fp);
}



