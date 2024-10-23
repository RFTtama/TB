#pragma once
#define ENAMES 25

/* クラスのひな型		*/
typedef struct
{
	int (*GetEnemyId)(void);
	void (*SetEnemyId)(int);
	void (*SetEnemyName)(int, char[ENAMES]);
}EnemyDefine;

/* 敵情報保存用構造体	*/
typedef struct
{
	char EnemyName[ENAMES];
}EnemyInfo;

/* コンストラクタ		*/
static EnemyDefine* EnemyDefineConstructor(void);