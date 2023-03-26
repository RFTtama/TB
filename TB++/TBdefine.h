#pragma once
/*Macros*/
#define savepatt1 name, data1[MLV], data1[Mxp], stgProgress, fpo, item, stage, pla.GetSkill(true), ac, skpt
#define savepatt2 APS.GetAIrate(), dislike, total_b, wlpattern[0], wlpattern[1] \
, s_rate, dominated, sklXp[0], sklLv[0], sklXp[1], sklLv[1] \
, sklXp[2], sklLv[2], VERSION, unlock_key, firstCont, calcDmg, APS.GetStreak(), APS.GetMaxRate() \
, cfg.getUnlocked(), APS.GetAIdecide(0), APS.GetAIdecide(1), APS.GetAIdecide(2), APS.GetAIdecide(3)\
, APS.GetAIdecide(4), APS.GetAIdecide(5), APS.GetAIdecide(6), APS.GetAIdecide(7), APS.GetAIdecide(8)\
, APS.GetAIdecide(9), APS.GetAIdecide(10), APS.GetAIdecide(11), APS.GetAIdecide(12), APS.GetAIdecide(13)\
, APS.GetAIdecide(14), APS.GetAIdecide(15), APS.GetAIdecide(16), APS.GetAIdecide(17), APS.GetAIdecide(18)\
, APS.GetAIdecide(19), APS.GetAIdecide(20)
#define ent if (EM.GetEi() == 8)data2[Etier]++;
#define enttier if(data2[Etier] > 5)data2[Etier] = 5;
#define sk1cp if(pla.GetSkill(false) == 1 && spsk1 > 0)data1[Mskc]++;
/**************/
/*defines*/
#define VERSION 130
#define CNUM 25
#define RANK_NUM 8
#define cMaxn 0
#define cnown 1
#define ENAMES 25
#define READ 0
#define WRITE 1
#define LOSE 1
#define WIN 2
#define DRAW 3
#define MLV 0
#define Mxp 1
#define Mreborn 2
#define Mmode 3
#define Mskc 4
#define Mill 5
#define Etier 0
#define Ecnt 1
#define Ecnt2 2
#define TOTAL_SKL 3
#define ARGE 40
#define MAZOKU_SKILL 20
#define keysize 0x7ffffffe
#define Nxp 700
#define ITEMNUM 18
#define MAX_SKPT 8000
#define TO_INT 0.99999999
#define E_SKILL_NUM 12 //none +
#define savet1 "TheBattle  %s %d %d %d %ld %lld %d %d %d %d "
#define savet2 "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lld %lld %d %d %d %d %d %d %d %d %d %d\
 %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
#define fcblack SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
#define fcred SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
#define fcgreen SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
#define fcyellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
#define fcblue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
#define fcmagenta SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
#define fccyan SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
#define fcwhite SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#define fcclear SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#define COLOR_WHITE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN

//modes
//#define RELEASE
#define SHOW_PERF