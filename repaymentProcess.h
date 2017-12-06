#pragma once
#include "menu.h"
#include "DetermineBarcodeInfo.h"

#include "printReceipts.h"



int checkBarcodeValid(char barcode[15]);
productR * getDataFromReceipt(char barcode[15]);
void DisplayRe(productR list[],char barcode[15]);

void repaymentProcess()
{
	int b[7] = { 0,0,0,0,0,0,0 }; //환불예정중인 물품갯수
	char barcode[15];
	printRefundMenu();
	strcpy(barcode,barcodeScannerDataR());
	productR repaymentList[7];
	
	if (checkBarcodeValid(barcode) == 1)
	{

		int val;
		printf("Barcode valid, Continue refund? (1.yes  2.no) \n");
		scanf("%d", &val);
		if (val == 1)
		{
			printf("Proceeding to refund \n");
			for (int i = 0; i < 7; i++)  //update data (getdata from receipt)
			{
				strcpy(repaymentList[i].name, getDataFromReceipt(barcode)[i].name);
				repaymentList[i].price = getDataFromReceipt(barcode)[i].price;
				repaymentList[i].quantity = getDataFromReceipt(barcode)[i].quantity;
				repaymentList[i].salePrice = getDataFromReceipt(barcode)[i].salePrice;
			}
			DisplayRe(repaymentList, barcode); //Display Cashier ,customer
			for (int i = 0; i < 7; i++)  //update data (getdata from receipt)
			{
				b[i] = getDataFromReceipt(barcode)[i].quantity;
			}
			//UpdateTime(1);
			updateStockAfterRefund(b);

			printRefundReceipt(repaymentList);

		}
		else
		{
			printf("canceled refund \n");
		}
	}
	else
	{
		printf("Wrong Barcode \n");
	}
	
}




int checkBarcodeValid(char barcodeC[15]) //이전에 발급했던여수증인지 확인
{
	char receiptData[10][15];
	int valid=0;
	FILE *fp = fopen("receiptList.txt", "rt");
	int ret;
	for (int i = 0; i < 10; i++)
	{
		ret = fscanf(fp, "%s", receiptData[i]);
	}
	fclose(fp);
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(barcodeC,receiptData[i])==0)
		{
			valid = 1;
			break;
		}
	}
	return valid;
}

productR * getDataFromReceipt(char barcode[15])
{
	char garbage1[15];
	char garbage2[15];
	char garbage3[15];
	char garbage4[25]; //garbage
	static productR List[7];

	char receiptFileName[30] = "sale_"; //파일이름생성
	//char receiptNum[15];
	char receiptFileTxt[] = ".txt";
	strcat(receiptFileName, barcode);
	strcat(receiptFileName, receiptFileTxt);
	FILE * fp = fopen(receiptFileName, "rt");

	fscanf(fp, "%s %s %s %s", garbage1, garbage2, garbage3, garbage4); // 파일포인터 이동용 
	fscanf(fp, "%s %s %s", garbage1, garbage2, garbage3);
	fscanf(fp, "%s %s", garbage1, garbage2); 
	for (int i = 0; i < 7; i++)
	{
		fscanf(fp, "%s %d %d %d", List[i].name, &List[i].price, &List[i].quantity, &List[i].salePrice);

	}
	fclose(fp);

	return List;
}

void DisplayRe(productR list[], char barcode[15])
{
	printf("*******CASHER DISPLAY******* : \n"); //cashier Display
	printf("solddate: %s \n",barcode); //판매날짜 미구현..
	int total = 0;
	for (int i = 0; i < 7; i++) //환불총액계산
	{
		total += list[i].salePrice;
	}
	printf("Refund total: %d \n", total);
	for (int i = 0; i < 7; i++) //환불리스트
	{
		printf("%s %d %d %d \n", list[i].name, list[i].price, list[i].quantity,list[i].salePrice);
	}
	printf("*******CASHER DISPLAY END******* : \n"); //cashier Display end
	printf("\n");
	printf("\n");
	printf("*******CUSTOMER DISPLAY******* : \n"); //customer Display
	printf("solddate: %s \n", barcode); //판매날짜 미구현..
	printf("refund total: %d \n", total);
	printf("*******CUSTOMER DISPLAY End******* : \n"); //customer Display
	printf("\n");
	printf("\n");
}