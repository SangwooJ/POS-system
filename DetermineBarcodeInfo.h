#pragma once
#include <stdio.h>
#include <string.h>
#include "BarcodeInterface.h"

char * barcodeScannerData() //��ǰ
{
	static char barcodeData[5];
	strcpy(barcodeData, getBarcodeScannerInput());
	return barcodeData;
}

char* barcodeScannerDataR() //������ ���ڵ�
{
	static char barcodeI[15];
	strcpy(barcodeI, getBarcodeScannerInputR());
	return barcodeI;
}