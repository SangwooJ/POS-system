#include <stdio.h>
#include "menu.h"
#include "DetermineTouchInfo.h"
#include "Controller.h"

int main(void)
{
	int power=0;
	while (1)
	{
		printf("to turn on power enter 1 :\n");
		scanf("%d", &power);
		if (power == 1)
		{
			break;
		}
		else
		{
			printf("sleeping... \n");
		}
	}
	Controller(power);
	return 0;

}