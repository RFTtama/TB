#pragma once
#define MAX_TURN 80

/* クラスのひな型		*/
typedef struct
{
	void (*TurnPlus)(void);
	int (*GetTurn)(void);
	int (*GetSetTurn)(void);
	int (*GetTurnRemains)(void);
}TurnManager;

/* コンストラクタ		*/
static TurnManager* TurnManagerConstructor(void);