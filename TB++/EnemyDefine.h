#pragma once
#define ENAMES 25

/* クラスのひな型	*/
typedef struct
{
	int (*GetEnemyId)(void);
	void (*SetEnemyId)(int);
	void (*SetEnemyName)(int, char[ENAMES]);
}EnemyDefine;

/* コンストラクタ	*/
static EnemyDefine* EnemyDefineConstructor(void);