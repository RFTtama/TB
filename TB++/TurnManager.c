#include "TurnManager.h"

/* �v���g�^�C�v�錾					*/
static void TurnPlus(void);
static int GetTurn(void);
static int GetSetTurn(void);
static int GetTurnRemains(void);

/* �ϐ��֘A							*/
static int turn		= 0;
static int setTurn	= 0;

/* �^�[���o�ߏ���					*/
static void TurnPlus(void)
{
	if (turn < 0xefffffff) 
	{
		turn++;
	}
}

/* ���݂̃^�[�����擾				*/
static int GetTurn(void)
{
	return turn;
}

/* �Z�b�g�̃^�[�����擾����			*/
static int GetSetTurn(void)
{
	return setTurn;
}

/* �Z�b�g�܂ł̎c��^�[�����擾����	*/
static int GetTurnRemains(void)
{
	return (setTurn - turn);
}

/* �C���X�^���X						*/
static TurnManager TM =
{
	TurnPlus,
	GetTurn,
	GetSetTurn,
	GetTurnRemains
};

/* �^�[���}�l�[�W���̃R���X�g���N�^	*/
static TurnManager* TurnManagerConstructor(void) 
{
	return &TM;
}