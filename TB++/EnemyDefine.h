#pragma once
#define ENAMES 25

/* �N���X�̂ЂȌ^	*/
typedef struct
{
	int (*GetEnemyId)(void);
	void (*SetEnemyId)(int);
	void (*SetEnemyName)(int, char[ENAMES]);
}EnemyDefine;

/* �R���X�g���N�^	*/
static EnemyDefine* EnemyDefineConstructor(void);