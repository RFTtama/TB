#pragma once
void init(void) {
	int a;
	for (a = 0; a < 6; a++) {//init
		data1[a] = 0;
		if (a < 3) {
			data2[a] = 0;
		}
	}
	APS.ResetAI();
	for (a = 0; a < 18; a++) {
		itemn[a] = 0;
	}
	for (a = 0; a < TOTAL_SKL; a++) {
		sklXp[a] = 0;
		sklLv[a] = 0;
	}
	dislike = 0;
	/*chardata init*/
	DM.InitData();
	DM.InitE(G1, G2, G3);
	SGM.ClearNowSG(All);
	pla.SetIdentify(0);
	ene.SetIdentify(1);
	pla.SetComp(&ene);
	ene.SetComp(&pla);
	/*end of chardata init*/
}

void datalimit(int mode) {
	switch (mode) {
	case 0:
		pla.SetMaxHP(pla.GetHP() + (pla.GetHP() * addition[8]) / 100, D_EQUAL);
		ene.SetMaxHP(ene.GetHP() + (ene.GetHP() * addition[9]) / 100, D_EQUAL);
		pla.SetHP(pla.GetMaxHP(), D_EQUAL);
		ene.SetHP(ene.GetMaxHP(), D_EQUAL);
		ene.SetAT(addition[1], D_PLUS);
		pla.SetAvoidTurn(addition[2], D_PLUS);
		ene.SetAvoidTurn(addition[3], D_PLUS);
		pla.SetCritper(addition[4], D_PLUS);
		ene.SetCritper(addition[5], D_PLUS);
		pla.SetDmgPer((float)addition[10], D_PLUS);
		ene.SetDmgPer((float)addition[11], D_PLUS);
		if (rageHP[0][0] <= 0) {
			rageHP[0][0] = pla.GetMaxHP();
		}
		if (rageHP[1][0] <= 0) {
			rageHP[1][0] = ene.GetMaxHP();
		}
		break;

	case 1:
		pla.AppHPlimit();
		ene.AppHPlimit();
		if ((DM.GetDomi() >= 1500) && (T.GetTurn() >= (T.GetSetTurn() / 4))) {
			Perform(13);
		}
		break;
	}
}

void sk2(void) {
	if (randnum(100) < spsc) {
		printf("\a大地の叫びが敵を切り裂く。\n");
		ene.SetDmg((pla.GetAT() + ene.GetAT()) * (int)((ac + 1) * 0.05), D_PLUS);
		ene.SetAvoid(1, D_PLUS);
		ene.SetDmgResistance(5, D_MINUS);
		Perform(19);
		spsc = randnum(51);
	}
	else {
		spsc += MAZOKU_SKILL;
		printf("スキル命中の確率:%d%%\n", spsc - MAZOKU_SKILL);
	}
}

void liker(void) {
}

int dmgd(int hmax, int hp, int AT) {//ダメージ精度演算
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

void dataSave(){
	int errorcheck = 0, a, b;
	unsigned _int64 lockeddata = 0;
	clock_t safetime, starttime;
	total_b = DM.GetTotal_b();
	if (fopen_s(&LV, "LV.tb", "w") == 0) {
		fprintf_s(LV, savet1, savepatt1);
		APS.CalAIrate();
		for (a = 0; a < 4; a++) {
			for (b = 0; b < 4; b++) {
				fprintf_s(LV, "%lld ", APS.AIout(a, b));
			}
		}
		unsigned _int64 firstCont = APS.GetFirstCont();
		fprintf_s(LV, savet2, savepatt2);
		fclose(LV);
	}
	else {
		outFileError();
	}
	if (fopen_s(&LV, "LV.tb", "r") == 0) {
		fseek(LV, 18L, SEEK_SET);
		starttime = clock();
		safetime = starttime;
		if (fopen_s(&LV2, "LV2.tb", "w") == 0) {
			fcred;
			if (unlock_key == 0) {
				strcpy_s(erstr, "Unknown cipher key");
				errorOutput();
				errorcheck++;
			}
			while (fscanf_s(LV, "%lld", &lockeddata) != EOF) {
				fprintf_s(LV2, "%lld ", lockeddata ^ unlock_key);
				safetime = clock();
				if (safetime - starttime > 2000) {
					strcpy_s(erstr, "Process timed out");
					errorOutput();
					errorcheck++;
					break;
				}
			}
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
	fcclear;
	if (errorcheck > 0) {
		printf("エラーが発生したためデータをリセットします\n");
		remove("LV.tb");
		remove("LV2.tb");
		startWait();
		exit(1);
	}
}

void startWait(void)
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
	printf("1:対戦\n2:ショップ\n3:データ\n4:コマンド(上級者向け)\n");
	connum(&yncnt);
	return yncnt;
}

void data_check(void)
{
	char data[10];
	char moto[] = { "TheBattle" };
	int len = 0;
	int a;
	printf("セーブデータのチェックをします。\n");
	timer(300);
	if (fopen_s(&LV, "LV.tb", "a") != 0) {
		outFileError();
	}
	fclose(LV);
	if (fopen_s(&LV, "LV.tb", "r") == 0) {
		fgets(data, 10, LV);
		fclose(LV);
		if (!strcmp(data, moto)) {
			printf("セーブデータが見つかりました。\n");
		}
		else {
			printf("\aセーブデータが無い可能性があります。\nセーブデータを初期化します。");
			initFlg = true;
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
			unlock_key = randnum(keysize) + 1;
			oldver = VERSION;
			startWait();
			dataSave();
		}
	}
	else {
		outFileError();
	}
}

void calLV(int xp, int* lv) {
	*lv = 1;
	while ((xp >= *lv * Nxp)) {
		xp -= *lv * Nxp;
		*lv += 1;
	}
}

void calRankBonus(void) {
	double rankn[RANK_NUM] = { 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.4 };
	int oldPoint = totalpo;
	int n = 0;
	for (int i = 1000; i <= 3100; i += 300, n++) {
		if (APS.GetAIrate() < i) {
			break;
		}
	}
	fcyellow;
	printf("ランクボーナス *%.1lf", rankn[n]);
	totalpo = (unsigned int)(totalpo * rankn[n]);
	if (oldPoint <= totalpo)printf(" (+%d)\n", totalpo - oldPoint);
	else printf(" (%d)\n", totalpo - oldPoint);
	fcclear;
}

int rank(void)
{
	int n = 0;
	for (int i = 1000; i <= 3100; i += 300, n++) {
		if (APS.GetAIrate() < i) {
			break;
		}
	}
	switch (n) {
	case 0:
		break;

	case 1:
		fcgreen;
		break;

	case 2:
		fcwhite;
		break;

	case 3:
		fcyellow;
		break;

	case 4:
		fcwhite;
		break;

	case 5:
		fcblue;
		break;

	case 6:
		fccyan;
		break;

	case 7:
		fcgreen;
		break;

	default:
		fcred;
		break;
	}
	printf("%s\n", rankName[n]);
	fcclear;
	return n;
}

int getRankChange(void) {
	int div, i;
	div = APS.GetAIrate() - 1000;
	for (i = 0; i < div; i += 300);
	i -= 300;
	if ((div - i) <= -1 * (div - (i + 300))) {
		return div - i;
	}
	else {
		return div - (i + 300);
	}
}

int getRankDiv(void) {
	int div = 0, n = 0, rate;
	rate = APS.GetAIrate();
	for (int i = 1000; i <= 2800; i += 300, n++) {
		if (rate < i) {
			break;
		}
	}
	for (int rateSamp = 999 + (n - 1) * 300; rateSamp < rate; rateSamp += 100) {
		div++;
	}
	return div;
}

void story(char st[256], int delay) {
	int a = 0;
	while (1) {
		putchar(st[a]);
		a++;
		if (st[a] == '\0') {
			break;
		}
		timer(delay);
	}
}

void SetColor(void) {
	if (reborneflg == 1) {
		fccyan;
	}
	else if (pla.GetHpPer() < 0.1) {
		fcred;
	}
	else if (pla.GetHpPer() < 0.25) {
		fcyellow;
	}
	else {
		fcclear;
	}
}

void Perform(int tag) {
	struct Cat {
		char String[CNUM][5] = {
			"", "命中", "回避", "反射", "急所", "耐久", "耐久", "勝利", "", "逆上", "発動",
			"遮断", "支配", "信頼", "終了", "高速", "軽傷", "重傷", "破壊", "妨害", "捕捉", "無効",
			"追撃", "回復", "不純"
		};
		int Point[CNUM] = {
			0, 4, 3, 5, 6, 2, 2, 20, 0, -30, 5,
			5, 2, 2, 5, 0, 4, 7, 2, 1, 3, 3,
			0, 1, -10
		};
	}Cat;
	switch (tag) {
	case 16:
		if (40 - T.GetTurn() >= 0) {
			if (40 - T.GetTurn() >= 10) {
#ifdef SHOW_PERF
				printf("<%s> %dpts\n", Cat.String[tag - 1], 100 - T.GetTurn());
#endif
				DM.SetPerf(100 - T.GetTurn());
			}
			else {
#ifdef SHOW_PERF
				printf("<%s> %dpts\n", Cat.String[tag - 1], 100 - T.GetTurn() * 2);
#endif
				DM.SetPerf(100 - T.GetTurn() * 2);
			}
		}
		break;

	case 23:
		if (c23pt > 0) {
#ifdef SHOW_PERF
			printf("<%s> %dpts\n", Cat.String[tag - 1], c23pt);
#endif
			DM.SetPerf(c23pt);
		}
		break;

	default:
#ifdef SHOW_PERF
		printf("<%s> %dpts\n", Cat.String[tag - 1], Cat.Point[tag - 1]);
#endif
		DM.SetPerf(Cat.Point[tag - 1]);
		break;
	}
}

void outFileError(void) {
	int erNum = errno;
	strerror_s(erstr, erNum);
	printf("Error Num: %d\n", erNum);
	errorOutput();
	startWait();
	exit(-1);
}

void nextStage(void) {
	fpo = 0;
	item = 0;
	for (int i = 0; i < ITEMNUM; i++) {
		itemn[i] = 0;
	}
	stgProgress = 0;
	for (int i = 0; i < TOTAL_SKL; i++) {
		sklXp[i] = 0;
		sklLv[i] = 0;
	}
	ac = 0;
	skpt = 0;
	data1[MLV] = 0;
	data1[Mxp] = 0;
	stageUpFlg = true;
}

void c23ptc(void) {
	c23pt++;
	if (c23pt > 5) {
		c23pt = 5;
	}
	if ((pla.GetSkill(false) == 3) && (c23pt > 0)) {
		printf("スキルによりシールドが");
		fccyan;
		printf("%d", 1 + (1 * data1[Mskc]));
		SetColor();
		printf("増加した!!\n");
		pla.SetShieldNum(1 + (1 * data1[Mskc]), D_PLUS);
		if (++data1[Mskc] > ac + 1) {
			data1[Mskc] = ac + 1;
		}
	}
	Perform(23);
}

void decc23(void) {
	c23pt = -1;
	if (pla.GetSkill(false) == 3) {
		data1[Mskc] = 0;
	}
}

void painin(void) {
	if (ene.GetSkill(false) == 10) {
		slowpain = 2;
		printf("苦しみの呪いをかけられた!!回避行動で解除しよう!!\n");
	}
}

void espain(void) {
	if (slowpain > 0) {
		slowpain = 0;
		printf("苦しみの呪いを解除した!!\n");
	}
}

int getRank(int value) {
	int n = 0;
	for (int i = 1000; i <= 2800; i += 300, n++) {
		if (value < i) {
			break;
		}
	}
	return n;
}