#pragma once
#include <stdio.h>

char* getBarcodeScannerInput()  // 상품바코드 데이터 전달
{
	static char barcode[5];
	scanf("%s", barcode);
	return barcode;
}

char* getBarcodeScannerInputR() // 영수증
{
	static char barcodeR[15];
	scanf("%s", barcodeR);
	return barcodeR;
}

