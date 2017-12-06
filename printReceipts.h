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
	char receiptFileName[30] = "sale_"; //�����̸�����
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total=0; 
	strcpy(receiptNum, getYMDhm());
	//sprintf(receiptNum, "%d", ReceiptnumInt);
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //�����̸������Ϸ�

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "receipt number : %s \n", receiptNum);
	fprintf(fp, "Date : %d \n",getDate());
	fprintf(fp, "Sale Product \n");
	for (int i = 0; i < 7; i++) //write file �ǸŸ���Ʈ
	{
		fprintf(fp, "%s %d %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, b[i], b[i] *(getStockFromDB()[i].price));
	}
	for (int i = 0; i < 7; i++) //�Ǹ��Ѿװ��
	{
		total += (getStockFromDB()[i].price * b[i]);
	}
	fprintf(fp, "total : %d \n", total); //total �Ǹž� writefile
	fclose(fp);
	updateReceiptList(receiptNum); // ������ ����Ʈ :ȯ���Ҷ� �������ֳ�Ȯ���Ҷ� �ʿ�
	printf("PRINT RECEIPT Complete\n");
}


void printRefundReceipt(productR productList[])
{
	char receiptFileName[30] = "refund_"; //�����̸�����
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	strcpy(receiptNum, getYMDhm());
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //�����̸������Ϸ�

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "receipt number : %s \n", receiptNum);
	fprintf(fp, "Date : %d \n", getDate());
	fprintf(fp, "Refund Product \n");
	for (int i = 0; i < 7; i++) //write file �ǸŸ���Ʈ
	{
		fprintf(fp, "%s %d %d %d \n", productList[i].name, productList[i].price, productList[i].quantity, productList[i].salePrice);
	}
	for (int i = 0; i < 7; i++) //�Ǹ��Ѿװ��
	{
		total += (productList[i].price *  productList[i].quantity);
	}
	fprintf(fp, "refund total : %d \n", total); //total �Ǹž� writefile
	fclose(fp);
	printf("PRINT REFUND RECEIPT Complete\n");
}

void printStockReceipt(stockE productList[])
{
	char receiptFileName[30] = "stock_"; //�����̸�����
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	strcpy(receiptNum, getYMDhm());
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //�����̸������Ϸ�

	FILE * fp = fopen(receiptFileName, "wt");

	fprintf(fp, "Date : %d \n", getDate());
	
	for (int i = 0; i < 7; i++) //write file �ǸŸ���Ʈ
	{
		fprintf(fp, "%s %d %d \n", productList[i].name, productList[i].price, productList[i].quantity);
	}
	
	fclose(fp);
	printf("PRINT STOCK RECEIPT Complete\n");
}

void printSettle()
{
	char receiptFileName[30] = "settle_"; //�����̸�����
	char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	//int ReceiptnumInt = generateReceiptNum();
	int total = 0;
	sprintf(receiptNum, "%d", getDate());
	//sprintf(receiptNum, "%d", ReceiptnumInt);
	strcat(receiptFileName, receiptNum);
	strcat(receiptFileName, receiptFileTxt); //�����̸������Ϸ�

	FILE * fp = fopen(receiptFileName, "wt");
	fprintf(fp, "Date : %d \n", getDate());
	fprintf(fp, "Sale Product \n");
	for (int i = 0; i < 7; i++) //write file �ǸŸ���Ʈ
	{
		fprintf(fp, "%s %d %d %d \n", getStockFromDB()[i].name, getStockFromDB()[i].price, (100 - getStockFromDB()[i].quantity), (100 - getStockFromDB()[i].quantity) * (getStockFromDB()[i].price));
	}
	for (int i = 0; i < 7; i++) //�Ǹ��Ѿװ��
	{
		total += (100 - getStockFromDB()[i].quantity) * (getStockFromDB()[i].price);
	}
	fprintf(fp, "total Sale : %d \n", total); //total �Ǹž� writefile
	fclose(fp);
}


int generateReceiptNum(void) //���ļ���
{
	int receiptNum = clock()/100;
	return receiptNum;
}

void updateReceiptList(char s[15]) // ������ ����Ʈ :ȯ���Ҷ� �������ֳ�Ȯ���Ҷ� �ʿ�
{
	FILE * fp = fopen("receiptList.txt", "at");
	fprintf(fp, "%s \n", s);
	fclose(fp);
}

void clearReceiptList() // ����������Ʈ �ʱ�ȭ : ���߿� ��¥ ����� �ʿ�
{
	FILE * fp = fopen("receiptList.txt", "wt");
	fprintf(fp, "\n");
	fclose(fp);
}



