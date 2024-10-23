#pragma once
#define MAX_TURN 80

/* �N���X�̂ЂȌ^		*/
typedef struct
{
	void (*TurnPlus)(void);
	int (*GetTurn)(void);
	int (*GetSetTurn)(void);
	int (*GetTurnRemains)(void);
}TurnManager;

/* �R���X�g���N�^		*/
static TurnManager* TurnManagerConstructor(void);