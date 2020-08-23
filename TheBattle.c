/* include files */
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"MT.h"
/*マクロ*/
#define read 0
#define write 1
#define allitem 11
#define lose 1
#define win 2
#define draw 3
#define savepatt name, lv, xp, battled, fpo, item, stage, data1[Mskill], ac, skpt \
, logAI[0][0], logAI[0][1], logAI[0][2], logAI[0][3] \
, logAI[1][0], logAI[1][1], logAI[1][2], logAI[1][3] \
, logAI[2][0], logAI[2][1], logAI[2][2], logAI[2][3] \
, logAI[3][0], logAI[3][1], logAI[3][2], logAI[3][3] \
, rate, master, unlike, master2
#define boost1 if (data1[Mdamageboost] == 1) data1[MAT] += 5;
#define boost2 if (data2[Edamageboost] == 1) data2[EAT] += 5;
#define heal1 if(turn <= healcnt){dmg[0] += ((int)((data1[MAT] * healp[0]) / 100) * -1);}
#define heal2 dmg[1] += ((int)((data2[EAT] * healp[1]) / 100) * -1);
#define shield1 if (data1[Mshield] == 1) data1[Mshieldnum] += 9, sheal[0]++;
#define shield2 if (data2[Eshield] == 1) data2[Eshieldnum] += 9, sheal[1]++;
#define atk1 dmg[1] += dmgd(hmax1, data1[MHP], data1[MAT]);
#define atk2 dmg[0] += dmgd(hmax2, data2[EHP], data2[EAT]);
#define spatk1 dmg[1] += dmgd(hmax1, data1[MHP], (int)(data1[MAT] * 1.25));
#define spatk2 dmg[0] += dmgd(hmax2, data2[EHP], (int)(data2[EAT] * 1.25));
#define atkE dmg[0] += dmgd(hmax2, data2[EHP], force);
#define spatkE dmg[0] += dmgd(hmax2, data2[EHP], (int)(force * 1.25));
#define pt if((dmg[1] > 0)/* && (end == 0)*/){totalpo += dmg[1];}
#define ref1 dmg[0] += dmgd(hmax1, data1[MHP], (int)(data1[MAT] * 1.25));
#define ref2 dmg[1] += dmgd(hmax2, data2[EHP], (int)(data2[EAT] * 1.25));
#define refE dmg[1] += dmgd(hmax2, data2[EHP], (int)(force * 1.25));
#define rptm data.s3 -= 10;
#define rptp data.s3 += 50;
#define ent if (EA == 8)data2[Etier]++;
#define enttier if(data2[Etier] > 5)data2[Etier] = 5;
#define cMaxn 0
#define cnown 1
#define FS0 if(SG[0][0] == SG[0][1]){fs[0]++, SG[0][1] = 0;}
#define FS1 if(SG[1][0] == SG[1][1]){fs[1]++, SG[1][1] = 0;}
#define painin if(data2[Eskill] == 10)slowpain = 2;
#define espain if(slowpain > 0)slowpain = 0;
#define du1 dmgp[0]++;
#define du2 dmgp[1]++;
/* ポイント */
#define c1 if(cMax[0][cnown] < cMax[0][cMaxn]){Evad[2] += 1; cMax[0][cnown]++; printf("<攻撃> +1pts\n");}
#define c2 if(cMax[1][cnown] < cMax[1][cMaxn]){Evad[2] += 2; cMax[1][cnown]++; printf("<命中> +2pts\n");}
#define c3 if(cMax[2][cnown] < cMax[2][cMaxn]){Evad[2] += 3; cMax[2][cnown]++; printf("<回避> +3pts\n");}
#define c4 if(cMax[3][cnown] < cMax[3][cMaxn]){Evad[2] += 5; cMax[3][cnown]++; printf("<反射> +5pts\n");}
#define c5 if(cMax[4][cnown] < cMax[4][cMaxn]){Evad[2] += 6; cMax[4][cnown]++; printf("<急所> +6pts\n");}
#define c6 if(cMax[5][cnown] < cMax[5][cMaxn]){Evad[2] += 2; cMax[5][cnown]++; printf("<耐久> +2pts\n");}//HPmax
#define c7 if(cMax[6][cnown] < cMax[6][cMaxn]){Evad[2] += 2; cMax[6][cnown]++; printf("<耐久> +2pts\n");}//lowHP
#define c8 if(cMax[7][cnown] < cMax[7][cMaxn]){Evad[2] += 10; cMax[7][cnown]++; printf("<勝利> +10pts\n");}
#define c9 if(cMax[8][cnown] < cMax[8][cMaxn]){Evad[2] += 1; cMax[8][cnown]++; printf("<耐久> +1pts\n");}//turn
#define c10 if(cMax[9][cnown] < cMax[9][cMaxn]){Evad[2] += 5; cMax[9][cnown]++; printf("<激怒> +5pts\n");}
#define c11 if(cMax[10][cnown] < cMax[10][cMaxn]){Evad[2] += 5; cMax[10][cnown]++; printf("<発動> +5pts\n");}//skill
#define c12 if(cMax[11][cnown] < cMax[11][cMaxn]){Evad[2] += 7; cMax[11][cnown]++; printf("<遮断> +7pts\n");}
#define c13 if(cMax[12][cnown] < cMax[12][cMaxn]){Evad[2] += 2; cMax[12][cnown]++; printf("<支配> +2pts\n");}
//#define c14 if(cMax[13][cnown] < cMax[13][cMaxn]){Evad[2] += 2; cMax[13][cnown]++; printf("<信頼> +2pts\n");}
#define c15 if(cMax[14][cnown] < cMax[14][cMaxn]){Evad[2] += 10; cMax[14][cnown]++; printf("<終了> +10pts\n");}
#define c16 if((cMax[15][cnown] < cMax[15][cMaxn]) && (50 - turn > 0)){Evad[2] += 70 - turn; cMax[15][cnown]++; printf("<高速> +%dpts\n", 70 - turn);}
#define c17 if(cMax[16][cnown] < cMax[16][cMaxn]){Evad[2] += 2; cMax[16][cnown]++; printf("<100超> +3pts\n");}
#define c18 if(cMax[17][cnown] < cMax[17][cMaxn]){Evad[2] += 4; cMax[17][cnown]++; printf("<200超> +5pts\n");}
/*************/
#define MHP 0
#define MAT 1
#define MLV 2
#define Mxp 3
#define Mreborn 4
#define Mdamageboost 5
#define Mshield 6
#define Mshieldnum 7
#define Mmode 8
#define Mskill 9
#define Mskc 10
#define Mill 11
#define EHP 0
#define EAT 1
#define Edamageboost 2
#define Eshield 3
#define Eshieldnum 4
#define Etier 5
#define Eskill 6
#define Ecnt 7
#define setturn 80
#define savet "TheBattle  %s %d %d %d %ld %lld %d %d %d %d %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %d %ud %d %ud"
#define fc_black system("color 0");
#define fc_blue system("color 1");
#define fc_green system("color 2");
#define fc_cyan system("color 3");
#define fc_red system("color 4");
#define fc_magenda system("color 5");
#define fc_yellow system("color 6");
#define fc_lcyan system("color B");
#define fc_lred system("color C");
#define fc_lyellow system("color E");
#define fc_def system("color 7");
//#define release

/* グローバル宣言 */
int data1[12];//自身データ 0:HP 1:AT 2:LV 3:xp 4:復活薬　5:ダメージブースト 6:シールド有無 7:シールド値 8:モード 9:スキル 10:スキルカウンタ 11:疫病
int data2[8];//敵データ 0:HP 1:AT 2:ダメージブースト 3:シールド有無 4:シールド値 5:邪神のティア 6:スキル 7:カウンタ
/* スキル 0:無し 1:ダメージインクリーズ 2:チャージ 3:分裂 4:デスカウント 5:衰弱の咳 6:吐血症の咳 7:壊死症の咳 8:疫病の咳 9:ユニット 10:ペイン */
unsigned int fpo = 0;
__int64 item = 0;
int itemn[18];
int battled;
unsigned int totalpo = 0;
char name[256];
int stage = 0;
int skpt = 0;
int ac = 0;
struct sample { float s0; int s1; int s2; int s3; };
struct tm tm;
time_t t = 0;
int turn = 0;
__int64 logAI[4][4];
short int ak = 0;
unsigned int kp[4];
int rate = 0;
unsigned int master = 0;
unsigned int master2 = 0;
int unlike = 0;
int unit[4][2] = { 250, 0, 150, 0, 300, 0, 400, 0 };
unsigned char SG[2][2] = { 0, 0, 0, 0 };
int spsc;
/******************/
FILE* LV;
FILE* BAK;
/******************/
/* プロトタイプ宣言 */
char menu(void);
int shop(int, int);
void startwait(void);
int randnum(int);
void timer(int);
void data_check(void);
void rank(void);
void saved(int, int);
void itemc(int);
int dmgd(int, int, int);

void sk2(int*);
void randchar(int);
void AI(short int, short int);
void initAI(short int, short int);
short int AIpat(short int, short int);
void AIsave(short int, short int);
void liker(void);
void connum(int*);
/********************/
int main(void)
{
	/* 変数の宣言 */
	int a, b, c, d[24];
	int k1 = 10;//koudou 1
	int k2 = 10;//koudou 2
	int ak1 = 10;//after koudou 1
	int ak2 = 10;//after koudou 2
	int hmax1 = 0;//hp max 1
	int hmax2 = 0;//hp max 2
	unsigned char nsp = 0;//not escape
	short int sp = 0;//escape
	short int sp2 = 50;//escape 2
	int xp_flg;
	char* entityname[4][11] = { "スケルトン", "ゾンビ", "ゴースト", "駆逐型ロボット", "ドラゴン", "邪悪の化身", "邪神", "邪神Ⅱ", "邪神Ⅲ", "黒い仔山羊", "闇の猟犬",/*stage 0*/
		"フィート", "ナル", "ベヒモス","あの世の使者", "アルジオロジー", "ボイド", "フィニート", "フィニッシュ・フィニート", "邪神Ⅲ", "黒い仔山羊", "闇の猟犬",/*stage 1*/
		"シュブニグラス", "", "", "", "", "", "", "", "邪神Ⅲ", "黒い仔山羊", "闇の猟犬",/*stage 2*/
		"seed00", "" };
	unsigned char EA = 0;
	unsigned char change = 0;
	int dmg[2] = { 0, 0 };//damage
	int save = 0;
	unsigned char tier = 0;
	int ent3 = 0;
	char* flavor[] = { "奇妙な石", "アルジオロジーの血", "期限の切れた薬品", "邪悪なる宝石", "復活薬",
		"回復薬","琥珀のかけら","救急キット","お医者さんキット","聖なるお祈り" };
	int force = 0;
	float hpercent[2][2] = { 0, 0, 0, 0 };
	struct sample data = { 0, 0, 0, 1000 };
	float Evad[3] = { 0.0, 0.0, 0.0 };
	int healcnt = setturn;//回復可能ターン数
	char dark = 0;
	unsigned char tag = 0;
	unsigned char arge = 34;
	unsigned char swAI = 1;
	unsigned char bond = 0;
	const unsigned char Eparge[] = { 50, 50, 100, 100, 100, 100, 100, 100 };
	unsigned int pen = 0;
	float per = 0;
	int E1 = 1500;
	int E2 = 60;
	int E3 = 190;
	char spsk1 = 0;
	float dmgcntr = 0;
	unsigned char deadflag = 0;
	unsigned char Mres[3] = { 1, 0, 1 };
	short int dmgp[2] = { 100, 100 };//damage percentage
	short int crit[2] = { 150, 150 };//critical
	short int healp[2] = { 50, 50 };// heal percentage
	int rageHP[2][2] = { 0, 0, 0, 0 };
	unsigned char rageflg[2] = { 0, 0 };
	unsigned char cMax[18][2] = { 20, 0, 15, 0, 15, 0, 10, 0, 3, 0, 35, 0, 10, 0, 1, 0, 50, 0, 1, 0, 10, 0, 10, 0, 10, 0, 20, 0, 1, 0, 1, 0, 10, 0, 5, 0 };
	unsigned char fs[2] = { 0, 0 };//forced strike
	unsigned char sheal[2] = { 0, 0 };//shield heal
	unsigned char nofi = 0;//number of item
	int pain = 0;
	unsigned char slowpain = 0;
	short int spdp = 0;
//	unsigned char end = 0;
	unsigned char set_flg = 0;
	unsigned char wildmode[2] = { 0, 0 };
	char wl = 0;
	/**************/
	/* ファイルポインタ */
	FILE* SF;
	/********************/
	for (a = 0; a <= 11; a++) {//初期化
		data1[a] = 0;
		if (a <= 7) {
			data2[a] = 0;
		}
	}
	for (a = 0; a < 4; a++) {
		for (b = 0; b < 4; b++) {
			if (b == 0)logAI[a][0] = 0x0001000100010000;
			if (b == 1)logAI[a][1] = 0x0001000100000001;
			if (b == 2)logAI[a][2] = 0x0001000000010001;
			if (b == 3)logAI[a][3] = 0x0000000100010001;
		}
	}
	for (a = 0; a < 18; a++) {
		itemn[a] = 0;
	}
	rate = 20;
	unlike = 90;
	data_check();
	fopen_s(&LV, "LV.tb", "r");
	fseek(LV, 11L, SEEK_SET);
	fgets(name, 7, LV);
	fscanf_s(LV, "%d%d%d%ld%lld%d%d%d%d",
		&data1[MLV], &data1[Mxp], &battled, &fpo, &item, &stage, &data1[Mskill], &ac, &skpt);
	for (a = 0; a < 4; a++) {
		for (b = 0; b < 4; b++) {
			fscanf_s(LV, "%lld", &logAI[a][b]);
		}
	}
	fscanf_s(LV, "%d%ud%d%ud", &rate, &master, &unlike, &master2);
	fclose(LV);
	if (unlike > 120) {
		remove("LV.tb");
		remove("backup.tb");
		printf("\n過度の切断が確認されたためデータを削除します。\n");
		startwait();
		exit(1);
	}
	if (stage <= 1) {
		printf("_/_/The Battle 第1期_/_/\n");
	}
	else if (stage == 2) {
		printf("_/_/The Battle 第2期_/_/\n");
	}
	else if (stage == 3) {
		printf("_/_/The Battle 第3期_/_/\n");
	}
	if (data1[Mskill] != 0) {
		printf("別のスキルを習得しますか?(マスターしていないスキルの途中経過は削除されます)\n");
		printf("Yes:10 No:else\n");
		connum(&a);
	}
	else {
		a = 10;
	}
	if (a == 10) {
		data1[Mskill] = 0;
		ac = 0;
		skpt = 0;
		saved(data1[MLV], data1[Mxp]);
	}
	printf("スキルツリー\n");
	printf("　★\n　｜\n");
	if ((master & 0x04) == 0x04) {
		printf("●");
	}
	else {
		printf("〇");
	}
	if ((master & 0x02) == 0x02) {
		printf("●");
	}
	else {
		printf("〇");
	}
	if ((master & 0x01) == 0x01) {
		printf("●\n");
	}
	else {
		printf("〇\n");
	}
	if (rate <= 0)swAI = 0;
	if (data1[Mskill] == 0) {
		printf("キャラクターの属性スキルを選択してください。\n\n");
		printf("1:\"竜族\" 火炎放射を選択した場合効果が発動する。\n");
		printf("効果: 相手に\"すこし\"のダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。\n\n");
		printf("2:\"魔族\" 特殊攻撃を行った際に効果が発動する。\n");
		printf("効果: 当たった相手に大ダメージを与えるスキルを発動する。命中率はスキル発動に失敗する度に\"1%%\"上昇する。\nこの能力発動時に命中率はリセットされる。\n\n");
		printf("3:\"機械族\" 5回攻撃行動を行った場合に効果が発動する。\n");
		printf("効果: 相手のストライクゲージを1減少させる。\n\n");
		a = 0;
		do {
			connum(&data1[Mskill]);
			switch (data1[Mskill]) {
			case 1:
				printf("\aあなたは\"竜族\"を選択しました。\n");
				if ((master & 0x01) == 0x01) {
					ac = 4;
					skpt = 10000;
				}
				a = 1;
				break;
			case 2:
				printf("\aあなたは\"魔族\"を選択しました。\n");
				if ((master & 0x02) == 0x02) {
					ac = 4;
					skpt = 10000;
				}
				a = 1;
				break;
			case 3:
				printf("\aあなたは\"機械族\"を選択しました。\n");
				if ((master & 0x04) == 0x04) {
					ac = 4;
					skpt = 10000;
				}
				a = 1;
				break;
			}
		} while (!a);
		saved(data1[MLV], data1[Mxp]);
	}
	itemc(read);
	printf("\n");
	if (stage == 3) {
		randchar(24);
		timer(100);
		change = 1;
		ent3 = 20;//5.00%
	}
	else if (battled < 1) {
		printf("*低ランク*\n");
		change = 2;
		ent3 = 100;//1.00%
	}
	else if (battled < 2) {
		printf("*高ランク*\n");
		change = 3;
		ent3 = 90;//1.11%
	}
	else if (battled < 3) {
		printf("*ブロンズランク*\n");
		change = 4;
		ent3 = 80;//1.25%
	}
	else if (battled < 4) {
		printf("*シルバーランク*\n");
		change = 5;
		ent3 = 70;//1.43%
	}
	else if (battled < 5) {
		printf("*ゴールドランク*\n");
		change = 6;
		ent3 = 60;//1.67%
	}
	else if ((battled < 6) || (stage == 2)) {
		printf("**ダイヤモンドランク**\n");
		change = 7;
		ent3 = 50;//2.00%
	}
	else {
		printf("***タンザナイトランク***\n");
		change = 8;
		ent3 = 40;//2.50%
	}
	printf("\nレベル:%d\n\n", data1[MLV]);
	timer(300);
	data2[Eshieldnum] = 0;
	switch (menu()) {
	case 1:
		break;

	case 2:
		shop(data1[MLV], data1[Mxp]);
		fopen_s(&LV, "LV.tb", "r");
		fseek(LV, 17L, SEEK_SET);
		fscanf_s(LV, "%d%d%d%d%lld%d%d%d%d",
			&data1[MLV], &data1[Mxp], &battled, &fpo, &item, &stage, &data1[Mskill], &ac, &skpt);
		fclose(LV);
		break;

	default:
		break;
	}
	data1[Mdamageboost] = 1, printf("ダメージブースト付与\n");
	data1[Mshield] = 1, printf("シールドブースト付与\n");
	data1[MHP] = 1000;
	data1[MAT] = 50 + data1[MLV] - 1;
	sp = 50;
	if (item > 0) {
		printf("アイテムを使用しますか? Yes=1\n");
		connum(&a);
		if (a == 1) {
			printf("どのアイテムを使用しますか?\n");
			for (a = 0; a < 10; a++) {
				if (itemn[a] > 0) {
					printf("%d:%s 個数:%x\n", a, flavor[a], itemn[a]);
				}
			}
			a = 0;
			connum(&a);
			printf("\n");
			timer(100);
			switch (a) {
			case 0:
				if (itemn[0] >= 1) {
					data1[Mreborn] = 2;
					itemn[0]--;
					nofi = 1;
					printf("ダメージ倍率10%%減少&2回復活可能!!\n");
				}
				break;
			case 1:
				if (itemn[1] - 1 >= 0) {
					itemn[1]--;
					nofi = 2;
					printf("取得経験値及びポイント100%%増加!!\n");
				}
				break;
			case 2:
				if (itemn[2] - 1 >= 0) {
					itemn[2]--;
					nofi = 3;
					printf("回復率20%%増加!!\n");
				}
				break;
			case 3:
				if (itemn[3] - 1 >= 0) {
					ent3 = 3;
					itemn[3]--;
					nofi = 4;
					printf("邪神Ⅲ出現確率上昇!!\n");
				}
				break;
			case 4:
				if (itemn[4] - 1 >= 0) {
					data1[Mreborn] = 1;
					itemn[4]--;
					nofi = 5;
					printf("体力が0以下になったときに1回復活!!\n");
				}
				break;
			case 5:
				if (itemn[5] - 1 >= 0) {
					data1[Mreborn] = 1;
					itemn[5]--;
					nofi = 6;
					printf("体力が50%%以下になったときに1回回復!!\n");
				}
				break;
			case 6:
				if (itemn[6] - 1 >= 0) {
					if (itemn[6] < 3) {
						printf("琥珀の数が足りません 3/%d\n", itemn[6]);
					}
					else {
						data1[Mmode] = 1;
						itemn[6] = itemn[6] - 3;
						nofi = 7;
						printf("自然の力を手にした!!\n");
					}
				}
				break;
			case 7:
				if (itemn[7] - 1 >= 0) {
					itemn[7] = itemn[7] - 1;
					nofi = 8;
					printf("HPが20%%以下の時最大HP固定!!\n");
				}
				break;
			case 8:
				if (itemn[8] - 1 >= 0) {
					itemn[8] = itemn[8] - 1;
					nofi = 9;
					printf("HPが10%%増加!!\n");
				}
				break;
			case 9:
				if (itemn[9] - 1 >= 0) {
					printf("天に向かって祈りを捧げた…\n");
					timer(700);
					if (randnum(4) == 0) {
						data1[Mreborn] = data1[Mreborn] + 1;
						printf("天は優しく微笑んだ。\n");
					}
					else {
						printf("天は邪悪な笑みを浮かべた…\n");
						dark = 1;
						nofi = 10;
					}
					timer(500);
				}
				itemn[9] = itemn[9] - 1;
				break;
			default:
				printf("無いアイテムをどうやって使うって言うんだ?\n");
				break;
			}
		}
	}
	itemc(write);
	saved(data1[MLV], data1[Mxp]);
	if (stage == 2)tag = 1;
	if (stage == 3)tag = 2;
	switch (data1[Mskill]) {
	case 1:
		spsk1 = 1;
		printf("\"竜族\" 火炎放射を選択した場合効果が発動する。\n");
		switch (ac) {
		case 0:
			printf("相手に\"すこし\"ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。\n");
			break;
		case 1:
			printf("相手に\"まぁまぁ\"ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。。\n");
			break;
		case 2:
			printf("相手に\"ふつうの\"ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。。\n");
			break;
		case 3:
			printf("相手に\"かなり\"ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。。\n");
			break;
		case 4:
			printf("相手に\"とてつもない\"ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃の行動をとる度に威力が上昇する。。\n");
			break;
		}
		SG[0][0] = 10;
		break;
	case 2:
		printf("\"魔族\" 特殊攻撃を行った際に効果が発動する。\n");
		printf("当たった相手に大ダメージを与えるスキルを発動する。命中率はスキル発動に失敗する度に\"%d%%\"上昇する。\nこの能力発動時に命中率はリセットされる。\n", ac + 1);
		SG[0][0] = 10;
		break;
	case 3:
		printf("\"機械族\" 5回攻撃行動を行った場合に効果が発動する。\n");
		printf("相手のストライクゲージを%d減少させる。\n", ac + 1);
		SG[0][0] = 10;
		break;
	default:
		break;
	};
	liker();

	if (data1[Mmode] == 1) {
		data1[Mshield] = 0;
		data1[Mshieldnum] = 10000;
	}
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	printf("%sのプロフィール\n", name);
	printf("HP:%d  AT:%d  LV:%d\n", data1[MHP], data1[MAT], data1[MLV]);
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	startwait();
	printf("\r");
	t = time(NULL);
	localtime_s(&tm, &t);
	if ((dark == 1) && (randnum(4) == 0)) {
		printf("\a");
		randchar(12);
		printf("\n");
		data2[EHP] = 10;
		data2[EAT] = 1;
		force = 100;
		data2[Eshieldnum] = 2500;
		data2[Eshield] = 1;
		rageHP[1][0] = data2[Eshieldnum];
		EA = 9;
		crit[0] += 849;
		SG[1][0] = 4;
	}
	else if ((randnum(20) == 0) && ((tm.tm_hour >= 21) && (tm.tm_hour <= 4))) {
		randchar(12);
		printf("\a\n");
		data2[EHP] = 2000;
		data2[EAT] = 60;
		data2[Eshield] = 1;
		rageHP[1][0] = 2000;
		data2[Eskill] = 10;
		EA = 10;
		SG[1][0] = 4;
	}
	else if (randnum(ent3) == 0) {//邪神Ⅲ
		printf("\a_/_/BOSS_/_/\n");
		data2[EHP] = 1;
		data2[EAT] = 1;
		data2[Eshieldnum] = 10000;
		rageHP[1][0] = 3000;
		EA = 8;
		crit[0] += 150;
		SG[1][0] = 16;
	}
	else {
		for (a = 0, b = 0; a < change; a++) {
			b = b + Eparge[a];
		}
		c = randnum(b);
		a = 0;
		b = 0;
		while (1) {
			b = b + Eparge[a];
			if (c < b) {
				change = a;
				break;
			}
			a++;
		}
		switch (stage) {
		case 0:
		case 1:
			switch (change) {
			case 0://スケルトン
				data2[EHP] = 1100;
				data2[EAT] = 70;
				EA = 0;
				SG[1][0] = 11;
				break;

			case 1://ゾンビ
				data2[EHP] = 900;
				data2[EAT] = 80;
				EA = 1;
				SG[1][0] = 13;
				break;

			case 2://ゴースト
				data2[EHP] = data1[MHP] + 800;
				data2[EAT] = 50 + (data1[MAT] / 2);
				data2[Eshield] = 1;
				data2[Eshieldnum] = 500;
				rageHP[1][0] = data2[EHP] + data2[Eshieldnum];
				EA = 2;
				SG[1][0] = 12;
				break;

			case 3://駆逐型ロボット
				data2[EHP] = 2400;
				data2[EAT] = 40;
				data2[Edamageboost] = 1;
				EA = 3;
				SG[1][0] = 11;
				break;

			case 4://ドラゴン
				data2[EHP] = 1500;
				data2[EAT] = 70;
				data2[Eshield] = 1;
				data2[Eshieldnum] = 700;
				EA = 4;
				SG[1][0] = 12;
				break;

			case 5://邪悪の化身
				data2[EHP] = 1800;
				data2[EAT] = 80;
				data2[Edamageboost] = 1;
				data2[Eshield] = 1;
				data2[Eshieldnum] = 500;
				force = 100;
				EA = 5;
				SG[1][0] = 12;
				break;

			case 6://邪神
				printf("\a_/_/Boss_/_/\n");
				data2[EHP] = 2000;
				data2[EAT] = 100;
				data2[Eshield] = 1;
				force = 180;
				EA = 6;
				SG[1][0] = 10;
				break;

			case 7://邪神Ⅱ
				printf("\a_/_/Boss_/_/\n");
				data2[EHP] = data1[MHP] * 5;
				data2[EAT] = 20;
				data2[Edamageboost] = 1;
				data2[Eshieldnum] = (int)(data1[MHP] * 2.5);
				EA = 7;
				SG[1][0] = 6;
				break;
			}
			break;
		case 2:
			switch (randnum(change)) {
			case 0://フィート
				data2[EHP] = data1[MHP];
				data2[EAT] = data1[MAT];
				data2[Eshieldnum] = data1[MHP];
				rageHP[1][0] = data1[MHP] * 2;
				EA = 0;
				SG[1][0] = 12;
				break;
			case 1://ナル
				data2[EHP] = 2100;
				data2[EAT] = 80;
				data2[Eskill] = 2;//チャージ
				sp2 = 100;
				EA = 1;
				SG[1][0] = 9;
				break;
			case 2://ベヒモス
				data2[EHP] = 5000;
				data2[EAT] = 0;
				data2[Edamageboost] = 1;
				data2[Eskill] = 1;
				EA = 2;
				SG[1][0] = 15;
				break;
			case 3://あの世の使者
				data2[EHP] = 1800;
				data2[EAT] = 80;
				data2[Eshield] = 1;
				data2[Eshieldnum] = 1000;
				data2[Eskill] = 3;
				EA = 3;
				SG[1][0] = 13;
				break;
			case 4://アルジオロジー
				data2[EHP] = 2300;
				data2[EAT] = 60;
				data2[Eshield] = 1;
				data2[Eskill] = 8;
				EA = 4;
				SG[1][0] = 16;
				break;
			case 5://ボイド
				data2[EHP] = 2500;
				data2[EAT] = 20;
				data2[Eshield] = 1;
				data2[Eshieldnum] = 1200;
				data2[Eskill] = 4;
				EA = 5;
				SG[1][0] = 20;
				break;
			case 6://フィニート
				printf("\a_/_/Boss_/_/\n");
				data2[EHP] = 2200;
				data2[EAT] = 100;
				data2[Eshield] = 1;
				data2[Eskill] = 2;
				EA = 6;
				SG[1][0] = 17;
				break;
			case 7://フィニッシュ・フィニート
				printf("\a_/_/Boss_/_/\n");
				data2[EHP] = 3500;
				data2[EAT] = 10;
				data2[Edamageboost] = 1;
				data2[Eshield] = 1;
				data2[Eskill] = 8;
				EA = 7;
				SG[1][0] = 20;
				break;
			}
			break;

		case 3://シュブニグラス
			printf("\a");
			randchar(12);
			printf("\n");
			data2[EHP] = 20000;
			data2[EAT] = 0;
			data2[Eshieldnum] = 10000;
			data2[Edamageboost] = 1;
			data2[Eskill] = 9;
			printf("ダメージブースト無効!!\n");
			data1[Mdamageboost] = 0;
			EA = 0;
			SG[1][0] = 20;
			break;
		}
	}

	timer(100);
	printf("敵データ Name:%s HP:%d  AT:%d\n", entityname[tag][EA], data2[EHP], data2[EAT]);
#ifdef release
	unlike = unlike + 15;
#endif
	saved(data1[MLV], data1[Mxp]);//途中セーブ
#ifdef release
	unlike = unlike - 15;
#endif
	timer(400);
	printf("対戦を始めます\n");
	startwait();
	for (a = 0; a < 24; a++) {
		d[a] = 0;
	}
	switch (data1[Mskill]) {

	default:
		break;
	}
	/*アイテム処理*/
	if (nofi == 1)d[10] = d[10] - 10;
	if (nofi == 3)d[6] = d[6] + 20;
	if (nofi == 9)d[8] = d[8] + 10;
	//d[] 12:自攻 13:敵攻 14:自sp 15:敵sp 16:自怯 17:敵怯 18:自回 19:敵回 20:自HP 21:敵HP 22:自ダ倍 23:敵ダ倍
	if (stage <= 1 && EA == 7) {
		d[19] = -100;
		d[17] = -25;
	}
	for (a = 0; a < 12; a++) {
		d[a] = d[a] + d[a + 12];
	}
	data1[MAT] = data1[MAT] + d[0];//d[] 0:自攻 1:敵攻 2:自sp 3:敵sp 4:自怯 5:敵怯 6:自回 7:敵回 8:自HP 9:敵HP 10:自ダ倍 11:敵ダ倍
	if (data1[MAT] < 1)data1[MAT] = 1;
	data2[EAT] = data2[EAT] + d[1];
	if (data2[EAT] < 1)data2[EAT] = 1;
	sp = sp + d[2];
	if (sp < 0)sp = 0;
	if (sp > 200)sp = 200;
	sp2 = sp2 + d[3];
	if (sp2 < 0)sp2 = 0;
	if (sp2 > 200)sp2 = 200;
	crit[0] = crit[0] + d[4];
	crit[1] = crit[1] + d[5];
	for (a = 0; a < 2; a++) {
		if (crit[a] < 101)crit[a] = 101;
	}
	healp[0] = healp[0] + d[6]; if (healp[0] < -500)healp[0] = -500;
	healp[1] = healp[1] + d[7]; if (healp[1] < -500)healp[1] = -500;
	data1[MHP] = data1[MHP] + ((int)(data1[MHP] * d[8]) / 100); if (data1[MHP] < 1)data1[MHP] = 1;
	data2[EHP] = data2[EHP] + ((int)(data2[EHP] * d[9]) / 100); if (data2[EHP] < 1)data2[EHP] = 1;
	dmgp[0] = dmgp[0] + d[10];
	dmgp[1] = dmgp[1] + d[11];
	for (a = 0; a < 2; a++) {
		if (dmgp[a] < 1)dmgp[a] = 1;
	}

	hmax1 = data1[MHP];
	hmax2 = data2[EHP];
	if (rageHP[0][0] <= 0) {
		rageHP[0][0] = hmax1;
	}
	if (rageHP[1][0] <= 0) {
		rageHP[1][0] = hmax2;
	}
	if (sp2 < 0) {
		sp2 = 0;
	}

	timer(700);
	while (1) {
		/*if (end == 1) {
			fc_lyellow;
		}
		else*/ if (data1[Mshieldnum] > 0) {
			fc_lcyan;
		}
		else if ((float)data1[MHP] / (float)hmax1 < 0.1) {
			fc_lred;
		}
		else if ((float)data1[MHP] / (float)hmax1 < 0.25) {
			fc_lyellow;
		}
		else {
			fc_def;
		}
		if (turn > 0) { c9; }
		/* 邪神Ⅲ処理 */
		if ((EA == 8) && (data2[Etier] != tier)) {
			if (data2[Etier] == 1) {//ティア2
				data2[EHP] = 2000;
				hmax2 = data2[EHP];
				data2[EAT] = 40;
				data2[Eshieldnum] = 1000;
				printf("\a邪神Ⅲは徐々に力を付けている…\n");
			}
			else if (data2[Etier] == 2) {//ティア3
				data2[Eshield] = 1;
				printf("\a邪神Ⅲにシールド再生能力が付与された\n");
			}
			else if (data2[Etier] == 3) {//ティア4
				data2[Edamageboost] = 1;
				printf("\a邪神Ⅲにダメージブーストが付与された\n");
			}
			else if (data2[Etier] == 4) {//ティア5
				hmax1 = data1[MHP];
				printf("\a回復能力が無効化された。\n");
				healcnt = turn;
			}
			tier = data2[Etier];
		}
		if ((data2[Etier] >= 5) && (EA == 8)) {
			data2[Etier] = 5;
			data2[EHP] = data2[EHP] + 10;
			if (data2[EHP] > hmax2) {
				data2[EHP] = hmax2;
			}
			if (data2[EHP] == hmax2) {
				force = data2[EAT] * 2;
				printf("邪神Ⅲはその身に絶大なパワーを宿している…\n");
			}
			else {
				force = 0;
			}
		}
		hpercent[0][0] = (float)data1[MHP] / hmax1;
		hpercent[1][0] = (float)data2[EHP] / hmax2;
		hpercent[0][1] = hpercent[0][0] * 10;
		hpercent[1][1] = hpercent[1][0] * 10;
		printf("\n");
//		if (end == 1)printf("<バグ発生>\n");
		printf("ターン:%d\n", turn);
		printf("_/_/_/_/_/%sのステータス HP:%d[%d](%.1lf%%) AT:%d", name, data1[MHP], data1[Mshieldnum], (double)hpercent[0][0] * 100, data1[MAT]);
		if (data1[Mdamageboost] == 1)printf(" [△]");
		if (data1[Mshield] == 1)printf(" [◇]");
		printf("_/_/_/_/_/");
		printf("\n_/_/_/_/_/%sのステータス HP:%d[%d](%.1lf%%) AT:%d", entityname[tag][EA], data2[EHP], data2[Eshieldnum], (double)hpercent[1][0] * 100, data2[EAT]);
		if (data2[Edamageboost] == 1)printf(" [△]");
		if (data2[Eshield] == 1)printf(" [◇]");
		if (EA == 8) {
			if (data2[Etier] >= 5) {
				printf(" Tier:5");
			}
			else {
				printf(" Tier:%d", data2[Etier] + 1);
			}
		}
		printf("_/_/_/_/_/\n\n");
		printf("\t%s\tSG:", name);
		for (a = 1; a <= 10; a++) {
			if ((((float)SG[0][1] / (float)SG[0][0]) * 100) >= (a * 10))printf("■");
			else printf("□");
		}
		printf("\n");
		printf("\t敵\tSG:");
		for (a = 1; a <= 10; a++) {
			if ((((float)SG[1][1] / (float)SG[1][0]) * 100) >= (a * 10))printf("■");
			else printf("□");
		}
		printf("\n");
		/*if (end == 0)*/printf("\t%sダメージ倍率:\t%d%%\t敵ダメージ倍率:\t%d%%\n", name, dmgp[0] + spdp, dmgp[1]);
		printf("\t      急所倍率:\t\t%d%%\t敵急所倍率:\t%d%%\n", crit[0], crit[1]);
		printf("\t      回避率:\t\t%d%%\t回避率:\t\t%d%%\n", sp, sp2);
		printf("\t      回復率:\t\t%d%%\t回復率:\t\t%d%%\n\n", healp[0], healp[1]);
		printf("%s:", name);
		if (data1[Mshieldnum] > 0) {
			printf("#");
		}
		for (a = 1; a <= 10; a++) {
			if (hpercent[0][1] >= a)printf("■");
			else printf("□");
		}
		if (data1[Mshieldnum] > 0) {
			printf("#");
		}
		printf("  %s:", entityname[tag][EA]);
		if (force > 0) {
			printf("*");
		}
		if (data2[Eshieldnum] > 0) {
			printf("#");
		}
		for (a = 1; a <= 10; a++) {
			if (hpercent[1][1] >= a)printf("■");
			else printf("□");
		}
		if (data2[Eshieldnum] > 0) {
			printf("#");
		}
		if (force > 0) {
			printf("*");
		}
		printf("\n");
		if ((stage == 3) && (EA == 0)) {
			if (unit[0][1] == 0) {
				printf("攻撃ユニット:\t\t%03dHP\n", unit[0][0]);
			}
			else {
				printf("ユニット破損…\n");
			}
			if (unit[1][1] == 0) {
				printf("シールドユニット:\t%03dHP\n", unit[1][0]);
			}
			else {
				printf("ユニット破損…\n");
			}
			if (unit[2][1] == 0) {
				printf("回復ユニット:\t\t%03dHP\n", unit[2][0]);
			}
			else {
				printf("ユニット破損…\n");
			}
			if (unit[3][1] == 0) {
				printf("ダメージユニット:\t%03dHP\n", unit[3][0]);
			}
			else {
				printf("ユニット破損…\n");
			}
		}
		/* 行動選択 */
		if (!!turn) {
			k2 = AIpat(ak1 - 1, ak2);
		}
		else {
			while (ak2 == k2) {
				k2 = randnum(4);
			}
		}
		do {
			printf("行動選択\n攻撃:1 特殊攻撃:2 回避行動:3 特殊攻撃壁:4");
			if ((data1[Mskill] == 1) && (spsk1 > 0)) {
				printf(" 火炎放射:5");
			}
			printf("\n");
			connum(&k1);
			if ((k1 == 5) && (data1[Mskill] == 1) && (spsk1 > 0)) {
				break;
			}
		} while ((k1 == ak1) || (k1 < 1) || (k1 > 4));
		if (k1 == 5) {
			printf("%sは火炎放射を使った!!\n", name);
			dmgcntr = 0;
			for (a = 1; a <= data1[Mskc]; a++) {
				dmgcntr = (float)(dmgcntr + (((ac * 0.1) + 0.5) / a) * data1[MAT]);
			}
			dmg[1] = (int)(dmgcntr);
			spsk1 = -1;
			data1[Mskc] = -1;
			k1 = 2;
		}
		if (randnum(100) <= (99 - unlike) / 2) {
			/*printf("プレイヤーと%sは息がぴったりだ!!\n", name);
			c14;
			bond = 1;*/
		}
		ak = k1;
		if (!!turn) {
			AI(ak1 - 1, ak2);
		}
		ak1 = k1;
		ak2 = k2;
		if (spsk1 > 0) {
			if (((ak1 == 1) || (ak1 == 2)) && (data1[Mskill] == 1)) {
				data1[Mskc]++;
				printf("現在のスキルカウンタ:%d\n", data1[Mskc]);
			}
		}
		if (((ak1 == 2) || (ak1 == 1)) && (data1[Mskill] == 3)) {
			data1[Mskc]++;
			if ((data1[Mskc]) >= 5) {
				if (SG[1][1] >= ac + 1) {
					SG[1][1] = SG[1][1] - (ac + 1);
				}
				else {
					SG[1][1] = 0;
				}
				printf("スキルによりストライクゲージが変動した!!\n");
				data1[Mskc] = 0;
			}
			else {
				printf("現在のスキルカウンタ:%d\n", data1[Mskc]);
			}
		}
		/******************************************************************************************************************/
		if ((k1 == 1) && (k2 == 0)) {//通常　通常
			if (force > 0) {
				atkE;
			}
			else {
				atk2;
			}
			atk1;
			du1;
			du2;
			printf("%sの通常攻撃!! %sの通常攻撃!!\n", name, entityname[tag][EA]);
			FS0;
			FS1;
			c1;
			c2;
		}
		else if ((k1 == 1) && (k2 == 1)) {//通常　特殊
			if (force > 0) {
				spatkE;
			}
			else {
				spatk2;
			}
			boost1;
			ent;
			enttier;
			rate++;
			du1;
			printf("%sの通常攻撃!! しかし%sは距離を取っている…\n%sの特殊攻撃!!\n", name, entityname[tag][EA], entityname[tag][EA]);
			FS0;
			FS1;
			c1;
		}
		else if ((k1 == 1) && (k2 == 2)) {//通常　回避
			if (randnum(100) < sp2) {
				heal2;
				if (dmg[1] < 0)dmg[1] = dmg[1] / 2;
				shield2;
				boost1;
				printf("%sの通常攻撃!! しかし%sの回避行動によって回避された。\n", name, entityname[tag][EA]);
				FS0;
				c1;
			}
			else {
				atk1;
				du2;
				printf("%sの通常攻撃!! %sは回避に失敗した!!\n", name, entityname[tag][EA]);
				FS0;
				c1;
				c2;
			}
		}
		else if ((k1 == 1) && (k2 == 3)) {//通常　壁
			atk1;
			rptp;
			rate--;
			du2;
			printf("%sの通常攻撃!! %sは攻撃反射に失敗した!!\n", name, entityname[tag][EA]);
			FS0;
			c1;
			c2;
		}
		/******************************************************************************************************************/
		else if ((k1 == 2) && (k2 == 0)) {//特殊　通常
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", entityname[tag][EA], name);
				data1[MAT] = 1;
				data1[Mdamageboost] = 0;
				data1[Mshield] = 0;
				data1[Mshieldnum] = 0;
				hmax1 = 1;
				spsk1 = 0;
				FS0;
			}
			else {
				spatk1;
				if (data1[Mskill] == 2) {
					sk2(&dmg[1]);
				}
				boost2;
				rptp;
				if (data2[Eskill] == 2)data2[Eskill] = 0;
				if (data2[Ecnt] == 2)data2[Ecnt] = 0;
				rate--;
				du2;
				printf("%sの特殊攻撃!! %sの攻撃は距離があって届かない!!\n", name, entityname[tag][EA]);
				FS0;
				FS1;
				c1;
				c2;
			}
		}
		else if ((k1 == 2) && (k2 == 1)) {//特殊　特殊
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", entityname[tag][EA], name);
				data1[MAT] = 1;
				data1[Mdamageboost] = 0;
				data1[Mshield] = 0;
				data1[Mshieldnum] = 0;
				hmax1 = 1;
				spsk1 = 0;
				FS0;
			}
			else {
				if (force > 0) {
					spatkE;
				}
				else {
					spatk2;
				}
				spatk1;
				if (data1[Mskill] == 2) {
					sk2(&dmg[1]);
				}
				ent;
				enttier;
				du1;
				du2;
				printf("%sの特殊攻撃!! %sの特殊攻撃!!\n", name, entityname[tag][EA]);
				FS0;
				FS1;
				c1;
				c2;
			}
		}
		else if ((k1 == 2) && (k2 == 2)) {//特殊　回避
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", entityname[tag][EA], name);
				data1[MAT] = 1;
				data1[Mdamageboost] = 0;
				data1[Mshield] = 0;
				data1[Mshieldnum] = 0;
				hmax1 = 1;
				spsk1 = 0;
				FS0;
			}
			else {
				if (randnum(100) < sp2 / 2) {
					heal2;
					shield2;
					if (dmg[1] < 0)dmg[1] = dmg[1] / 3;
					boost1;
					printf("%sの特殊攻撃!! しかし%sの回避行動によって回避された。\n", name, entityname[tag][EA]);
					FS0;
					c1;
				}
				else {
					spatk1;
					if (data1[Mskill] == 2) {
						sk2(&dmg[1]);
					}
					du2;
					printf("%sの特殊攻撃!! %sは回避に失敗した!!\n", name, entityname[tag][EA]);
					FS0;
					c1;
					c2;
				}
			}
		}
		else if ((k1 == 2) && (k2 == 3)) {//特殊　壁
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", entityname[tag][EA], name);
				data1[MAT] = 1;
				data1[Mdamageboost] = 0;
				data1[Mshield] = 0;
				data1[Mshieldnum] = 0;
				hmax1 = 1;
				spsk1 = 0;
				FS0;
			}
			else {
				ref1;
				if (data1[Mill] != 1)boost1;
				rptm;
				rate++;
				painin;
				du1;
				printf("%sの特殊攻撃!! しかし%sの特殊攻撃壁によって反射された。\n", name, entityname[tag][EA]);
				FS0;
				c1;
			}
		}
		/******************************************************************************************************************/
		else if ((k1 == 3) && (k2 == 0)) {//回避　通常
			if (randnum(100) < sp && !nsp) {
				shield1;
				heal1;
				if (stage == 3)heal1;
				if (data2[Eskill] == 2)data2[Eskill] = 0;
				if (data2[Ecnt] == 2)data2[Ecnt] = 0;
				if (dmg[0] < 0)dmg[0] = dmg[0] / 2;
				boost2;
				espain;
				printf("%sの通常攻撃!! しかし%sは攻撃を回避した!!\n", entityname[tag][EA], name);
				FS1;
				c3;
			}
			else {
				if (force > 0) {
					atkE;
				}
				else {
					atk2;
				}
				rptm;
				du1;
				printf("%sの通常攻撃!! %sは回避に失敗した。\n", entityname[tag][EA], name);
				FS1;
			}
		}
		else if ((k1 == 3) && (k2 == 1)) {//回避　特殊
			ent;
			enttier;
			if (randnum(100) < sp / 2 && !nsp) {
				shield1;
				heal1;
				if (stage == 3)heal1;
				if (data2[Eskill] == 2)data2[Eskill] = 0;
				if (data2[Ecnt] == 2)data2[Ecnt] = 0;
				if (dmg[0] < 0)dmg[0] = dmg[0] / 3;
				boost2;
				espain;
				printf("%sの特殊攻撃!! %sは回避した!!\n", entityname[tag][EA], name);
				FS1;
				c3;
			}
			else {
				if (force > 0) {
					spatkE;
				}
				else {
					spatk2;
				}
				rptm;
				du1;
				printf("%sの特殊攻撃!! %sは回避に失敗してしまった。\n", entityname[tag][EA], name);
				FS1;
			}
		}
		else if ((k1 == 3) && (k2 == 2)) {//回避　回避
			heal1;
			if (stage == 3)heal1;
			heal2;
			shield1;
			shield2;
			rptm;
			espain;
			printf("%sと%sの回避行動… お互いに睨みあっている。\n", name, entityname[tag][EA]);
		}
		else if ((k1 == 3) && (k2 == 3)) {//回避　壁
			shield1;
			heal1;
			if (stage == 3)heal1;
			rptm;
			rate--;
			painin;
			printf("%sの回避行動!! %sは特殊反射の構えに入っている。\n", name, entityname[tag][EA]);
		}
		/******************************************************************************************************************/
		else if ((k1 == 4) && (k2 == 0)) {//壁　通常
			if (force > 0) {
				atkE;
			}
			else {
				atk2;
			}
			rate++;
			du1;
			printf("%sは特殊反射の構えに入っている… %sの通常攻撃!!\n", name, entityname[tag][EA]);
			FS1;
		}
		else if ((k1 == 4) && (k2 == 1)) {//壁　特殊
			ref2;
			boost2;
			if (data2[Eskill] == 2)data2[Eskill] = 0;
			if (data2[Ecnt] == 2)data2[Ecnt] = 0;
			rate--;
			du2;
			printf("%sの特殊攻撃!! しかし%sの特殊反射壁によって反射した!!\n", entityname[tag][EA], name);
			FS1;
			c4;
		}
		else if ((k1 == 4) && (k2 == 2)) {//壁　回避
			heal2;
			shield2;
			rptm;
			printf("%sは特殊反射の構えに入っている… %sは回避運動をしている…\n", name, entityname[tag][EA]);
		}
		else if ((k1 == 4) && (k2 == 3)) {//壁　壁
			rptm;
			rate--;
			painin;
			printf("お互いに睨みあっている\n");
		}
		/******************************************************************************************************************/
		if ((setturn - turn) <= 5 && ((setturn - turn) >= 0)) {
			printf("\n\aセットまであと%dターン\n\n", setturn - turn);
		}
		if ((setturn - turn) == 0) {
			printf("\nセット!!\n");
			set_flg = 1;
		}
		if ((ak1 == 1) || (ak1 == 2))pen++; else pen = 0;
		if (pen > 4)data.s1 = data.s1 - 3;
		if (pen > 6) { printf("<不純> -6pts\n"); if (Evad[2] - 6 < 0)Evad[2] = 0; else Evad[2] = Evad[2] - 6; }
//		if ((turn <= 0) && (end == 1))end = 0, dmg[0] = 100000000, dmg[1] = 100000000, totalpo = totalpo + 3000, dmgp[0] = 1000, dmgp[1] = 1000, turn = 75;
		if (dmg[0] > 0 /*&& end == 0*/) {
			dmg[0] = (int)((dmg[0] * (dmgp[0] + spdp)) / 100);
			if (dmg[0] <= 0)dmg[0] = 1;
		}
		if (dmg[1] > 0 /*&& end == 0*/) {
			dmg[1] = (int)((dmg[1] * dmgp[1]) / 100);
			if (dmg[1] <= 0)dmg[1] = 1;
		}
		switch (data2[Eskill]) {
		case 0:
			break;
		case 1:
			if (dmg[1] > 0) {
				data2[EAT] = data2[EAT] + 5;
			}
			break;
		case 2:
			timer(1);
			if ((dmg[0] > 0) && ((ak2 == 0) || (ak2 == 1))) {
				if (randnum(2) == 0) {
					data2[Ecnt]++;
					printf("%sは力をためている…\n", entityname[tag][EA]);
				}
				else {
					for (a = 0, b = data2[EAT]; a < data2[Ecnt]; a++) {
						b = b * 2;
					}
					data2[Ecnt] = 0;
					dmg[0] = dmgd(hmax2, data2[EHP], b);
					printf("%sは力を開放した。\n", entityname[tag][EA]);

				}
			}
			break;
		case 3:
			break;
		case 4:
			timer(1);
			if (dmg[0] > 0) {
				timer(1);
				if (randnum(100) <= data2[Ecnt]) {
					Mres[0] = 0;
					dmg[0] = data1[MHP] + data1[Mshieldnum];
					printf("%sのスキルにより%sは即死した。\n", entityname[tag][EA], name);
				}
				else {
					data2[Ecnt]++;
					printf("闇の霧の濃度:%d%%\n", data2[Ecnt]);
				}
			}
			break;
		case 5:
			timer(1);
			if ((ak2 == 0) || (ak2 == 1) && (dmg[0] > 0) && (data2[Ecnt] == 0)) {
				if (data1[Mill] != 1) {
					if (randnum(100) <= arge) {
						data2[Ecnt] = 4;
						data1[Mill] = 1;
						printf("衰弱症が発症した。\n");
					}
				}
			}
			if (data1[Mill] == 1) {
				if (data2[Ecnt] == 4) {
					data1[MAT] = data1[MAT] / 2;
				}
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					data1[MAT] = data1[MAT] * 2;
					printf("衰弱症が完治した!!\n");
				}
			}
			break;
		case 6:
			timer(1);
			if ((ak2 == 0) || (ak2 == 1) && (dmg[0] > 0) && (data2[Ecnt] == 0)) {
				if (data1[Mill] != 2) {
					if (randnum(100) <= arge) {
						data2[Ecnt] = 4;
						data1[Mill] = 2;
						printf("吐血症が発症した。\n");
					}
				}
			}
			if (data1[Mill] == 2) {
				data1[MHP] = data1[MHP] - data1[MHP] / 10;
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					printf("吐血症が完治した!!\n");
				}
			}
			break;
		case 7:
			timer(1);
			if ((ak2 == 0) || (ak2 == 1) && (dmg[0] > 0) && (data2[Ecnt] == 0)) {

				if (data1[Mill] != 3) {
					if (randnum(100) <= arge) {
						data2[Ecnt] = 6;
						data1[Mill] = 3;
						printf("壊死症が発症した。\n");
					}
				}
			}
			if (data1[Mill] == 3) {
				nsp = 1;
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					nsp = 0;
					printf("壊死症が完治した。\n");
				}
			}
			break;
		case 8:
			timer(1);
			if (((ak2 == 0) || (ak2 == 1)) && (dmg[0] > 0)) {
				if (randnum(100) <= arge) {
					if ((data1[Mill] != 0) && (data1[Mill] != 4)) {
						if (data1[Mill] == 1) {
							data1[MAT] = data1[MAT] * 2;
						}
						data1[Mill] = 4;
						nsp = 1;
						data2[Ecnt] = 5;
						printf("錯乱症が発症した。\n");
					}
					else if (data1[Mill] != 4) {
						timer(1);
						while ((a = randnum(3)) == (data1[Mill] - 1));
						if (a == 0) {
							data2[Ecnt] = 6;
							data1[Mill] = 1;
							printf("衰弱症が発症した。\n");
						}
						else if (a == 1) {
							data2[Ecnt] = 4;
							data1[Mill] = 2;
							printf("吐血症が発症した。\n");
						}
						else if (a == 2) {
							data2[Ecnt] = 6;
							data1[Mill] = 3;
							printf("壊死症が発症した。\n");
						}
					}
				}
			}
			if (data1[Mill] == 1) {
				if (data2[Ecnt] == 4) {
					data1[MAT] = data1[MAT] / 2;
				}
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					data1[MAT] = data1[MAT] * 2;
					printf("衰弱症が完治した!!\n");
				}
			}
			else if (data1[Mill] == 2) {
				data1[MHP] = data1[MHP] - data1[MHP] / 10;
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					printf("吐血症が完治した!!\n");
				}
			}
			else if (data1[Mill] == 3) {
				nsp = 1;
				data2[Ecnt]--;
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					nsp = 0;
					printf("壊死症が完治した。\n");
				}
			}
			else if (data1[Mill] == 4) {
				nsp = 1;
				if ((dmg[0] >= 0) && (dmg[1] >= 0)) {
					dmg[0] = dmg[0] + dmg[1];
					dmg[1] = 0;
				}
				else if ((dmg[0] < 0) && (dmg[1] <= 0)) {
					dmg[1] = dmg[0] + dmg[1];
					dmg[0] = 0;
				}
				else if ((dmg[0] <= 0) && (dmg[1] >= 0)) {
					a = dmg[0];
					dmg[0] = dmg[1];
					dmg[1] = a;
				}
				if (data2[Ecnt] <= 0) {
					data1[Mill] = 0;
					data2[Ecnt] = 0;
					nsp = 0;
					printf("錯乱症が完治した。\n");
				}
			}
			break;
		case 9:
			if (dmg[1] > 0) {
				if (data2[Eshieldnum] > 0) {
					unit[1][0] = unit[1][0] - dmg[1];
					printf("%sに%dダメージ!! しかしシールドユニットに吸収されてしまった。\n", entityname[tag][EA], dmg[1]);
					pt;
					dmg[1] = 0;
				}
				if (ak1 == 1) {
					unit[0][0] = unit[0][0] - dmg[1];
					for (a = 2; a < 4; a++) {
						unit[a][0] = unit[a][0] - (dmg[1] / 2);
					}
				}
				else if (ak1 == 2) {
					unit[2][0] = unit[2][0] - dmg[1];
					unit[0][0] = unit[0][0] - (dmg[1] / 2);
					unit[3][0] = unit[3][0] - (dmg[1] / 2);
				}
				else {
					unit[0][0] = unit[0][0] - (dmg[1] / 2);
					for (a = 2; a < 4; a++) {
						unit[a][0] = unit[a][0] - (dmg[1] / 2);
					}
				}
				for (a = 0; a < 4; a++) {
					if (unit[a][0] <= 0) {
						unit[a][0] = 0;
						if ((a == 0) && (unit[a][1] == 0)) {
							printf("\a攻撃ユニット破壊!!\n");
							hmax2 = hmax2 - 500;
							data2[EAT] = data2[EAT] / 2;
							data2[Edamageboost] = 0;
							unit[a][1] = 4;
						}
						if ((a == 1) && (unit[a][1] == 0)) {
							printf("\aシールドユニット破壊!!\n");
							hmax2 = hmax2 - 500;
							data2[Eshieldnum] = 0;
							unit[a][1] = 3;
						}
						if ((a == 2) && (unit[a][1] == 0)) {
							printf("\a回復ユニット破壊!!\n");
							hmax2 = hmax2 - 500;
							unit[a][1] = 4;
						}
						if ((a == 3) && (unit[a][1] == 0)) {
							printf("\aダメージユニット破壊!!\n");
							unit[2][1] = 1;
							hmax2 = hmax2 - 500;
							unit[a][1] = 5;
						}
					}
				}
			}
			if (unit[2][1] == 0) {
				for (a = 0; a < 4; a++) {
					if (unit[a][1] > 0) {
						unit[a][1]--;
						if ((a == 0) && (unit[a][1] == 0)) {
							printf("攻撃ユニット復活\n");
							unit[a][0] = 250;
							data2[Edamageboost] = 1;
							data2[EAT] = data2[EAT] * 2;
						}
						else if ((a == 1) && (unit[a][1] == 0)) {
							printf("シールドユニット復活\n");
							unit[a][0] = 150;
						}
						else if ((a == 2) && (unit[a][1] == 0)) {
							printf("回復ユニット復活\n");
							unit[a][0] = 300;
						}
						else if ((a == 3) && (unit[a][1] == 0)) {
							printf("ダメージユニット復活\n");
							unit[a][0] = 400;
						}
					}
				}
			}
			else {
				unit[2][1]--;
				if (unit[2][1] == 0) {
					printf("回復ユニット復活\n");
					unit[2][0] = 300;
				}
			}
			if (unit[1][1] == 0) {
				data2[Eshieldnum] = 10000;
			}
			if (unit[3][1] != 0) {
				hmax2 = hmax2 - 1000;
			}
			break;
		}
		if ((hmax1 <= 0) && (deadflag == 0)) {//最大HPの処理はこれより上に
			hmax1 = 1;
		}
		if (hmax2 <= 0) {
			hmax2 = 1;
		}
		if ((EA == 7) && (stage == 2) && (dmg[0] > 0)) {
			if (randnum((data1[MHP] / hmax1) * 100) == 0) {
				printf("凄まじい衝撃波は%sを吹き飛ばした。\n", name);
				Mres[0] = 0;
				dmg[0] = data1[MHP] + data1[Mshieldnum];
			}
		}
		if ((data2[Eskill] == 1) || (data2[Ecnt] == 1) && (dmg[1] > 0)) {
			data2[EAT] = data2[EAT] + 5;
		}
		/*if (end != 1)*/turn++;//ターン増加
//		if (end == 1)turn--;//ターン現象
		if (dmg[1] > 0)data.s1++;
		if (dmg[0] > 0)data.s2++;
		if (dmg[0] > 0) {
			rageHP[0][1] = rageHP[0][1] + dmg[0];
		}
		if (dmg[1] > 0) {
			rageHP[1][1] = rageHP[1][1] + dmg[1];
		}
		if (((fs[1] > 0) || (randnum(100) < 1)) && ((ak2 == 0) || (ak2 == 1)) && (dmg[0] > 0)) {
			printf("\a%sは怯んだ!!\n", name);
			if (dmg[0] > 0) {
				dmg[0] = (int)(dmg[0] * crit[0] / 100);
			}
			dmgp[0] = dmgp[0] + 4;
		}
		if (((fs[0] > 0) || (randnum(100) < 1)) && ((ak1 == 1) || (ak1 == 2)) && (dmg[1] > 0)) {
			printf("\a%sは怯んだ!!\n", entityname[tag][EA]);
			if (dmg[1] > 0) {
				dmg[1] = (int)(dmg[1] * crit[1] / 100);
			}
			c5;
			pain = 0;
			dmgp[1] = dmgp[1] + 4;
		}
		if ((data2[Eskill] == 10) && (dmg[1] > 0))pain = pain + (int)(dmg[1] * 0.5);
		if (slowpain == 1)dmg[0] = dmg[0] + pain, printf("苦しみが%sを襲う!!\n", name);
		if (slowpain == 2)slowpain = 1;
		if (dmg[1] >= 200) {
			c18;
		}
		else if (dmg[1] >= 100) {
			c17;
		}
		if (dmg[0] > 0) {
			printf("%sに%dダメージ!!", name, dmg[0]);
		}
		else if (dmg[0] < 0) {
			printf("%sは%d回復!!", name, dmg[0] * -1);
		}
		printf("\n");
		if (dmg[1] > 0) {
			printf("%sに%dダメージ!!", entityname[tag][EA], dmg[1]);
		}
		else if (dmg[1] < 0) {
			printf("%sは%d回復!!", entityname[tag][EA], dmg[1] * -1);
		}
		printf("\n");
		if (dmg[0] > 0)sheal[0] = 0;
		if (dmg[1] > 0)sheal[1] = 0;
		if (sheal[0] > 0)data1[Mshieldnum] = data1[Mshieldnum] + sheal[0];
		if (sheal[1] > 0)data2[Eshieldnum] = data2[Eshieldnum] + sheal[1];
		/*****************************************ダメージ処理************************************************/
		pt;
		if ((data1[Mshieldnum] > 0) && (dmg[0] > 0)) {
			data1[Mshieldnum] = data1[Mshieldnum] - dmg[0];
			if (data1[Mshieldnum] < 0) {
				dmg[0] = (data1[Mshieldnum]) * -1;
				data1[Mshieldnum] = 0;
			}
			else {
				dmg[0] = 0;
				c12;
			}
		}
		if ((data2[Eshieldnum] > 0) && (dmg[1] > 0)) {
			data2[Eshieldnum] = data2[Eshieldnum] - dmg[1];
			if (data2[Eshieldnum] < 0) {
				dmg[1] = (data2[Eshieldnum]) * -1;
				data2[Eshieldnum] = 0;
			}
			else {
				dmg[1] = 0;
			}
		}
		data1[MHP] = data1[MHP] - dmg[0];
		data2[EHP] = data2[EHP] - dmg[1];
		dmg[0] = 0;
		dmg[1] = 0;
		if (data1[MHP] == hmax1) { c6; }
		/*********************************************end****************************************************/
		if ((nofi == 6) && (((float)data1[MHP] / (float)hmax1) <= 0.5)) {
			data1[MHP] = data1[MHP] + (int)(hmax1 * 0.1);
			nofi = 0;
			printf("アイテムの能力でHPを回復!!\n");
		}
		if ((nofi == 8) && (((float)data1[MHP] / (float)hmax1) <= 0.2)) {
			hmax1 = data1[MHP];
			nofi = 0;
			printf("アイテムの能力で最大HPを固定!!\n");
		}
		if (data1[MHP] + data1[Mshieldnum] < (data2[EAT] * dmgp[0] / 100)) { c7; }
		if ((rageHP[0][0] <= rageHP[0][1]) && rageflg[0] == 0 && data1[MHP] > 0) {
			dmgp[1] = dmgp[1] + 50;
			crit[1] = crit[1] + 25;
			rageflg[0] = 1;
			rageflg[1] = 1;
			printf("\a%sは激怒した!!\n", name);
			c10;
		}
		if ((rageHP[1][0] <= rageHP[1][1]) && rageflg[1] == 0 && data2[EHP] > 0) {
			dmgp[0] = dmgp[0] + 50;
			crit[0] = crit[0] + 25;
			rageflg[0] = 1;
			rageflg[1] = 1;
			printf("\a%sは激怒した!!\n", entityname[tag][EA]);
		}
		if (data1[Mmode] == 1) {
			data1[Mshieldnum] = data1[Mshieldnum] - 500;
			data1[MHP] = data1[MHP] - (int)(data1[MHP] * 0.02);
			if (data1[Mshieldnum] <= 0) {
				data1[Mshieldnum] = 0;
				data1[Mmode] = 0;
				printf("琥珀のかけらの効果が切れた。\n");
			}
		}
		if ((data2[Eskill] == 3) && (data2[EHP] <= hmax2 / 2)) {
			data2[EAT] = data2[EAT] + (data2[EAT] / 2);
			hmax2 = data2[EHP];
			printf("%sは分裂した!!\n", entityname[tag][EA]);
		}
		if (Evad[0] >= 3000) { c13; }
		if (data2[Eskill] == 9) {
			data2[EHP] = hmax2;
		}
		if (data1[MAT] > 100) {
			data1[MAT] -= 1;
			printf("プレイヤーはAT上限によるペナルティをうけた\n");
			if (data1[MAT] < 100) {
				data1[MAT] = 100;
			}
		}
		if (data2[EAT] > 100) {
			data2[EAT] -= 1;
			printf("敵はAT上限によるペナルティをうけた\n");
			if (data2[EAT] < 100) {
				data2[EAT] = 100;
			}
		}
		if (data1[Mshieldnum] > 10000) {
			data1[Mshieldnum] = 10000;
		}
		if (data2[Eshieldnum] > 10000) {//シールドMAX
			data2[Eshieldnum] = 10000;
		}
		if (data1[MHP] > hmax1) {
			data1[MHP] = hmax1;
		}
		if (data2[EHP] > hmax2) {
			data2[EHP] = hmax2;
		}
		if (data1[MAT] < 1)data1[MAT] = 1;
		if (data2[EAT] < 1)data2[EAT] = 1;
		if (sp < 0)sp = 0;
		if (sp > 200)sp = 200;
		if (sp2 < 0)sp2 = 0;
		if (sp2 > 200)sp2 = 200;
		for (a = 0; a < 2; a++) {
			if (crit[a] < 100)crit[a] = 100;
		}
		if (healp[0] < -500)healp[0] = -500;
		if (healp[1] < -500)healp[1] = -500;
		for (a = 0; a < 2; a++) {
			if (dmgp[a] < 0)dmgp[a] = 0;
		}
		if ((data1[MHP] <= 0) && (wildmode[0] == 1)) {
			printf("\a%sは持ちこたえている!!\n", name);
			data1[MHP] = 1;
		}
		if ((data1[MHP] <= 0) && (data1[Mreborn] > 0)) {
			printf("\a%sは復活した!!\n", name);
			data1[MHP] = 1;
			data1[Mreborn] = data1[Mreborn] - 1;
		}
		bond = 0;
/*		if (((dmgp[0] + spdp <= 0) || (dmgp[1] <= 0)) && end != 1) {
			end = 1;
			turn = turn / 4;
			printf("\aバグ発生!!\n");
		}*/
		SG[0][1]++;
		if (SG[0][1] > SG[0][0])SG[0][1] = SG[0][0];
		SG[1][1]++;
		if (SG[1][1] > SG[1][0])SG[1][1] = SG[1][0];
		for (a = 0; a < 2; a++)fs[a] = 0;
		timer(450);
		/********************************************************************/
		/********************************************************************/
		if ((data1[MHP] <= 0 || data2[EHP] <= 0) || (stage == 3 && EA == 0 && hmax2 == 1)) {
			fc_def;
			fopen_s(&SF, "Battle.txt", "a");
			if (data.s1 <= 0)data.s1 = 1;
			if (data.s2 <= 0)data.s2 = 1;
			data.s0 = (float)data.s1 / data.s2;
			data.s0 = data.s0 * data.s3;
			Evad[0] = data.s0;
			if (Evad[0] > E1)Evad[0] = (float)E1;
			if (Evad[2] > E3)Evad[2] = (float)E3;
			if (EA == 9) {
				randchar(1000);
				exit(1);
			}
			if ((rate < 0) && (swAI == 0)) {
				for (a = 0; a < 4; a++) {
					for (b = 0; b < 4; b++) {
						if (b == 0)logAI[a][0] = 0x0001000100010000;
						if (b == 1)logAI[a][1] = 0x0001000100000001;
						if (b == 2)logAI[a][2] = 0x0001000000010001;
						if (b == 3)logAI[a][3] = 0x0000000100010001;
					}
				}
				rate = 20;
				printf("\n");
			}
			else if (rate < 0) {
				rate = 0;
			}
			if (nofi == 2)totalpo = totalpo * 2, printf("アイテムの効果で取得経験値+100%%\n");
			if (data1[MHP] <= 0 && data2[EHP] > 0) {
				wl = lose;
			}
			else if (data2[EHP] <= 0 && data1[MHP] > 0) {
				wl = win;
			}
			else if ((data1[MHP] <= 0 && data2[EHP] <= 0) || (set_flg)) {
				wl = draw;
			}
			if (wl > 0) {

				switch (wl) {
				case lose:
					printf("\nlose\n");
					if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 1) {
						Evad[1] = 60;
					}
					else if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 2) {
						Evad[1] = 50;
					}
					else if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 3) {
						Evad[1] = 40;
					}
					else if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 4) {
						Evad[1] = 30;
					}
					else if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 5) {
						Evad[1] = 20;
					}
					else if ((data2[Eshieldnum] + data2[EHP]) <= data1[MAT] * 6) {
						Evad[1] = 10;
					}
					else {
						Evad[1] = 0;
					}
					break;

				case win:
					printf("\nwin\n");
					c8;
					c16;
					if ((data1[Mskill] == 1) && (spsk1 == 0)) {
						c15;
					}
					liker();
					Evad[1] = 100;
					break;

				case draw:
					printf("\ndraw\n");
					liker();
					Evad[1] = 60;
					break;
				}
				printf("\a評価:\n");
				printf("\"支配\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (Evad[0] / E1 * 10 >= (float)a) {
						printf("■");
					}
					else {
						printf("□");
					}
				}
				printf("%dpts/%dpts", (int)Evad[0], E1);
				printf("\n\"執念\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (Evad[1] / E2 * 10 >= (float)a) {
						printf("■");
					}
					else {
						printf("□");
					}
				}
				printf("%dpts/%dpts", (int)Evad[1], E2);
				printf("\n\"演出\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (Evad[2] / E3 * 10 >= (float)a) {
						printf("■");
					}
					else {
						printf("□");
					}
				}
				printf("%dpts/%dpts\n", (int)Evad[2], E3);
				b = 0;
				if (Evad[0] >= E1)b++;
				if (Evad[1] >= E2)b++;
				if (Evad[2] >= E3)b++;
				if ((wl != win) && (b >= 3)) {
					if (((battled > 0) && (EA == battled + 1)) || ((battled == 0) && (EA <= 1))) {
						battled++;
						printf("ランクアップ\n");
					}
				}
				data.s0 = data.s0 + skpt;
				skpt = (int)data.s0;
				if ((skpt > 5000) && (ac >= 4)) {
					skpt = 5000;
					printf("\aスキルプロセスが最高点に到達しました。\n");
					if (((master >> (data1[Mskill] - 1)) & 0x01) != 0x01) {
						master = master + (1 << (data1[Mskill] - 1));
					}
				}
				else {
					while (skpt > 5000) {
						if (ac >= 4) {
							ac = 4;
							skpt = 5000;
							break;
						}
						printf("\aスキルレベルがアップしました。\n\n");
						skpt = skpt - 5000;
						ac++;
					}
				}
				switch (wl) {
				case lose:
					printf("\a敵の勝利… 敵HP:%d\n", data2[EHP]);
					break;

				case win:
					if (((battled > 0) && (EA == battled + 1)) || ((battled == 0) && (EA <= 1))) {
						battled++;
						printf("ランクアップ\n");
					}
					if ((EA == 7) && (stage == 0)) {//次ステージへ
						stage = 1;
					}
					if ((EA == 7) && (stage == 2)) {
						data1[MLV] = 1;
						data1[Mxp] = 0;
						stage = 3;
						battled = 0;
						printf("ステージが3に上がった!!\n");
					}
					totalpo = totalpo + ((totalpo / 10) * (b + 1));
					printf("\a%sの勝利!! 残りHP:%d\n", name, data1[MHP]);
					break;

				case draw:
					printf("\a引き分け\n");
					break;
				}
				if (battled > 6)battled = 6;
				timer(1);
				rank();
				data1[Mxp] = data1[Mxp] + totalpo;
				fpo = fpo + totalpo;
				printf("現在のポイント:%d\n\n", fpo);
				printf("スキルレベル:%d\n", ac);
				printf("スキルポイント:%d/5000\n\n", skpt);
				a = 0;
				while (data1[Mxp] > data1[MLV] * 200) {
					if (data1[MLV] >= 50) {
						data1[MLV] = 50;
						break;
					}
					xp_flg = data1[Mxp] - data1[MLV] * 200;
					data1[MLV] = data1[MLV] + 1;
					data1[Mxp] = xp_flg;
					printf("\aレベルアップ!! LV:%d\n", data1[MLV]);
					timer(1000);
				}
				printf("経験値:%d\n", data1[Mxp]);
				if (wl == win) {
					if (stage == 3) {
						printf("全ステージクリア!!\a\n");
						timer(500);
						printf("プレイしていただきありがとうございます。\n");
						timer(500);
						printf("クリアしていただいたあなたはサイコーです!!\n");
						timer(500);
						printf("Thanks!!\n");
						timer(500);
						randchar(15);
						timer(500);
						randchar(13);
						timer(500);
						randchar(10);
						printf("…");
						timer(500);
						printf("…");
						timer(500);
						printf("…\n");
						timer(500);
						printf("また会う時まで…\n");
						timer(500);
						printf("ありがとうございました…\n");
						fopen_s(&LV, "Thanks.txt", "w");
						fprintf(LV, "ありがとうございました<(_ _)>\n");
						timer(500);
						stage = 4;
						battled = 0;
					}
				}
				timer(1000);
				printf("データの保存中…\n");
				itemc(write);
				saved(data1[MLV], data1[Mxp]);
				switch (wl) {
				case lose:
					fprintf(SF, "Lose %s HP:%d(over damage) %s EHP:%d\n", name, data1[MHP], entityname[tag][EA], data2[EHP]);
					break;

				case win:
					fprintf(SF, "Win %s HP:%d %s EHP:%d(over damage)\n", name, data1[MHP], entityname[tag][EA], data2[EHP]);
					break;

				case draw:
					fprintf(SF, "Draw %s HP:%d(over damage) %s EHP:%d(over damage)\n", name, data1[MHP], entityname[tag][EA], data2[EHP]);
					break;
				}
				timer(2000);
				break;
			}
		}
	}
	startwait();
	exit(1);
}
/* AI pattern sistems */
void AIsave(short int ak1, short int ak2) {
	unsigned _int64 samp = 0;
	unsigned char a;
	if (!!turn) {
		for (a = 0; a < 3; a++) {//kp3 kp2 kp1 kp0
			samp = samp + kp[3 - a];
			samp = samp << 16;
		}
		samp = samp + kp[0];
		logAI[ak1][ak2] = samp;
	}
}

short int AIpat(short int ak1, short int ak2) {
	int total = 0, T;
	double pat[4];
	unsigned char a;
	initAI(ak1, ak2);
	kp[ak2] = 0;
	for (a = 0; a < 4; a++) {
		total = total + kp[a];
	}
	for (a = 0; a < 4; a++) {
		pat[a] = (double)kp[a] / total * 1000;
	}
	timer(1);
	T = randnum(1000) + 1;
	if (pat[0] > T && ak2 != 0) {
		return 0;
	}
	else if (pat[0] + pat[1] >= T && ak2 != 1) {
		return 1;
	}
	else if (pat[0] + pat[1] + pat[2] >= T && ak2 != 2) {
		return 2;
	}
	if (pat[0] + pat[1] + pat[2] + pat[3] >= T && ak2 != 3) {
		return 3;
	}
	else {
		return 4;
		printf("\aError\n\n");
	}

}

void initAI(short int ak1, short int ak2) {
	unsigned __int64 samp;
	unsigned char a;
	if (!!turn) {
		samp = logAI[ak1][ak2];
		for (a = 0; a < 4; a++) {
			kp[a] = samp & 0xffff;
			samp = samp >> 16;
		}
	}
}

void AI(short int ak1, short int ak2) {
	switch (ak) {
	case 1:
		initAI(ak1, ak2);
		if (ak2 != 0)kp[0]++;
		if (ak2 != 1)kp[1]++, kp[1]++;
		if (ak2 != 2)kp[2]++;
		AIsave(ak1, ak2);
		break;
	case 2:
		initAI(ak1, ak2);
		if (ak2 != 1)kp[1]++;
		if (ak2 != 2)kp[2]++;
		if (ak2 != 3)kp[3]++, kp[3]++;
		AIsave(ak1, ak2);
		break;
	case 3:
		initAI(ak1, ak2);
		if (ak2 != 0)kp[0]++;
		if (ak2 != 1)kp[1]++;
		AIsave(ak1, ak2);
		break;
	case 4:
		initAI(ak1, ak2);
		if (ak2 != 0)kp[0]++;
		AIsave(ak1, ak2);
		break;
	}
}
/* AI patern systems END */


void sk2(int* damage) {
	if (randnum(100) < spsc) {
		printf("\a大地の叫びが敵を切り裂く。\n");
		*damage = ((data1[MAT] + data2[EAT]) / 2) * 3;
		spsc = 0;
	}
	else {
		spsc = spsc + ac + 1;
		printf("スキル命中の確率:%d%%\n", spsc - (ac + 1));
	}
}

void liker(void) {
}

int dmgd(int hmax, int hp, int AT) {//ダメージ精度演算
	timer(1);
	float per;
	per = (float)AT - (float)hp / hmax * AT;
	return AT - randnum((int)per);
}

void itemc(int iflg) {
	int cnt = 0;
	__int64 itemcnt = item;
	if (iflg == 0) {
		for (cnt = 0; cnt < 18; cnt++) {
			itemn[cnt] = itemcnt & 0x7;
			itemcnt = itemcnt >> 3;
		}
	}
	else {
		item = 0;
		for (cnt = 17; cnt >= 0; cnt--) {
			item = item + itemn[cnt];
			if (cnt != 0) {
				item = item << 3;
			}
		}
	}
}

void saved(int lv, int xp) {
	fopen_s(&LV, "LV.tb", "w");
	fprintf(LV, savet, savepatt);
	fclose(LV);
}

void startwait(void)
{
	int swc;
	while (1) {
		printf("1を入力してください:");
		connum(&swc);
		if (swc == 1) {
			break;
		}
	}
}

char menu(void)
{
	int yncnt;
	printf("1:バトル\n2:ショップ\n");
	connum(&yncnt);
	return yncnt;
}

int randnum(int suu)
{
	int a;
	timer(3);
	init_genrand((unsigned int)clock());
	if (suu > 0) {
		a = genrand_int32() % suu;
	}
	else {
		a = 0;
	}
	return a;
}

void timer(int time)
{
	clock_t start, clockt; /* 無駄を省いた最高のプログラム */
	start = clock();       /* 適切な時間を計測可能         */
	clockt = clock();      /* time = 1ms.....1s = 1000ms   */
	while (clockt - start <= time) {
		clockt = clock();
	}
}

void data_check(void)
{
	char data[10];
	char* moto[] = { "TheBattle" };
	int len = 0;
	int a;
	printf("セーブデータのチェックをします。\n");
	timer(300);
	fopen_s(&LV, "LV.tb", "a");
	fclose(LV);
	fopen_s(&LV, "LV.tb", "r");
	fgets(data, 10, LV);
	fclose(LV);
	if (!strcmp(data, moto[0])) {
		printf("セーブデータが見つかりました。\n");
	}
	else {
		printf("\aセーブデータが無い可能性があります。\nセーブデータを初期化します。");
		do {
			printf("キャラクターの名前は何ですか？ 6文字以内で入力してください。(全角3文字)\n");
			gets_s(name, sizeof(name));
			len = (int)strlen(name);
		} while (len > 6);
		for (len = 0; len < 6; len++) {
			if (name[len] == '\0') {
				for (a = len; a < 6; a++) {
					name[a] = ' ';
				}
				break;
			}
			name[6] = '\0';
		}
		startwait();
		saved(1, 0);
	}

}

void rank(void)
{
	if (battled < 1) {
		//低ランク
	}
	else if (battled < 2) {
		totalpo = (unsigned int)(totalpo * 1.1);//高ランク
	}
	else if (battled < 3) {
		totalpo = (unsigned int)(totalpo * 1.2);//ブロンズランク
	}
	else if (battled < 4) {
		totalpo = (unsigned int)(totalpo * 1.3);//シルバーランク
	}
	else if (battled < 5) {
		totalpo = (unsigned int)(totalpo * 1.4);//ゴールドランク
	}
	else if (battled < 6) {
		totalpo = (unsigned int)(totalpo * 1.5);//ダイヤモンドランク
	}
	else if (battled >= 6) {
		totalpo = (unsigned int)(totalpo * 1.6);//タンザナイトランク
	}
}

void randchar(int c) {
	unsigned char a = 0xff, b;
	int d;
	time_t t;
	time(&t);
	c--;
	for (d = 0; d <= c; d++) {
		init_genrand(clock() + (unsigned long)t);
		a = genrand_int32() % 0x06 + 2;
		a = a << 4;
		timer(1);
		init_genrand(clock());
		b = genrand_int32() % 0x10;
		a = a + b;
		printf("%c", a);
		timer(10);
	}
}

void connum(int* a) {//全角修正予定
	int b;
	scanf_s("%d", &b);
	*a = b;
}

int shop(int a, int b)
{
	int spcnt, spcnt2, spcnt3;
	int abip = 6;
	unsigned char itemper[allitem] = { 2, 7, 7, 8, 8, 8, 12, 12, 12, 17, 17 };
	while (1) {
		printf("point:%d\n***商品***\n1::不思議な箱:: 5000ポイント\n", fpo);
		if (stage == 1) {
			printf("2::ステージ2へのチケット:: 50000ポイント\n");
		}
		connum(&spcnt);
		if ((spcnt >= 2) && (stage != 1)) {
			return 0;
		}
		if ((spcnt == 1) && (fpo >= 5000)) {//アイテムスロット
			fpo = fpo - 5000;
			timer(1000);
			printf("3\a");
			timer(1000);
			printf("\r2\a");
			timer(1000);
			printf("\r1\a");
			timer(1000);
			printf("\ropen!!\n\n");
			spcnt = 0;
			for (spcnt2 = 0; spcnt2 < allitem - 1; spcnt2++) {
				spcnt = spcnt + itemper[spcnt2];
			}
			spcnt3 = randnum(spcnt);
			spcnt = 0;
			for (spcnt2 = 0; spcnt2 < allitem - 1; spcnt2++) {
				spcnt = spcnt + itemper[spcnt2];
				if (spcnt3 < spcnt) {
					spcnt = spcnt2;
					break;
				}
			}
			switch (spcnt) {
			case 0:
				printf("** Legendary **\n\a");
				printf("Item:奇妙な石\n\n");
				printf("奇妙な力を受けて震えている。 水切りをするには手ごろな形。\n*ダメージ倍率が10%%減少する。バトル中のHPが0未満になったとき、2度だけ復活できる。*\n");
				itemn[0]++;
				printf("所持数:%x\n", itemn[0]);
				break;
			case 1:
				printf("** Epiq **\n\a");
				printf("Item:アルジオロジーの血\n\n");
				printf("「アルジオロジー」という縁起の悪い生物の血。 多分おいしくない。\n*力を増強する。取得経験値及び、取得ポイントが100%%上昇する。*\n");
				itemn[1]++;
				printf("所持数:%x\n", itemn[1]);
				break;
			case 2:
				printf("** Epiq **\n\a");
				printf("Item:期限の切れた薬品\n\n");
				printf("賞味期限だからまだ大丈夫…\n*回復率が20%%上昇する。*\n");
				itemn[2]++;
				printf("所持数:%x\n", itemn[2]);
				break;
			case 3:
				printf("** Super Rea **\n\a");
				printf("Item:邪悪なる宝石\n\n");
				printf("漆黒の宝石。\n*邪神Ⅲの出現確率がとてつもなく上昇する。*\n");
				itemn[3]++;
				printf("所持数:%x\n", itemn[3]);
				break;
			case 4:
				printf("** Super Rea **\n\a");
				printf("Item:復活薬\n\n");
				printf("復活するための薬。 ほっぺたが落ちるほどの不味さ。 \n*バトル中のHPが0未満になったとき、1度だけ復活できる。*\n");
				itemn[4]++;
				printf("所持数:%x\n", itemn[4]);
				break;
			case 5:
				printf("** Super Rea **\n\a");
				printf("Item:\n\n");
				printf("。\n*。*\n");
				break;
			case 6:
				printf("** Rea **\n");
				printf("Text:回復薬\n\n");
				printf("飲むと回復した気になれる薬(実は青汁)。\n*バトル中のHPが最大HPの50%%以下になったとき、1度だけ最大HPの10%%のHPを回復する。*\n");
				itemn[5]++;
				printf("所持数:%x\n", itemn[5]);
				break;
			case 7:
				printf("** Rea **\n");
				printf("Text:琥珀のかけら\n\n");
				printf("きれいな琥珀のかけら、3個集まることで効果を発揮する。\n*自然の力を身に宿すことができる。*\n");
				itemn[6]++;
				printf("所持数:%x\n", itemn[6]);
				break;
			case 8:
				printf("** Rea **\n");
				printf("Text:救急キット\n\n");
				printf("簡易的な救急キット。\n*HPが20%%以下になった時にHPを固定する。*\n");
				itemn[7]++;
				printf("所持数:%x\n", itemn[7]);
				break;
			case 9:
				printf("** Un common **\n");
				printf("Text:お医者さんキット\n\n");
				printf("子供のごっこ遊び用キット。 …風邪薬が入ってたりする。\n*HPが10%%増加する*\n");
				itemn[8]++;
				printf("所持数:%x\n", itemn[8]);
				break;
			case 10:
				printf("** Un common **\n");
				printf("Text:聖なるお祈り\n\n");
				printf("天に向かい祈りを捧げる…\n*少しの確率で1回だけ復活できるかもしれない。*\n");
				itemn[9]++;
				printf("所持数:%x\n", itemn[9]);
				break;
			}//ここまで
			for (spcnt = 0; spcnt < 18; spcnt++) {/*アイテム総数18個まで*/
				if (itemn[spcnt] > 7)/*保有できるアイテムの最大値 unsigned _int64 int = 8byte = 64bitなので、32/18=3.5 = 3bit*/
					itemn[spcnt] = 7;/*約3bitを1つのアイテムに使用できます。3bit=7個なのでアイテムの最大保有数は7個になります。*/
			}
			printf("\n\n");
		}
		else if ((spcnt == 2) && (fpo >= 50000)) {
			printf("\a*注意* ステージを2にすると一部データがリセットされ、現在より難易度が高くなります。\n");
			printf("よろしいですか? Yes=1\n");
			connum(&spcnt);
			if (spcnt == 1) {
				fpo = fpo - 50000;
				stage = 2;
				b = a * 10;
				a = 1;
				fpo = fpo / 10;
				battled = 0;
				item = 0;
				printf("\aステージが2になりました。\n");
				printf("Lv:%d\n", a);
				printf("xp:%d\n", b);
				printf("ポイント:%d\n", fpo);
				printf("ランク:低ランク\n");
				itemc(read);
				itemc(write);
				saved(a, b);
				printf("再起動してください。\n");
				timer(800);
				startwait();
				exit(1);
			}
			else {
				printf("ポイントが足りません\n");
				return 0;
			}
		}
		else {
			return 0;
		}
		itemc(write);
		saved(a, b);
		itemc(read);
	}
}
