#pragma once
#include <stdio.h>
#include <time.h>

void UpdateTime(int c,int startTime)
{
	int y, mo, d, h, m, s;
	int lastTime, totalTime;
	time_t ctime;
	int currentTimesys = time(&ctime);
	int currentTime = (currentTimesys-startTime)*480;
	FILE *fp = fopen("time.txt", "rt");
	fscanf(fp, "%d", &totalTime);
	fscanf(fp, "%d", &lastTime);
	totalTime = totalTime + (currentTime - lastTime);
	fclose(fp);
	FILE *fp2 = fopen("time.txt", "wt");
	fprintf(fp2, "%d \n", totalTime);
	if (c == 1) //������Ʈ
		fprintf(fp2, "%d \n", currentTime);
	if (c == 2) //����
		fprintf(fp2, "%d \n", 0);
	fclose(fp2);
	y = 2000;
	mo = 1;
	d = 1 + ((totalTime / 3600) / 24);
	h = (totalTime / 3600) % 24;
	m = (totalTime % 3600 / 60);
	s = ((totalTime % 3600) % 60);
	FILE *fp3 = fopen("YYYYMMDD.txt", "wt");
	fprintf(fp3, "%d%02d%02d \n", y, mo, d);
	fclose(fp3);
	FILE *fp4 = fopen("YYYYMMDDhhmm.txt", "wt");
	fprintf(fp4, "%d%02d%02d%02d%02d \n", y, mo, d, h, m);
	fclose(fp4);


}

char * getYMDhm()
{
	static char YMDhm[15];
	FILE *fp = fopen("YYYYMMDDhhmm.txt", "rt");
	fscanf(fp, "%s", YMDhm);
	fclose(fp);
	return YMDhm;
}

int getDate()
{
	int date;
	FILE *fp = fopen("YYYYMMDD.txt", "rt");
	fscanf(fp, "%d", &date);
	fclose(fp);
	return date;
}

/*
int main(void)
{

	while (1)
	{
		int a = 0;
		scanf("%d", &a);
		if (a == 1)
		{
			UpdateTime(a);
			printf("������Ʈ�Ϸ� \n");
		}
		if (a == 2)
		{
			UpdateTime(1);
			UpdateTime(a);
			printf("�ý������� \n");
			return 0;
		}
	}
}
*/