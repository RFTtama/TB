#pragma once
#include "MT.h"
#include <time.h>
#include <stdio.h>

#define ER_STR_SIZE 96
char erstr[ER_STR_SIZE];

int randnum(int value)
{
	int randomVal;
	if (value > 0) {
		randomVal = genrand_int32() % value;
	}
	else {
		randomVal = 0;
	}
	return randomVal;
}

void timer(int toTime)
{
	clock_t start, clockt;
	start = clock();
	clockt = clock();      /* time = 1ms.....1s = 1000ms   */
	while (clockt - start <= toTime) {
		clockt = clock();
	}
}

void connum(int* adr_int32) {
	int mem = 0;
	char s[255];
	fgets(s, 255, stdin);
	mem = atoi(s);
	*adr_int32 = mem;
}

void connum_int16(short int* adr_int16) {
	short int mem = 0;
	char s[255];
	while (mem < 48 || mem > 57) {
		gets_s(s, (unsigned)sizeof(s));
		mem = s[0];
	}
	mem -= 48;
	*adr_int16 = mem;
}

void randchar(int c) {
	unsigned char a = 0xff, b;
	time_t t;
	time(&t);
	c--;
	for (int i = 0; i <= c; i++) {
		a = genrand_int32() % 0x06 + 2;
		a = a << 4;
		b = genrand_int32() % 0x10;
		a = a + b;
		switch (a % 3) {
		case 0:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COMMON_LVB_GRID_LVERTICAL | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
			break;
		case 1:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COMMON_LVB_GRID_RVERTICAL | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
			break;
		case 2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COMMON_LVB_GRID_HORIZONTAL | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
		}

		printf("%c", a);
		timer(10);
	}
	SetColor();
	printf("\n");
}

void errorOutput(void) {
	printf("\aError: %s\n\n", erstr);
	FILE* log;
	if(fopen_s(&log, "ErrorLog.txt", "a") != 0){
		printf("Error: Log output failed\n");
	}
	else {
		fprintf(log, "Error: %s\n\n", erstr);
	}
	startWait();
}