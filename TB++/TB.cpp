/*start of FILEs*/
#include"TBinclude.h"

/*****************/
int main(void)
{
	/* variable */
	int a, b, c;
	short int k1 = 10;//koudou 1
	short int k2 = 10;//koudou 2
	short int ak1 = 10;//after koudou 1
	short int ak2 = 10;//after koudou 2
	short int ak = 10;
	unsigned char nsp = 0;//not escape
	char charbox[ENAMES];
	unsigned char change = 0;
	int save = 0;
	unsigned char tier = 0;
	int ent3 = 0;
	char dark = 0;
	unsigned char tag = 0;
	//unsigned char bond = 0;
	const unsigned char Eparge[] = { 10, 10, 20, 20, 20, 20, 19, 19 };
	unsigned int pen = 0;
	float per = 0;
	char spsk1 = 0;
	unsigned char deadflag = 0;
	unsigned char Mres[3] = { 1, 0, 1 };
	bool rageflg[2] = { false, false };
	unsigned char nofi = 0;//number of item
	int pain = 0;
	//	unsigned char end = 0;
	bool set_flg = false;
	char wl = 0;
	unsigned _int64 unlockingdata[2] = { 0, 0 };
	clock_t safetime, starttime;
	short int dataerrorcheck = 0;
	unsigned _int64 AIdata;
	int skill;
	unsigned _int64 firstCont = 0;
	int maxRate = 0;
	int AIdecide = 0;
	int unlocked = 0;
	int decideData[DECIDE_NUM];
	int oldLvl;
	int argePer = ARGE;
	/********************/
	/* file pointer */
	/********************/
	init();
	APS.SetAIdecide(decideData);
	APS.InitAIdecide();
	init_genrand((unsigned int)time(NULL));
	APS.SetAk(&ak1, &ak2, &ak);
	data_check();
	if (fopen_s(&LV, "LV.tb", "r") == 0) {
		fseek(LV, 11L, SEEK_SET);
		fgets(name, 7, LV);
		fscanf_s(LV, "%d%d%d%ld%lld%d%d%d%d",
			&data1[MLV], &data1[Mxp], &stgProgress, &fpo, &item, &stage, &skill, &ac, &skpt);
		pla.SetSkill(skill);
		for (a = 0; a < 4; a++) {
			for (b = 0; b < 4; b++) {
				//			fscanf_s(LV, "%lld", &logAI[a][b]);
				fscanf_s(LV, "%lld", &AIdata);
				APS.SetAIdata(a, b, AIdata);
			}
		}
		fscanf_s(LV, "%d%d%d%d%d%d%d", &rate, &dislike, &total_b, &wlpattern[0], &wlpattern[1], &s_rate, &dominated);
		for (a = 0; a < TOTAL_SKL; a++) {
			fscanf_s(LV, "%d%d", &skdata[a], &skldata[a]);
		}
		fscanf_s(LV, "%d%d%lld%lld%d%d%d", &oldver, &unlock_key, &firstCont, &calcDmg, &strea, &maxRate, &unlocked);
		for (a = 0; a < 20; a++) {
			fscanf_s(LV, "%d", &decideData[a]);
		}
		fclose(LV);
	}
	else {
		outFileError();
	}
	APS.SetAIrate(rate);
	DM.SetTotal_b(total_b);
	APS.SetFirstCont(firstCont);
	APS.SetStreak(strea);
	APS.SetMaxRate(maxRate);
	cfg.setUnlocked(unlocked);
	/* version updata */
	if (110 > oldver) {
		printf("\nゲームのバージョンが新しくなりました\n\n");
		printf("データをリセットします\n");
		remove("LV.tb");
		remove("LV2.tb");
		startWait();
		exit(1);
	}
	else if (VERSION < oldver) {
		fcred;
		printf("\a\nセーブデータとゲームデータのバージョンが違います\n");
		printf("互換性が確認できないためゲームの起動を中止します\n");
		strcpy_s(erstr, "Unavailable game version");
		errorOutput();
		startWait();
		fcclear;
		exit(1);
	}
	if (fopen_s(&LV, "LV.tb", "r") == 0) {
		if (fopen_s(&LV2, "LV2.tb", "a+") == 0) {
			fseek(LV, 18L, SEEK_SET);
			starttime = clock();
			safetime = starttime;
			a = 0;
			printf("データの整合性を確認します…\n");
			if (unlock_key == 0) {
				strcpy_s(erstr, "Unknown cipher key");
				errorOutput();
				dataerrorcheck++;
			}
			while (fscanf_s(LV, "%lld", &unlockingdata[0]) != EOF) {
				a++;
				//fscanf_s(LV, "%lld", &unlockingdata[0]);
				fscanf_s(LV2, "%lld", &unlockingdata[1]);
				unlockingdata[1] = unlockingdata[1] ^ unlock_key;
				safetime = clock();
				if (unlockingdata[0] != unlockingdata[1]) {
					strcpy_s(erstr, "Mismatch data");
					errorOutput();
					dataerrorcheck++;
				}
				if (safetime - starttime > 2000) {
					strcpy_s(erstr, "Process timed out");
					errorOutput();
					dataerrorcheck++;
					break;
				}
			}
			if (dataerrorcheck > 0)printf("エラー数:%d\n\n", dataerrorcheck);
			fclose(LV2);
		}
		else {
			outFileError();
		}
		fclose(LV);
	}
	else {
		outFileError();
	}
	if (dataerrorcheck > 0) {
		printf("エラーが発生したためデータをリセットします\n");
		remove("LV.tb");
		remove("LV2.tb");
		startWait();
		exit(1);
	}
	fclose(LV2);
	fclose(LV);
	/*処理終了*/
	if (DM.GetTotal_b() % 5 == 0 && DM.GetTotal_b() > 0) {
		if (--dislike < 0) {
			dislike = 0;
		}
	}
	if (dislike >= 4) {
		remove("LV.tb");
		remove("LV2.tb");
		printf("\a\n複数回に及ぶ不正が確認されたため、ゲームデータをリセットします\n");
		startWait();
		exit(1);
	}
	else if (dislike >= 1) {
		fcyellow;
		printf("\a\nプレイ中にゲームを閉じるのは不正行為とみなされます\n");
		fcclear;
	}
	if (stage == 0) {
		printf("浅域\n");
	}
	else if (stage == 1) {
		printf("中域\n");
	}
	else if (stage == 2) {
		printf("深域\n");
	}
	if (cfg.getUnlocked() == 1) {
		fcyellow;
		printf("Developer mode\n");
		fcclear;
	}
	if (pla.GetSkill(true) != 0) {
		printf("別のスキルを選択しますか?\n");
		printf("Yes:0 No:else\n");
		connum(&a);
	}
	else {
		a = 0;
	}
	if (a == 0) {
		pla.SetSkill(0);
		ac = 0;
		skpt = 0;
		dataSave();
	}
	if (pla.GetSkill(true) == 0) {
		printf("キャラクターの族性スキルを選択してください。\n\n");
		printf("1:\"竜族 Lv:%d\" 火炎放射を選択した場合効果が発動する。\n", skldata[0]);
		printf("効果: 相手にダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃を命中させる度に威力が上昇する。\n\n");
		printf("2:\"魔族 Lv:%d\" 特殊攻撃を命中させた際に効果が発動する。\n", skldata[1]);
		printf("効果: 当たった相手にダメージを与え能力を弱体化させるスキルを発動する。命中率はスキル発動に失敗する度に上昇する。\nこの能力発動時に命中率はリセットされる。\n\n");
		printf("3:\"機械族 Lv:%d\" 連続で攻撃を命中させると効果が発動する。\n", skldata[2]);
		printf("効果: シールドを獲得する。\nこの値は連続で攻撃を命中させる度に増加する。\n\n");
		a = 0;
		do {
			connum(&skill);
			pla.SetSkill(skill);
			switch (pla.GetSkill(true)) {
			case 1:
				printf("\aあなたは\"竜族\"を選択しました。\n");
				ac = skldata[0];
				skpt = skdata[0];
				a = 1;
				break;
			case 2:
				printf("\aあなたは\"魔族\"を選択しました。\n");
				ac = skldata[1];
				skpt = skdata[1];
				a = 1;
				break;
			case 3:
				printf("\aあなたは\"機械族\"を選択しました。\n");
				ac = skldata[2];
				skpt = skdata[2];
				a = 1;
				break;
			}
		} while (!a);
		dataSave();
	}
	itemc(READ);
	printf("\n");
	if (stage == 2) {
		randchar(24);
		timer(100);
		change = 1;
		ent3 = 20;//5.00%
	}
	else if (stgProgress < 1) {
		printf("*Ⅰ*\n");
		change = 2;
		ent3 = 100;//1.00%
	}
	else if (stgProgress < 2) {
		printf("*Ⅱ*\n");
		change = 3;
		ent3 = 90;//1.11%
	}
	else if (stgProgress < 3) {
		printf("*Ⅲ*\n");
		change = 4;
		ent3 = 80;//1.25%
	}
	else if (stgProgress < 4) {
		printf("*Ⅳ*\n");
		change = 5;
		ent3 = 70;//1.43%
	}
	else if (stgProgress < 5) {
		printf("*Ⅴ*\n");
		change = 6;
		ent3 = 60;//1.67%
	}
	else if (stgProgress < 6) {
		printf("**Ⅵ**\n");
		change = 7;
		ent3 = 50;//2.00%
	}
	else {
		printf("***FINAL***\n");
		change = 8;
		ent3 = 40;//2.50%
	}
	calLV(data1[Mxp], &data1[MLV]);
	oldLvl = data1[MLV];
	printf("\nレベル:%d\n\n", data1[MLV]);
	timer(300);
	ene.SetShieldNum(0, D_EQUAL);
	do{
		a = menu();
		switch (a) {
		case 1:
			break;

		case 2:
			shop.shopFunc();
			if (fopen_s(&LV, "LV.tb", "r") == 0) {
				fseek(LV, 17L, SEEK_SET);
				fscanf_s(LV, "%d%d%d%d%lld%d%d%d%d",
					&data1[MLV], &data1[Mxp], &stgProgress, &fpo, &item, &stage, &skill, &ac, &skpt);
				fclose(LV);
			}
			else {
				outFileError();
			}
			pla.SetSkill(skill);
			break;

		case 3:
			if (cfg.getUnlocked() == 1) {
				fcyellow;
				printf("警告:開発者モードです");
			}
			printf("\n------------------------\n");
			printf("バージョン: %d\n", VERSION);
			printf("キャラネーム: %s\n", name);
			printf("レベル: %d\n", data1[MLV]);
			printf("ステージ: %d\n", stage + 1);
			printf("進行度: %d\n", stgProgress);
			printf("ポイント: %d\n", fpo);
			printf("ランク: ");
			rank();
			if (cfg.getUnlocked() == 1)fcyellow;
			printf("区分け: %d\n", getRankDiv());
			printf("確定ランク: %s\n", rankName[APS.GetMaxAIdecideRank()]);
			printf("区分け: %d\n", APS.GetMaxAIdecideRankDiv());
			printf("スキル: %d\n", pla.GetSkill(true));
			printf("スキルレベル: %d\n", (ac + 1));
			printf("スキルポイント: %.0f%%\n", (skpt / (float)MAX_SKPT * 100.0));
			printf("アイテムデータ: %llx\n", item);
			printf("合計プレイ回数: %d\n", total_b);
			printf("平均支配率: %.2lf%%\n", (double)dominated / total_b / 10.0);
			printf("最高評価取得数: %d\n", s_rate);
			printf("勝利数: %d\n", wlpattern[0]);
			printf("勝率: %.2lf%%\n", (double)wlpattern[0] / total_b * 100.0);
			printf("与えたダメージ: %lld\n", calcDmg);
			printf("平均ダメージ: %.2lf\n", (double)calcDmg / total_b);
			printf("ストリーク: %d\n", APS.GetStreak());
			printf("切断数: %d\n", dislike);
			printf("------------------------\n\n");
			fcclear;
			break;

		case 4:
			cfg.TB_cmd_mode();
			break;

		default:
			break;
		}
	} while (a == 3);
	pla.SetHP(1000, D_EQUAL);
	pla.SetAT(50 + (data1[MLV] - 1), D_EQUAL);
	if (item > 0) {
		printf("アイテムを使用しますか? Yes=0\n");
		connum(&a);
		if (a == 0) {
			printf("どのアイテムを使用しますか?\n");
			for (a = 0; a < 11; a++) {
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
					printf("霞んだ記憶出現確率上昇!!\n");
				}
				break;
			case 4:
				if (itemn[4] - 1 >= 0) {
					data1[Mreborn] = 2;
					itemn[4]--;
					nofi = 5;
					printf("体力が0以下になったときに2回復活!!\n");
				}
				break;
			case 5:
				if (itemn[5] - 1 >= 0) {
					itemn[5]--;
					nofi = 6;
					printf("HPが50%%減少した際に10%%回復!!\n");
				}
				break;
			case 6:
				if (itemn[6] - 1 >= 0) {
					itemn[6]--;
					nofi = 7;
					printf("急所攻撃に必要なSGが1減った!!\n");
				}
				break;
			case 7:
				if (itemn[7] - 1 >= 0) {
					itemn[7]--;
					nofi = 8;
					printf("HPが20%%以下の時最大HP固定!!\n");
				}
				break;
			case 8:
				if (itemn[8] - 1 >= 0) {
					itemn[8]--;
					nofi = 9;
					printf("HPが10%%増加!!\n");
				}
				break;
			case 9:
				if (itemn[9] - 1 >= 0) {
					printf("天に向かって祈りを捧げた…\n");
					timer(700);
					if (randnum(2) == 0) {
						data1[Mreborn] = data1[Mreborn] + 1;
						printf("願いがかなったような気がした…\n");
					}
					else {
						printf("願いは何者かによってかき消された…\n");
						dark = 1;
						nofi = 10;
					}
					timer(500);
				}
				itemn[9]--;
				break;
			case 10:
				if (itemn[10] - 1 >= 0) {
					itemn[10]--;
					nofi = 11;
					APS.SetAIoutputFlg(true);
					printf("相手の行動が読めそうだ!!\n");
				}
			default:
				break;
			}
		}
	}
	itemc(WRITE);
	dataSave();
	tag = stage;
	printf("\n");
	switch (pla.GetSkill(true)) {
	case 1:
		spsk1 = 1;
		fccyan;
		printf("\"竜族\"");
		fcwhite;
		printf(" 火炎放射を選択した場合効果が発動する。\n");
		printf("相手に");
		fcgreen;
		printf("\"%s\"", sk1flaze[ac]);
		fcwhite;
		printf("ダメージを与え、自分の能力が弱体化する。\nこの能力は1回の対戦で1回使え、攻撃を命中させる度に威力が上昇する。\n");
//		SG[0][0] = 10;
		SGM.SetMaxSG(10, Pla);
		break;
	case 2:
		fccyan;
		printf("\"魔族\"");
		fcwhite;
		printf(" 特殊攻撃を命中させた際に効果が発動する。\n");
		printf("当たった相手に");
		fcgreen;
		printf("\"%s\"", sk1flaze[ac]);
		fcwhite;
		printf("ダメージを与え能力を弱体化するスキルを発動する。命中率はスキル発動に失敗する度に%d%%上昇する。\nこの能力発動時に命中率はリセットされる。\n", MAZOKU_SKILL);
//		SG[0][0] = 10;
		SGM.SetMaxSG(10, Pla);
		break;
	case 3:
		fccyan;
		printf("\"機械族\"");
		fcwhite;
		printf(" 連続で攻撃を命中させると効果が発動する。\n");
		printf("1ポイントのシールドを獲得する。\nこの値は連続で攻撃を命中させると1ポイントずつ増加し、最大");
		fcgreen;
		printf("\"%d\"", (ac + 1));
		fcwhite;
		printf("増加する。\n");
//		SG[0][0] = 10;
		SGM.SetMaxSG(10, Pla);
		break;
	default:
		break;
	};
	fcclear;
//	if (nofi == 7)SG[0][0]--;
	if (nofi == 7)SGM.SetMaxSG(SGM.GetMaxSG(Pla) - 1, Pla);
	printf("\n");
	liker();

	data1[MLV] = 1;
	if (data1[Mmode] == 1) {
		pla.SetShield(false);
		pla.SetShieldNum(10000, D_EQUAL);
	}
	calLV(data1[Mxp], &data1[MLV]);
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	printf("%sのプロフィール\n", name);
	printf("HP:%d  AT:%d  LV:%d\n", pla.GetHP(), pla.GetAT(), data1[MLV]);
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	startWait();
	printf("\r");
	t = time(NULL);
	localtime_s(&tm, &t);
	if ((dark == 1) && (randnum(10) == 0)) {
		printf("\a");
		randchar(24);
		printf("\n");
		ene.SetHP(1000, D_EQUAL);
		ene.SetAT(1, D_EQUAL);
		ene.SetPlusAT(20, D_EQUAL);
		rageHP[1][0] = 1000;
		ene.SetSkill(6);
		ene.SetDmgPer(0, D_EQUAL);
		ene.SetCritper(0, D_EQUAL);
		EM.SetEI(9);
		pla.SetCritper(850, D_PLUS);
//		SG[1][0] = 4;
		SGM.SetMaxSG(5, Ene);
	}
	else if ((randnum(20) == 0) && ((tm.tm_hour >= 21) && (tm.tm_hour <= 4))) {
		randchar(24);
		printf("\a\n");
		ene.SetHP(2000, D_EQUAL);
		ene.SetAT(60, D_EQUAL);
		ene.SetShield(true);
		rageHP[1][0] = 2000;
		ene.SetSkill(10);
		EM.SetEI(10);
//		SG[1][0] = 4;
		SGM.SetMaxSG(4, Ene);
	}
	else if (randnum(ent3) == 0) {//霞んだ記憶
		printf("\a_/_/BOSS_/_/\n");
		ene.SetHP(1, D_EQUAL);
		ene.SetAT(1, D_EQUAL);
		ene.SetShieldNum(10000, D_EQUAL);
		rageHP[1][0] = 2000;
		EM.SetEI(8);
		ene.SetCritper(150, D_PLUS);
//		SG[1][0] = 16;
		SGM.SetMaxSG(16, Ene);
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
			switch (change) {
			case 0://ゾンビ
				ene.SetHP(900, D_EQUAL);
				ene.SetAT(50, D_EQUAL);
//				SG[1][0] = 11;
				if (stgProgress >= 1)ene.SetSkill(3);
				SGM.SetMaxSG(11, Ene);
				break;

			case 1://狂犬
				ene.SetHP(800, D_EQUAL);
				ene.SetAT(60, D_EQUAL);
//				SG[1][0] = 13;
				if (stgProgress >= 1)ene.SetSkill(3);
				SGM.SetMaxSG(13, Ene);
				break;

			case 2://ゴースト
				ene.SetHP(pla.GetHP(), D_EQUAL);
				ene.SetAT(50, D_EQUAL);
				ene.SetShieldNum(250, D_EQUAL);
				rageHP[1][0] = ene.GetHP() + ene.GetShieldNum();
				if (stgProgress >= 2)ene.SetSkill(7);
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;

			case 3://裏切者
				ene.SetHP(1300, D_EQUAL);
				ene.SetAT(50, D_EQUAL);
				if (stgProgress >= 3)ene.SetSkill(1);
//				SG[1][0] = 11;
				SGM.SetMaxSG(11, Ene);
				break;

			case 4://記憶の模倣
				ene.SetHP(pla.GetHP(), D_EQUAL);
				ene.SetAT(pla.GetAT(), D_EQUAL);
				ene.SetSkill(randnum(2) + 1);
//				SG[1][0] = 10;
				SGM.SetMaxSG(10, Ene);
				break;

			case 5://悪夢
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(80, D_EQUAL);
				ene.SetPlusAT(2, D_EQUAL);
				if (stgProgress >= 5)ene.SetSkill(3);
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;

			case 6://邪神
				printf("\a_/_/Boss_/_/");
				ene.SetHP(1400, D_EQUAL);
				ene.SetAT(90, D_EQUAL);
//				SG[1][0] = 13;
				SGM.SetMaxSG(13, Ene);
				break;

			case 7://邪神Ⅱ
				printf("\a_/_/Boss_/_/");
				ene.SetHP(1600, D_EQUAL);
				ene.SetAT(90, D_EQUAL);
				ene.SetSkill(1);
//				SG[1][0] = 15;
				SGM.SetMaxSG(15, Ene);
				break;
			}
			break;
		case 1:
			switch (change) {
			case 0://フロート
				ene.SetHP(pla.GetHP() / 2, D_EQUAL);
				ene.SetAT(pla.GetAT(), D_EQUAL);
				ene.SetSkill(5);
				ene.SetShieldNum(pla.GetHP() / 2 + pla.GetHP() % 2, D_EQUAL);
				rageHP[1][0] = ene.GetHP() * 2;
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;
			case 1://ナル
				ene.SetHP(1200, D_EQUAL);
				ene.SetAT(70, D_EQUAL);
				ene.SetSkill(2);
//				SG[1][0] = 9;
				SGM.SetMaxSG(9, Ene);
				break;
			case 2://実験体Ⅰ
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(90, D_EQUAL);
				ene.SetSkill(1);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			case 3://あの世の使者
				ene.SetHP(1300, D_EQUAL);
				ene.SetAT(80, D_EQUAL);
				ene.SetSkill(3);
//				SG[1][0] = 13;
				SGM.SetMaxSG(13, Ene);
				break;
			case 4://アルジオロジー
				ene.SetHP(1600, D_EQUAL);
				ene.SetAT(60, D_EQUAL);
				ene.SetSkill(8);
//				SG[1][0] = 16;
				SGM.SetMaxSG(16, Ene);
				break;
			case 5://ボイド
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(20, D_EQUAL);
				ene.SetShieldNum(1200, D_EQUAL);
				ene.SetSkill(4);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			case 6://フィニート
				printf("\a_/_/Boss_/_/");
				ene.SetHP(2000, D_EQUAL);
				ene.SetAT(100, D_EQUAL);
				ene.SetSkill(2);
//				SG[1][0] = 17;
				SGM.SetMaxSG(17, Ene);
				break;
			case 7://エル
				printf("\a_/_/Boss_/_/");
				ene.SetHP(2000, D_EQUAL);
				ene.SetAT(10, D_EQUAL);
				ene.SetSkill(7);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			}
			break;

		case 3://偽りの希望
			switch (change) {
			case 0:
				printf("\a_/_/Boss_/_/");
				ene.SetHP(2000, D_EQUAL);
				ene.SetAT(80, D_EQUAL);
				ene.SetSkill(9);
				data2[Ecnt] = 1;
				data2[Ecnt2] = 1;
//				SG[1][0] = 15;
				SGM.SetMaxSG(15, Ene);
				break;
			}
			break;
		}
		EM.SetEI(change);
	}
	EM.GetEn(tag, charbox);
	timer(100);
	pla.SetDmgBoost(true);
	pla.SetShield(true);
	ene.SetDmgBoost(true);
	ene.SetShield(true);
	pla.CalcStrength();
	ene.CalcStrength();
	if (APS.GetAIrate() < 1000) {
		pla.SetRevenge(true);
		ene.SetDmgBoost(false);
		ene.SetShield(false);
		fcyellow;
		printf("\n難易度調整");
		fcwhite;
		printf("\nプレイヤー\n");
		fcyellow;
		printf("圏外ランクのため全ての能力を有効\n\n");
		fcclear;

	}
	printf("\n_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	printf("敵データ\nName:%s HP:%d  AT:%d\n", charbox, ene.GetHP(), ene.GetAT());
	printf("スキル:%s\n", eskname[ene.GetSkill(false)]);
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n");
	fccyan;
	printf("\"%s\" ", eskname[ene.GetSkill(false)]);
	fcwhite;
	printf("%s\n\n", eskchips[ene.GetSkill(false)]);
	fcclear;
	printf("結果予想: %s\n\n", expect[pla.ExpectResult()]);
#ifdef RELEASE
	dislike++;
#endif
	dataSave();//途中セーブ
#ifdef RELEASE
	dislike--;
#endif
	timer(400);
	printf("対戦を始めます\n");
	startWait();
	printf("\n");
	for (a = 0; a < 12; a++) {
		addition[a] = 0;
	}
	/*アイテム処理*/
	if (nofi == 1)addition[10] -= 10;
	if (nofi == 3)addition[6] += 20;
	if (nofi == 9)addition[8] += 10;
	if ((stage == 0) && (EM.GetEi() == 7)) {
		addition[7] = -50;
	}
	if (EM.GetEi() == 9) {
		addition[7] = -100;
	}
		datalimit(0);
		timer(700);
		while (1) {
		if (errno != 0) {
			int erNum = errno;
			strerror_s(erstr, erNum);
			printf("Error Num: %d\n", erNum);
			errorOutput();
			exit(1);
		}
		/*if (end == 1) {
			fc_lyellow;
		}
		else*/
		SetColor();
		/* 霞んだ記憶処理 */
		if ((EM.GetEi() == 8) && (data2[Etier] != tier)) {
			fcyellow;
			if (data2[Etier] == 1) {//ティア2
				ene.SetHP(1000, D_EQUAL);
				ene.SetMaxHP(ene.GetHP(), D_EQUAL);
				ene.SetAT(60, D_EQUAL);
				ene.SetShieldNum(1000, D_EQUAL);
				printf("\a霞んだ記憶は徐々に力を付けている…\n");
			}
			else if (data2[Etier] == 2) {//ティア3
				ene.SetShield(true);
				printf("\a霞んだ記憶にシールド再生能力が付与された\n");
			}
			else if (data2[Etier] == 3) {//ティア4
				ene.SetDmgBoost(true);
				printf("\a霞んだ記憶にダメージブーストが付与された\n");
			}
			else if (data2[Etier] == 4) {//ティア5
				pla.SetSkillFlg(false);
				printf("\aスキルが無効化された。\n");
			}
			tier = data2[Etier];
			SetColor();
		}
		if ((data2[Etier] >= 5) && (EM.GetEi() == 8)) {
			data2[Etier] = 5;
			ene.SetHP(10, D_PLUS);
			ene.AppHPlimit();
			if (ene.GetHpPer() == 1.0) {
				ene.SetPlusAT(5, D_EQUAL);
				fcred;
				printf("霞んだ記憶はその身に絶大なパワーを宿している…\n");
				SetColor();
			}
			else {
				ene.SetPlusAT(0, D_EQUAL);
			}
		}
		printf("\n");
		//		if (end == 1)printf("<バグ発生>\n");
		printf("ターン:%d\n", T.GetTurn());
		printf("_/_/_/_/_/%sのステータス HP:%d[%d](%.1lf%%) AT:%d", name, pla.GetHP(), pla.GetShieldNum(), (double)pla.GetHpPer() * 100.0, pla.GetAT());
		if (pla.GetPlusAT() > 0) {
			fcred;
			printf("+%d", pla.GetPlusAT() * PLUSNUM);
			SetColor();
		}
		if (pla.GetDmgBoost())printf(" [△]");
		if (pla.GetShield())printf(" [□]");
		if (pla.GetRevenge())printf(" [▽]");
		printf(" _/_/_/_/_/");
		printf("\n_/_/_/_/_/%sのステータス HP:%d[%d](%.1lf%%) AT:%d", charbox, ene.GetHP(), ene.GetShieldNum(), (double)ene.GetHpPer() * 100.0, ene.GetAT());
		if (ene.GetPlusAT() > 0) {
			fcred;
			printf("+%d", ene.GetPlusAT() * PLUSNUM);
			SetColor();
		}
		if (ene.GetDmgBoost())printf(" [△]");
		if (ene.GetShield())printf(" [□]");
		if (ene.GetRevenge())printf(" [▽]");
		if (EM.GetEi() == 8) {
			if (data2[Etier] >= 5) {
				printf(" Tier:5");
			}
			else {
				printf(" Tier:%d", data2[Etier] + 1);
			}
		}
		printf(" _/_/_/_/_/\n\n");
		/*if (end == 0)*/printf("\t%sダメージ倍率:\t%.0lf%%(+%.0lf%%)\t敵ダメージ倍率:\t%.0lf%%(+%.0lf%%)\n", name, floor(pla.GetDmgPer()),floor(pla.GetDmgPerInc()), floor(ene.GetDmgPer()), floor(ene.GetDmgPerInc()));
		printf("\t      急所倍率:\t\t%d%%\t\t敵急所倍率:\t%d%%\n", pla.GetCritPer(), ene.GetCritPer());
		printf("\t      回復率:\t\t%.0lf%%\t\t回復率:\t\t%.0lf%%\n", floor(pla.GetHealPer()), floor(ene.GetHealPer()));
		printf("\t      正気度:\t\t%s\t\t正気度:\t\t%s\n\n", sensesFlavor[(int)(pla.GetSenses() + TO_INT)], sensesFlavor[(int)(ene.GetSenses() + TO_INT)]);
		printf("%s:", name);
		pla.ResetDmgPerBef();
		ene.ResetDmgPerBef();
		for (a = 1; a <= 10; a++) {
			if (((pla.GetShieldNum() / (float)pla.GetMaxHP()) * 10.0 >= 11 - a) && (pla.GetShieldNum() > 0)) {
				fccyan;
				printf("＃");
				SetColor();
			}
			else if (pla.GetHpPer() * 10.0 >= a) {
				printf("■");
			}
			else {
				printf("□");
			}
		}
		SetColor();
		printf("  %s:", charbox);
		for (a = 1; a <= 10; a++) {
			if (((ene.GetShieldNum() / (float)ene.GetMaxHP()) * 10.0 >= 11 - a) && (ene.GetShieldNum() > 0)) {
				fccyan;
				printf("＃");
				SetColor();
			}
			else if (ene.GetHpPer() * 10.0 >= a) {
				printf("■");
			}
			else {
				printf("□");
			}
		}
		SetColor();
		printf("\n");
		printf("    SG:");
		if (SGM.GerPer(Pla) >= 1.0)fcclear;
		for (a = 1; a <= 10; a++) {
			if ((SGM.GerPer(Pla) * 100) >= ((double)a * 10))printf("●");
			else printf("〇");
		}
		SetColor();
		if (SGM.GerPer(Ene) >= 1.0)fcclear;
		for (a = 0; a < strlen(charbox); a++) {
			printf(" ");
		}
		printf("SG:");
		for (a = 1; a <= 10; a++) {
			if ((SGM.GerPer(Ene) * 100) >= ((double)a * 10))printf("●");
			else printf("〇");
		}
		SetColor();
		printf("\n");
		/* 行動選択 */
		if (T.GetTurn() > 0 && stgProgress > 0) {
//			k2 = AIpat(ak1 - 1, ak2);
			k2 = APS.AIpat();
		}
		else {
			while (ak2 == k2) {
				k2 = randnum(4);
			}
		}
		do {
			printf("行動選択\n通常攻撃");
			if (!SGM.GetSf(Pla)) {
				printf("(%.0lf)", pla.CalcAT() * NOMAL_MAGN * (ene.GetDmgPer() / 100.0));
			}
			else {
				fcyellow;
				printf("(%.0lf)", pla.CalcAT() * NOMAL_MAGN * (ene.GetDmgPer() / 100.0) * (ene.GetCritPer() / 100.0));
				SetColor();
			}
			printf(" :1 特殊攻撃");
			if (!SGM.GetSf(Pla)) {
				printf("(%.0lf)", pla.CalcAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0));
			}
			else {
				fcyellow;
				printf("(%.0lf)", pla.CalcAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0) * (ene.GetCritPer() / 100.0));
				SetColor();
			}
			printf(" : 2 回避行動");
			if (!nsp) {
				printf("(%.0lf%%)", pla.GetAvoidPer());
			}
			else {
				printf("(0%%)");
			}
			printf(" : 3 特殊攻撃壁");
			printf("(%.0lf)", ene.GetAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0));
			printf(" : 4");
			if ((pla.GetSkill(false) == 1) && (spsk1 > 0)) {
				printf(" 火炎放射:5(+%d)", data1[Mskc]);
			}
			printf("\n");
			connum_int16(&k1);
			if ((k1 == 5) && (pla.GetSkill(false) == 1) && (spsk1 > 0)) {
				break;
			}
		} while ((k1 == ak1) || (k1 < 1) || (k1 > 4));
		if (k1 == 5) {
			printf("%sは火炎放射を使った!!\n", name);
			float dmgcntr = 0.0;
			for (a = 1; a <= data1[Mskc]; a++) {
				dmgcntr = (float)(dmgcntr + (((ac * 0.1) + 0.20) / a) * pla.GetAT());
			}
			ene.SetDmg((int)(dmgcntr), D_EQUAL);
			spsk1 = -1;
			data1[Mskc] = -1;
			k1 = 2;
		}
		pla.PatternPlus(k1 - 1);
		ene.PatternPlus(k2);
		/*
		if (randnum(100) <= (99 - dislike) / 2) {
			printf("プレイヤーと%sは息がぴったりだ!!\n", name);
			c14;
			bond = 1;
		}
		*/
		ak = k1;
		if (T.GetTurn() > 0) {
//			SaveAI(ak1 - 1, ak2);
			APS.SaveAI();
		}
		ak1 = k1;
		ak2 = k2;
/*		if (SG[0][1] == SG[0][0]) {
			chardata[0].Fs = true;
		}
		if (SG[1][1] == SG[1][0]) {
			chardata[1].Fs = true;
		}*/
		/******************************************************************************************************************/
		if ((k1 == 1) && (k2 == 0)) {//通常　通常
			ene.Atk();
			pla.Atk();
			sk1cp;
			printf("%sの通常攻撃!! %sの通常攻撃!!\n", name, charbox);
			pla.Decr();
			ene.Decr();
			Perform(2);
			c23ptc();
		}
		else if ((k1 == 1) && (k2 == 1)) {//通常　特殊
			ene.SpAtk();
			pla.Boost();
			ent;
			enttier;
			printf("%sの通常攻撃!! しかし%sは距離を取っている…\n%sの特殊攻撃!!\n", name, charbox, charbox);
			ene.Decr();
			decc23();
		}
		else if ((k1 == 1) && (k2 == 2)) {//通常　回避
			if (randnum(100) < ene.GetAvoidPer()) {
				ene.Heal();
				if (ene.GetDmg() < 0)ene.SetDmg(ene.GetDmg() / 2, D_EQUAL);
				ene.Shield();
				pla.Boost();
				printf("%sの通常攻撃!! しかし%sの回避行動によって回避された。\n", name, charbox);
				decc23();
				Perform(20);
			}
			else {
				pla.Atk();
				sk1cp;
				printf("%sの通常攻撃!! %sは回避に失敗した!!\n", name, charbox);
				pla.Decr();
				Perform(2);
				Perform(21);
				c23ptc();
			}
		}
		else if ((k1 == 1) && (k2 == 3)) {//通常　壁
			pla.Atk();
			sk1cp;
			printf("%sの通常攻撃!! %sは攻撃反射に失敗した!!\n", name, charbox);
			pla.Decr();
			Perform(2);
			c23ptc();
		}
		/******************************************************************************************************************/
		else if ((k1 == 2) && (k2 == 0)) {//特殊　通常
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", charbox, name);
				pla.Weak();
				pla.Decr();
				spsk1 = 0;
			}
			else {
				pla.SpAtk();
				if ((pla.GetSkill(false) == 2)) {
					sk2();
				}
				ene.Boost();
				sk1cp;
				printf("%sの特殊攻撃!! %sの攻撃は距離があって届かない!!\n", name, charbox);
				pla.Decr();
				Perform(2);
				c23ptc();
			}
		}
		else if ((k1 == 2) && (k2 == 1)) {//特殊　特殊
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", charbox, name);
				pla.Weak();
				pla.Decr();
				spsk1 = 0;
			}
			else {
				ene.SpAtk();
				pla.SpAtk();
				if ((pla.GetSkill(false) == 2)) {
					sk2();
				}
				ent;
				enttier;
				sk1cp;
				printf("%sの特殊攻撃!! %sの特殊攻撃!!\n", name, charbox);
				pla.Decr();
				ene.Decr();
				Perform(2);
				c23ptc();
			}
		}
		else if ((k1 == 2) && (k2 == 2)) {//特殊　回避
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", charbox, name);
				pla.Weak();
				pla.Decr();
				spsk1 = 0;
			}
			else {
				if (randnum(100) < ene.GetAvoidPer() / 2) {
					ene.Heal();
					ene.Shield();
					if (ene.GetDmg() < 0)ene.SetDmg(ene.GetDmg() / 3, D_EQUAL);
					pla.Boost();
					printf("%sの特殊攻撃!! しかし%sの回避行動によって回避された。\n", name, charbox);
					decc23();
					Perform(20);
				}
				else {
					pla.SpAtk();
					if ((pla.GetSkill(false) == 2)) {
						sk2();
					}
					sk1cp;
					printf("%sの特殊攻撃!! %sは回避に失敗した!!\n", name, charbox);
					pla.Decr();
					Perform(2);
					Perform(21);
					c23ptc();
				}
			}
		}
		else if ((k1 == 2) && (k2 == 3)) {//特殊　壁
			if (spsk1 < 0) {
				printf("%sは%sの灼熱の炎で燃やされている!!\n", charbox, name);
				pla.Weak();
				pla.Decr();
				spsk1 = 0;
			}
			else {
				ene.Ref();
				if (data1[Mill] != 1)pla.Boost();
				painin();
				printf("%sの特殊攻撃!! しかし%sの特殊攻撃壁によって反射された。\n", name, charbox);
				decc23();
			}
		}
		/******************************************************************************************************************/
		else if ((k1 == 3) && (k2 == 0)) {//回避　通常
			if (randnum(100) < (pla.GetAvoidPer()) && !nsp) {
				pla.Shield();
				pla.Heal();
				if (pla.GetDmg() < 0)pla.SetDmg(pla.GetDmg() / 2, D_EQUAL);
				ene.Boost();
				espain();
				printf("%sの通常攻撃!! しかし%sは攻撃を回避した!!\n", charbox, name);
				Perform(3);
				Perform(24);
			}
			else {
				ene.Atk();
				printf("%sの通常攻撃!! %sは回避に失敗した。\n", charbox, name);
				ene.Decr();
			}
		}
		else if ((k1 == 3) && (k2 == 1)) {//回避　特殊
			ent;
			enttier;
			if (randnum(100) < pla.GetAvoidPer() / 2 && !nsp) {
				pla.Shield();
				pla.Heal();
				if (pla.GetDmg() < 0)pla.SetDmg(pla.GetDmg() / 3, D_EQUAL);
				ene.Boost();
				espain();
				printf("%sの特殊攻撃!! %sは回避した!!\n", charbox, name);
				Perform(3);
				Perform(24);
			}
			else {
				ene.SpAtk();
				printf("%sの特殊攻撃!! %sは回避に失敗してしまった。\n", charbox, name);
				ene.Decr();
			}
		}
		else if ((k1 == 3) && (k2 == 2)) {//回避　回避
			pla.Heal();
			ene.Heal();
			pla.Shield();
			ene.Shield();
			espain();
			printf("%sと%sの回避行動… お互いに睨みあっている。\n", name, charbox);
			Perform(24);
		}
		else if ((k1 == 3) && (k2 == 3)) {//回避　壁
			pla.Shield();
			pla.Heal();
			painin();
			printf("%sの回避行動!! %sは特殊反射の構えに入っている。\n", name, charbox);
			Perform(24);
		}
		/******************************************************************************************************************/
		else if ((k1 == 4) && (k2 == 0)) {//壁　通常
			ene.Atk();
			printf("%sは特殊反射の構えに入っている… %sの通常攻撃!!\n", name, charbox);
			ene.Decr();
		}
		else if ((k1 == 4) && (k2 == 1)) {//壁　特殊
			pla.Ref();
			ene.Boost();
			printf("%sの特殊攻撃!! しかし%sの特殊反射壁によって反射した!!\n", charbox, name);
			Perform(4);
		}
		else if ((k1 == 4) && (k2 == 2)) {//壁　回避
			ene.Heal();
			ene.Shield();
			printf("%sは特殊反射の構えに入っている… %sは回避運動をしている…\n", name, charbox);
		}
		else if ((k1 == 4) && (k2 == 3)) {//壁　壁
			painin();
			printf("お互いに睨みあっている\n");
		}
		/******************************************************************************************************************/
		if ((T.TurnRemains()) <= 5 && (T.TurnRemains() >= 0)) {
			printf("\n\aセットまであと%dターン\n\n", T.TurnRemains());
		}
		if (T.TurnRemains() == 0) {
			printf("\nセット!!\n");
			set_flg = true;
		}
		if ((ak1 == 1) || (ak1 == 2))pen++; else pen = 0;
		if (pen > 4) { 
			Perform(25);
		}
		//		if ((T.GetTurn() <= 0) && (end == 1))end = 0, dmg[0] = 100000000, dmg[1] = 100000000, totalpo = totalpo + 3000, chardata[0].Dmgper = 1000, chardata[1].Dmgper = 1000, turn = 75;
		/*敵スキル処理*/
		switch (ene.GetSkill(false)) {
		case 0:
			break;
		case 1:
			if (ene.GetDmg() > 0) {
				ene.SetPlusAT(1, D_PLUS);
				if (ene.GetPlusAT() > 10) {
					ene.SetPlusAT(10, D_EQUAL);
				}
				ene.SetDmgPer(2, D_PLUS);
			}
			break;
		case 2:
			timer(1);
			if ((pla.GetDmg() > 0) && ((ak2 == 0) || (ak2 == 1))) {
				if (randnum(2) == 0 || data2[Ecnt] == 0) {
					data2[Ecnt]++;
					printf("%sは力をためている…\n", charbox);
				}
				else {
					for (a = 0, b = ene.GetAT(); a < data2[Ecnt]; a++) {
						b = (int)(b * 1.5);
					}
					data2[Ecnt] = 0;
					pla.SetDmg(ene.Dmgd(b), D_PLUS);
					printf("%sは力を開放した。\n", charbox);

				}
			}
			break;
		case 3:
			break;
		case 4:
			timer(1);
			if (pla.GetDmg() > 0) {
				if (randnum(100) <= data2[Ecnt]) {
					Mres[0] = 0;
					pla.SetDmg(pla.GetHP() + pla.GetShieldNum(), D_EQUAL);
					printf("%sのスキルにより%sは即死した。\n", charbox, name);
				}
				else {
					data2[Ecnt]++;
					printf("闇の霧の濃度:%d%%\n", data2[Ecnt]);
				}
			}
			break;
		case 5:
			break;
		case 6:
			ene.SetPlusAT(1, D_PLUS);
			ene.SetCritper(2, D_PLUS);
			break;
		case 7:
			if (ene.GetDmg() > 0) {
				ene.SetDmgPer(1, D_MINUS);
			}
			break;
		case 8:
			if ((((ak2 == 0) || (ak2 == 1)) && (pla.GetDmg() > 0))) {
				if (randnum(100) <= argePer) {
					if ((data1[Mill] != 0) && (data1[Mill] != 4)) {
						data1[Mill] = 4;
						nsp = 1;
						illcnt = 2;
						printf("錯乱症が発症した。\n");
					}
					else if (data1[Mill] != 4) {
						timer(1);
						while ((a = randnum(3)) == (data1[Mill] - 1));
						if (a == 0) {
							illcnt = 3;
							data1[Mill] = 1;
							printf("衰弱症が発症した。\n");
						}
						else if (a == 1) {
							illcnt = 2;
							data1[Mill] = 2;
							printf("吐血症が発症した。\n");
						}
						else if (a == 2) {
							illcnt = 4;
							data1[Mill] = 3;
							printf("壊死症が発症した。\n");
						}
					}
					argePer -= 2;
				}
			}
			if (data1[Mill] == 1) {
				printf("力が衰えてゆく…\n");
				pla.SetAT(2, D_MINUS);
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					printf("衰弱症が完治した!!\n");
				}
			}
			else if (data1[Mill] == 2) {
				printf("体力が衰えてゆく…\n");
				pla.SetDmg((int)(pla.GetHP() * 0.1), D_PLUS);
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					printf("吐血症が完治した!!\n");
				}
			}
			else if (data1[Mill] == 3) {
				printf("思うように体が動かない…\n");
				nsp = 1;
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					nsp = 0;
					printf("壊死症が完治した。\n");
				}
			}
			else if (data1[Mill] == 4) {
				randchar(36);
				printf("\n");
				nsp = 1;
				if ((pla.GetDmg() >= 0) && (ene.GetDmg() >= 0)) {
					pla.SetDmg(pla.GetDmg() + ene.GetDmg(), D_EQUAL);
					ene.SetDmg(0, D_EQUAL);
				}
				else if ((pla.GetDmg() < 0) && (ene.GetDmg() <= 0)) {
					ene.SetDmg(pla.GetDmg() + ene.GetDmg(), D_EQUAL);
					pla.SetDmg(0, D_EQUAL);
				}
				else if ((pla.GetDmg() <= 0) && (ene.GetDmg() >= 0)) {
					a = pla.GetDmg();
					pla.SetDmg(ene.GetDmg(), D_EQUAL);
					ene.SetDmg(a, D_EQUAL);
				}
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					nsp = 0;
					printf("錯乱症が完治した。\n");
				}
			}
			break;
		case 9:
			ene.SetShieldNum(10, D_PLUS);
			break;
		case 10:
			break;
		case 11:
			if (randnum((int)(pla.GetHpPer() * 200.0)) == 0 && pla.GetDmg() > 0) {
				printf("凄まじい衝撃波は%sを吹き飛ばした。\n", name);
				Mres[0] = 0;
				pla.SetDmg(pla.GetHP() + pla.GetShieldNum(), D_EQUAL);
			}
			break;
		}
		pla.Revenge();
		ene.Revenge();
		/*if (end != 1)*/T.PlusTurn();//ターン増加
//		if (end == 1)turn--;//ターン減少
		if (pla.GetDmg() > 0) {
			DM.SetData(2);
		}
		if (ene.GetDmg() > 0) {
			DM.SetData(1);
		}
		DM.CalcData();
		if (pla.GetDmg() > 0) {
			rageHP[0][1] = rageHP[0][1] + pla.GetDmg();
		}
		if (ene.GetDmg() > 0) {
			rageHP[1][1] = rageHP[1][1] + ene.GetDmg();
		}
		if ((SGM.GetSf(Ene)) && ((ak2 == 0) || (ak2 == 1)) && (pla.GetDmg() > 0)) {
			fcred;
			printf("\a%sは怯んだ!!\n", name);
			SetColor();
			pla.Crit();
			SGM.ClearSF(Ene);
		}
		else if ((SGM.GetSf(Ene)) && ((ak2 == 0) || (ak2 == 1))) {
			SGM.ClearSF(Ene);
		}
		if ((SGM.GetSf(Pla)) && ((ak1 == 1) || (ak1 == 2)) && (ene.GetDmg() > 0)) {
			fcred;
			printf("\a%sは怯んだ!!\n", charbox);
			SetColor();
			ene.Crit();
			Perform(5);
			pain = 0;
			SGM.ClearSF(Pla);
		}
		else if ((SGM.GetSf(Pla)) && ((ak1 == 1) || (ak1 == 2))) {
			SGM.ClearSF(Pla);
		}
		if ((ene.GetSkill(false) == 10) && (ene.GetDmg() > 0))pain = pain + (int)(ene.GetDmg() * 0.1);
		if (slowpain == 1)pla.SetDmg(pain, D_PLUS), printf("苦しみが%sを襲う!!\n", name);
		if (slowpain == 2)slowpain = 1;
		if ((ene.GetSkill(false) == 5) && (ene.GetDmg() > 50)) {
			printf("敵のスキルによりダメージが吸収された!!\n");
			ene.SetDmg(50, D_EQUAL);
			data2[Ecnt]++;
		}
		pla.CalDmg();
		ene.CalDmg();
		if (ene.GetTotalDmg() >= 200) {
			Perform(18);
		}
		else if (ene.GetTotalDmg() >= 100) {
			Perform(17);
		}
		if (pla.GetTotalDmg() > 0) {
			printf("%sに", name);
			if (pla.GetTotalDmg() >= 200) {
				fcred;
			}
			else if (pla.GetTotalDmg() >= 100) {
				fcyellow;
			}
			printf("%d", pla.GetTotalDmg());
			SetColor();
			printf("ダメージ!!");
		}
		else if (pla.GetTotalDmg() < 0) {
			printf("%sは", name);
			fccyan;
			printf("%d", pla.GetTotalDmg() * -1);
			SetColor();
			printf("回復!!");
		}
		printf("\n");
		if (ene.GetTotalDmg() > 0) {
			printf("%sに", charbox);
			if (ene.GetTotalDmg() >= 200) {
				fcred;
			}
			else if (ene.GetTotalDmg() >= 100) {
				fcyellow;
			}
			printf("%d", ene.GetTotalDmg());
			SetColor();
			printf("ダメージ!!");
		}
		else if (ene.GetTotalDmg() < 0) {
			printf("%sは", charbox);
			fccyan;
			printf("%d", ene.GetTotalDmg() * -1);
			SetColor();
			printf("回復!!");
		}
		printf("\n");
		/*****************************************ダメージ処理************************************************/
		pla.Dmg();
		ene.Dmg();
		if (ene.GetDmg() > 0) {
			calcDmg += ene.GetTotalDmg();
		}
		pla.ResetDmg();
		ene.ResetDmg();
		if (pla.GetHpPer() == 1.0) { Perform(6); }
		/*********************************************end****************************************************/
		if ((nofi == 6) && ((pla.GetHpPer()) <= 0.5)) {
			pla.SetHP((int)(pla.GetMaxHP() * 0.1), D_PLUS);
			nofi = 0;
			printf("アイテムの能力でHPを回復!!\n");
		}
		if ((nofi == 8) && ((pla.GetHpPer()) <= 0.2)) {
			pla.SetMaxHP(pla.GetHP(), D_EQUAL);
			nofi = 0;
			printf("アイテムの能力で最大HPを固定!!\n");
		}
		if (pla.GetHP() + pla.GetShieldNum() < (ene.GetAT() * pla.GetDmgPer() / 100)) { Perform(7); }
		if ((rageHP[0][0] <= rageHP[0][1]) && rageflg[0] == false && pla.GetHP() > 0) {
			ene.SetDmgPer(50, D_PLUS);
			ene.SetCritper(25, D_PLUS);
			rageflg[0] = true;
			rageflg[1] = true;
			printf("\a%sは激怒した!!\n", name);
			Perform(10);
		}
		if ((rageHP[1][0] <= rageHP[1][1]) && rageflg[1] == false && ene.GetHP() > 0) {
			pla.SetDmgPer(50, D_PLUS);
			pla.SetCritper(25, D_PLUS);
			rageflg[0] = true;
			rageflg[1] = true;
			printf("\a%sは激怒した!!\n", charbox);
		}
		if ((ene.GetSkill(false) == 3) && (ene.GetHP() <= ene.GetMaxHP() / 2)) {
			ene.SetAT(ene.GetAT() / 2, D_PLUS);
			ene.SetMaxHP(ene.GetHP(), D_EQUAL);
			printf("%sは分裂した!!\n", charbox);
		}
		datalimit(1);
		if (reborneflg == 1)reborneflg = 0;
		if ((pla.GetHP() <= 0) && (data1[Mreborn] > 0)) {
			printf("\a%sは復活した!!\n", name);
			pla.SetHP(1, D_EQUAL);
			data1[Mreborn] = data1[Mreborn] - 1;
			reborneflg = 1;
		}
		//bond = 0;
		/*		if (((chardata[0].Dmgper + spdp <= 0) || (chardata[1].Dmgper <= 0)) && end != 1) {
					end = 1;
					turn = turn / 4;
					printf("\aバグ発生!!\n");
				}*/
		pla.PlusAvoidCnt();
		ene.PlusAvoidCnt();
		SGM.PlusNowSG(1, Pla);
		SGM.PlusNowSG(1, Ene);
		timer(450);
		/********************************************************************/
		/********************************************************************/
		if ((pla.GetHP() <= 0 || ene.GetHP() <= 0) || set_flg) {
			fcclear;
			if (EM.GetEi() == 9) {
				dislike = dislike - 1;
				randchar(1000);
				dataSave();
				exit(1);
			}
			if (pla.GetHP() <= 0 && ene.GetHP() > 0) {
				wl = LOSE;
			}
			else if (ene.GetHP() <= 0 && pla.GetHP() > 0) {
				wl = WIN;
			}
			else if ((pla.GetHP() <= 0 && ene.GetHP() <= 0) || (set_flg)) {
				wl = DRAW;
			}
			APS.CalcStreak(wl);
			if (wl > 0) {
				DM.PlusTotal_b();
				switch (wl) {
				case LOSE:
					fccyan;
					printf("\nlose\n");
					fcclear;
					if ((rageHP[1][0] - (ene.GetHP() + ene.GetShieldNum())) / rageHP[1][0] < 1.0) {
						DM.SetTena((float)(rageHP[1][0] - (ene.GetHP() + ene.GetShieldNum())) / rageHP[1][0] * 100);
					}
					else {
						DM.SetTena(100.0);
					}
					break;

				case WIN:
					fcred;
					printf("\nwin\n");
					fcclear;
					Perform(8);
					Perform(16);
					if ((pla.GetSkill(false) == 1) && (spsk1 == 0)) {
						Perform(15);
					}
					liker();
					DM.SetTena((float)(pla.GetHP() + pla.GetShieldNum()) / pla.GetMaxHP() * 100);
					break;

				case DRAW:
					fcwhite;
					printf("\ndraw\n");
					fcclear;
					liker();
					DM.SetTena(0.0);
					break;
				}
				printf("\a評価:\n");
				printf("\"支配\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetTrueDomi() < DM.GetE(1)) {
						if (DM.GetPerc(0) * 10.0 >= (float)a) {
							printf("■");
						}
						else {
							printf("□");
						}
					}
					else {
						printf("■");
					}
				}
				printf("%dpts/%dpts", (int)DM.GetTrueDomi(), DM.GetE(1));
				printf("\n\"執念\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetPerc(1) * 10 >= (float)a) {
						printf("■");
					}
					else {
						printf("□");
					}
				}
				printf("%dpts/%dpts", (int)DM.GetTena(), DM.GetE(2));
				printf("\n\"演出\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetPerc(2) * 10 >= (float)a) {
						printf("■");
					}
					else {
						printf("□");
					}
				}
				printf("%dpts/%dpts\n", DM.GetPerf(), DM.GetE(3));
				b = 0;
				if (DM.GetTrueDomi() >= DM.GetE(1))b++;
				if (DM.GetTena() >= DM.GetE(2))b++;
				if (DM.GetPerf() >= DM.GetE(3))b++;
				if (b >= 3)s_rate++;
				dominated += (int)DM.GetDomi();
				APS.SetRateClass(wl);
				/*ポイント計算*/
				totalpo = (unsigned int)((DM.GetDomi() + DM.GetPerf() * 10) * (1.0 + DM.GetTena() / 100));
				/**************/
				if (nofi == 2)totalpo = totalpo * 2, printf("アイテムの効果で取得経験値+100%%\n");
				if ((wl != WIN) && (b >= 3)) {
					if ((((stgProgress > 0) && (EM.GetEi() == stgProgress + 1)) || ((stgProgress == 0) && (EM.GetEi() <= 1))) && (stgProgress <= 6)) {
						stgProgress++;
						printf("奥に進んだ!!\n");
					}
				}
				//				data.s0 = data.s0 + skpt;
				DM.SetData0(DM.CallData0() + skpt);
				skpt = (int)DM.CallData0();
				if ((skpt > MAX_SKPT) && (ac >= 4)) {
					skpt = MAX_SKPT;
					fcyellow;
					printf("\n\a＊");
					fcclear;
					printf("経験値によってこれ以上スキルレベルは上がりません。\n");
					fccyan;
					printf("\"ショップ\"");
					fcclear;
					printf("の");
					fccyan;
					printf("\"スキル強化\"");
					fcclear;
					printf("を利用してください。\n\n");
				}
				else {
					while (skpt > MAX_SKPT) {
						if (ac >= 4) {
							ac = 4;
							skpt = MAX_SKPT;
							break;
						}
						printf("\aスキルレベルがアップしました。\n\n");
						skpt -= MAX_SKPT;
						ac++;
					}
				}
				switch (wl) {
				case LOSE:
					printf("\a敵の勝利… 敵HP:%d\n", ene.GetHP());
					wlpattern[1]++;
					break;

				case WIN:
					if ((((stgProgress > 0) && (EM.GetEi() == stgProgress + 1)) || ((stgProgress == 0) && (EM.GetEi() <= 1))) && (stgProgress <= 6)) {
						stgProgress++;
						printf("奥に進んだ!!\n");
					}
					if (EM.GetEi() == 7) {//次ステージへ
						printf("記憶の深層に足を進める…\n");
						nextStage();
						stage++;
					}
					if (EM.GetEi() == 8) {
						if (itemn[10] < 7)itemn[10]++;
						printf("喜楽の記憶を手に入れた!!\n");
					}
					printf("\a%sの勝利!! 残りHP:%d\n", name, pla.GetHP());
					wlpattern[0]++;
					break;

				case DRAW:
					printf("\a引き分け\n");
					break;
				}
				if (stgProgress > 6)stgProgress = 6;
				printf("ランク: ");
				int oldRank = rank();
				printf("区分け: ");
				fcyellow;
				printf("%d\n\n", getRankDiv());
				fcclear;
				calRankBonus();
				data1[Mxp] += totalpo;
				int oldPo = fpo;
				fpo += totalpo;
				printf("現在のポイント:%d +%d\n\n", fpo, fpo - oldPo);
				printf("スキルレベル:%d\n", (ac + 1));
				printf("スキルポイント:%.0f%%\n\n", (skpt / (float)MAX_SKPT * 100.0));
				skldata[pla.GetSkill(true) - 1] = ac;
				skdata[pla.GetSkill(true) - 1] = skpt;
				a = 0;
				calLV(data1[Mxp], &data1[MLV]);
				printf("現在のLV:%d (+%d)\n\n", data1[MLV], (data1[MLV] - oldLvl));
				printf("\n");
				if (wl == WIN) {
					if (stage == 3) {
						printf("ボスを倒した!!\a\n");
						stgProgress = 0;
					}
				}
				timer(1000);
				printf("データの保存中…\n");
				itemc(WRITE);
				dataSave();
#ifdef OUT_AI_RATE
				printf("\nAIレート:%d\n", APS.GetAIrate());
				printf("変動:");
				if (APS.GetAIDiff() >= 0) {
					fcgreen;
					printf("+%d\n", APS.GetAIDiff());
					fcclear;
				}
				else {
					fcred;
					printf("%d\n", APS.GetAIDiff());
					fcclear;
				}
				if (getRankChange() < 0) {
					printf("ランク昇格まで:");
					fcgreen;
					printf("%d\n\n", getRankChange() * -1);
					fcclear;
				}
				else {
					printf("ランク降格まで:");
					fcred;
					printf("%d\n\n", getRankChange());
					fcclear;
				}
#endif
				printf("戦績適用後のランク\n");
				int newRank = rank();
				if (oldRank != newRank) {
					printf("%s", rankText[newRank]);
				}
				printf("区分け: ");
				fcyellow;
				printf("%d\n\n", getRankDiv());
				fcclear;
				timer(2000);
				break;
			}
		}
	}
	startWait();
	exit(1);
}