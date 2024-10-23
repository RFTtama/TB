#pragma once
#define SGM_ALL 0
#define SGM_PLA 1
#define SGM_ENE 2

/* �N���X�̂ЂȌ^	*/
typedef struct
{
	void (*ClearNowSG)(int);
	void (*SetMaxSG)(short, int);
	short (*GetMaxSG)(int);
	void (*MinusMaxSG)(int);
	void (*PlusNowSG)(short, int);
	short (*GetNowSG)(int);
	double (*GetPercentage)(int);
	unsigned char (*GetStrikeFlg)(int);
	void (*ClearStrikeFlg)(int);
}StrikeGageManager;

/* �R���X�g���N�^	*/
static StrikeGageManager* StrikeGageConstructor(void);