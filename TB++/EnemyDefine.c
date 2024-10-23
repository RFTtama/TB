#include "EnemyDefine.h"

/* プロトタイプ宣言			*/
static int GetEnemyId(void);
static void SetEnemyId(int);
static void GetEnemyName(int, EnemyInfo*);

/* 変数関連					*/
static int enemyId = 0;

static char entityname[3][11][ENAMES] = 
{ 
"ゾンビ", "狂犬", "ゴースト", "裏切者", "記憶の模倣", "悪夢", "邪神", "邪神Ⅱ", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 0*/
"フロート", "ナル", "実験体Ⅰ","あの世の使者", "アルジオロジー", "ボイド","フィニート" ,"エル", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 1*/
"偽りの希望", "", "", "", "", "", "", "", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 2*/
};

/* 敵キャラのIDを取得する	*/
static int GetEnemyId(void)
{
	return enemyId;
}

/* 敵キャラのIDを設定する	*/
static void SetEnemyId(int id)
{
	enemyId = id;
}

/* 敵キャラの名前を設定する	*/
static void GetEnemyName(int stage, EnemyInfo* info)
{
	int i;
	for (i = 0; entityname[stage][enemyId][i] != '\0'; i++) {
		info->EnemyName[i] = entityname[stage][enemyId][i];
	}
	info->EnemyName[i] = '\0';
}

/* インスタンス				*/
static EnemyDefine ED =
{
	GetEnemyId,
	SetEnemyId,
	GetEnemyName
};

/* コンストラクタ			*/
static EnemyDefine* EnemyDefineConstructor(void)
{
	return &ED;
}