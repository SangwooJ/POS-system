#pragma once
#include <stdio.h>

char* getBarcodeScannerInput()  // ��ǰ���ڵ� ������ ����
{
	static char barcode[5];
	scanf("%s", barcode);
	return barcode;
}

char* getBarcodeScannerInputR() // ������
{
	static char barcodeR[15];
	scanf("%s", barcodeR);
	return barcodeR;
}

