#pragma once
#include <stdio.h>
#include <string.h>
#include "BarcodeInterface.h"

char * barcodeScannerData() //상품
{
	static char barcodeData[5];
	strcpy(barcodeData, getBarcodeScannerInput());
	return barcodeData;
}

char* barcodeScannerDataR() //영수증 바코드
{
	static char barcodeI[15];
	strcpy(barcodeI, getBarcodeScannerInputR());
	return barcodeI;
}