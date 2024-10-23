#include "EnemyDefine.h"

/* �v���g�^�C�v�錾			*/
static int GetEnemyId(void);
static void SetEnemyId(int);
static void GetEnemyName(int, EnemyInfo*);

/* �ϐ��֘A					*/
static int enemyId = 0;

static char entityname[3][11][ENAMES] = 
{ 
"�]���r", "����", "�S�[�X�g", "���؎�", "�L���̖͕�", "����", "�א_", "�א_�U", "���񂾋L��", "�m�F�s�\", "�ł̗�",/*stage 0*/
"�t���[�g", "�i��", "�����̇T","���̐��̎g��", "�A���W�I���W�[", "�{�C�h","�t�B�j�[�g" ,"�G��", "���񂾋L��", "�m�F�s�\", "�ł̗�",/*stage 1*/
"�U��̊�]", "", "", "", "", "", "", "", "���񂾋L��", "�m�F�s�\", "�ł̗�",/*stage 2*/
};

/* �G�L������ID���擾����	*/
static int GetEnemyId(void)
{
	return enemyId;
}

/* �G�L������ID��ݒ肷��	*/
static void SetEnemyId(int id)
{
	enemyId = id;
}

/* �G�L�����̖��O��ݒ肷��	*/
static void GetEnemyName(int stage, EnemyInfo* info)
{
	int i;
	for (i = 0; entityname[stage][enemyId][i] != '\0'; i++) {
		info->EnemyName[i] = entityname[stage][enemyId][i];
	}
	info->EnemyName[i] = '\0';
}

/* �C���X�^���X				*/
static EnemyDefine ED =
{
	GetEnemyId,
	SetEnemyId,
	GetEnemyName
};

/* �R���X�g���N�^			*/
static EnemyDefine* EnemyDefineConstructor(void)
{
	return &ED;
}