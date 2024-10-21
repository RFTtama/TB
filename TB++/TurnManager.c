#include "TurnManager.h"

/* 変数関連							*/
static int turn		= 0;
static int setTurn	= 0;

/* ターン経過処理					*/
static void TurnPlus(void)
{
	if (turn < 0xefffffff) 
	{
		turn++;
	}
}

/* 現在のターン数取得				*/
static int GetTurn(void)
{
	return turn;
}

/* セットのターンを取得する			*/
static int GetSetTurn(void)
{
	return setTurn;
}

/* セットまでの残りターンを取得する	*/
static int GetTurnRemains(void)
{
	return (setTurn - turn);
}

/* インスタンス						*/
static TurnManager TM =
{
	TurnPlus,
	GetTurn,
	GetSetTurn,
	GetTurnRemains
};

/* ターンマネージャのコンストラクタ	*/
static TurnManager* TurnManagerConstructor(void) 
{
	return &TM;
}