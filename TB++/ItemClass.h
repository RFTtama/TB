#pragma once
#define COMMON 30
#define UN_COMMON 24
#define REA 12
#define SUPER_REA 8
#define EPIQ 5
#define LEGENDARY 1

class ItemClass {
public:
	char name[25];
	char description[255];
	char skillDesc[255];
	int price;
	int reality;
};