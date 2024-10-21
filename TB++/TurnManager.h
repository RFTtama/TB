#pragma once
#define G1 700
#define G2 90
#define G3 250
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