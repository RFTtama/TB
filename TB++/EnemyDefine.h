#pragma once
#define ENAMES 25

/* �N���X�̂ЂȌ^		*/
typedef struct
{
	int (*GetEnemyId)(void);
	void (*SetEnemyId)(int);
	void (*SetEnemyName)(int, char[ENAMES]);
}EnemyDefine;

/* �G���ۑ��p�\����	*/
typedef struct
{
	char EnemyName[ENAMES];
}EnemyInfo;

/* �R���X�g���N�^		*/
static EnemyDefine* EnemyDefineConstructor(void);