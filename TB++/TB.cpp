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
		printf("\n�Q�[���̃o�[�W�������V�����Ȃ�܂���\n\n");
		printf("�f�[�^�����Z�b�g���܂�\n");
		remove("LV.tb");
		remove("LV2.tb");
		startWait();
		exit(1);
	}
	else if (VERSION < oldver) {
		fcred;
		printf("\a\n�Z�[�u�f�[�^�ƃQ�[���f�[�^�̃o�[�W�������Ⴂ�܂�\n");
		printf("�݊������m�F�ł��Ȃ����߃Q�[���̋N���𒆎~���܂�\n");
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
			printf("�f�[�^�̐��������m�F���܂��c\n");
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
			if (dataerrorcheck > 0)printf("�G���[��:%d\n\n", dataerrorcheck);
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
		printf("�G���[�������������߃f�[�^�����Z�b�g���܂�\n");
		remove("LV.tb");
		remove("LV2.tb");
		startWait();
		exit(1);
	}
	fclose(LV2);
	fclose(LV);
	/*�����I��*/
	if (DM.GetTotal_b() % 5 == 0 && DM.GetTotal_b() > 0) {
		if (--dislike < 0) {
			dislike = 0;
		}
	}
	if (dislike >= 4) {
		remove("LV.tb");
		remove("LV2.tb");
		printf("\a\n������ɋy�ԕs�����m�F���ꂽ���߁A�Q�[���f�[�^�����Z�b�g���܂�\n");
		startWait();
		exit(1);
	}
	else if (dislike >= 1) {
		fcyellow;
		printf("\a\n�v���C���ɃQ�[�������͕̂s���s�ׂƂ݂Ȃ���܂�\n");
		fcclear;
	}
	if (stage == 0) {
		printf("���\n");
	}
	else if (stage == 1) {
		printf("����\n");
	}
	else if (stage == 2) {
		printf("�[��\n");
	}
	if (cfg.getUnlocked() == 1) {
		fcyellow;
		printf("Developer mode\n");
		fcclear;
	}
	if (pla.GetSkill(true) != 0) {
		printf("�ʂ̃X�L����I�����܂���?\n");
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
		printf("�L�����N�^�[�̑����X�L����I�����Ă��������B\n\n");
		printf("1:\"���� Lv:%d\" �Ή����˂�I�������ꍇ���ʂ���������B\n", skldata[0]);
		printf("����: ����Ƀ_���[�W��^���A�����̔\�͂���̉�����B\n���̔\�͂�1��̑ΐ��1��g���A�U���𖽒�������x�ɈЗ͂��㏸����B\n\n");
		printf("2:\"���� Lv:%d\" ����U���𖽒��������ۂɌ��ʂ���������B\n", skldata[1]);
		printf("����: ������������Ƀ_���[�W��^���\�͂���̉�������X�L���𔭓�����B�������̓X�L�������Ɏ��s����x�ɏ㏸����B\n���̔\�͔������ɖ������̓��Z�b�g�����B\n\n");
		printf("3:\"�@�B�� Lv:%d\" �A���ōU���𖽒�������ƌ��ʂ���������B\n", skldata[2]);
		printf("����: �V�[���h���l������B\n���̒l�͘A���ōU���𖽒�������x�ɑ�������B\n\n");
		a = 0;
		do {
			connum(&skill);
			pla.SetSkill(skill);
			switch (pla.GetSkill(true)) {
			case 1:
				printf("\a���Ȃ���\"����\"��I�����܂����B\n");
				ac = skldata[0];
				skpt = skdata[0];
				a = 1;
				break;
			case 2:
				printf("\a���Ȃ���\"����\"��I�����܂����B\n");
				ac = skldata[1];
				skpt = skdata[1];
				a = 1;
				break;
			case 3:
				printf("\a���Ȃ���\"�@�B��\"��I�����܂����B\n");
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
		printf("*�T*\n");
		change = 2;
		ent3 = 100;//1.00%
	}
	else if (stgProgress < 2) {
		printf("*�U*\n");
		change = 3;
		ent3 = 90;//1.11%
	}
	else if (stgProgress < 3) {
		printf("*�V*\n");
		change = 4;
		ent3 = 80;//1.25%
	}
	else if (stgProgress < 4) {
		printf("*�W*\n");
		change = 5;
		ent3 = 70;//1.43%
	}
	else if (stgProgress < 5) {
		printf("*�X*\n");
		change = 6;
		ent3 = 60;//1.67%
	}
	else if (stgProgress < 6) {
		printf("**�Y**\n");
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
	printf("\n���x��:%d\n\n", data1[MLV]);
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
				printf("�x��:�J���҃��[�h�ł�");
			}
			printf("\n------------------------\n");
			printf("�o�[�W����: %d\n", VERSION);
			printf("�L�����l�[��: %s\n", name);
			printf("���x��: %d\n", data1[MLV]);
			printf("�X�e�[�W: %d\n", stage + 1);
			printf("�i�s�x: %d\n", stgProgress);
			printf("�|�C���g: %d\n", fpo);
			printf("�����N: ");
			rank();
			if (cfg.getUnlocked() == 1)fcyellow;
			printf("�敪��: %d\n", getRankDiv());
			printf("�m�胉���N: %s\n", rankName[APS.GetMaxAIdecideRank()]);
			printf("�敪��: %d\n", APS.GetMaxAIdecideRankDiv());
			printf("�X�L��: %d\n", pla.GetSkill(true));
			printf("�X�L�����x��: %d\n", (ac + 1));
			printf("�X�L���|�C���g: %.0f%%\n", (skpt / (float)MAX_SKPT * 100.0));
			printf("�A�C�e���f�[�^: %llx\n", item);
			printf("���v�v���C��: %d\n", total_b);
			printf("���ώx�z��: %.2lf%%\n", (double)dominated / total_b / 10.0);
			printf("�ō��]���擾��: %d\n", s_rate);
			printf("������: %d\n", wlpattern[0]);
			printf("����: %.2lf%%\n", (double)wlpattern[0] / total_b * 100.0);
			printf("�^�����_���[�W: %lld\n", calcDmg);
			printf("���σ_���[�W: %.2lf\n", (double)calcDmg / total_b);
			printf("�X�g���[�N: %d\n", APS.GetStreak());
			printf("�ؒf��: %d\n", dislike);
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
		printf("�A�C�e�����g�p���܂���? Yes=0\n");
		connum(&a);
		if (a == 0) {
			printf("�ǂ̃A�C�e�����g�p���܂���?\n");
			for (a = 0; a < 11; a++) {
				if (itemn[a] > 0) {
					printf("%d:%s ��:%x\n", a, flavor[a], itemn[a]);
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
					printf("�_���[�W�{��10%%����&2�񕜊��\!!\n");
				}
				break;
			case 1:
				if (itemn[1] - 1 >= 0) {
					itemn[1]--;
					nofi = 2;
					printf("�擾�o���l�y�у|�C���g100%%����!!\n");
				}
				break;
			case 2:
				if (itemn[2] - 1 >= 0) {
					itemn[2]--;
					nofi = 3;
					printf("�񕜗�20%%����!!\n");
				}
				break;
			case 3:
				if (itemn[3] - 1 >= 0) {
					ent3 = 3;
					itemn[3]--;
					nofi = 4;
					printf("���񂾋L���o���m���㏸!!\n");
				}
				break;
			case 4:
				if (itemn[4] - 1 >= 0) {
					data1[Mreborn] = 2;
					itemn[4]--;
					nofi = 5;
					printf("�̗͂�0�ȉ��ɂȂ����Ƃ���2�񕜊�!!\n");
				}
				break;
			case 5:
				if (itemn[5] - 1 >= 0) {
					itemn[5]--;
					nofi = 6;
					printf("HP��50%%���������ۂ�10%%��!!\n");
				}
				break;
			case 6:
				if (itemn[6] - 1 >= 0) {
					itemn[6]--;
					nofi = 7;
					printf("�}���U���ɕK�v��SG��1������!!\n");
				}
				break;
			case 7:
				if (itemn[7] - 1 >= 0) {
					itemn[7]--;
					nofi = 8;
					printf("HP��20%%�ȉ��̎��ő�HP�Œ�!!\n");
				}
				break;
			case 8:
				if (itemn[8] - 1 >= 0) {
					itemn[8]--;
					nofi = 9;
					printf("HP��10%%����!!\n");
				}
				break;
			case 9:
				if (itemn[9] - 1 >= 0) {
					printf("�V�Ɍ������ċF���������c\n");
					timer(700);
					if (randnum(2) == 0) {
						data1[Mreborn] = data1[Mreborn] + 1;
						printf("�肢�����Ȃ����悤�ȋC�������c\n");
					}
					else {
						printf("�肢�͉��҂��ɂ���Ă��������ꂽ�c\n");
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
					printf("����̍s�����ǂ߂�����!!\n");
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
		printf("\"����\"");
		fcwhite;
		printf(" �Ή����˂�I�������ꍇ���ʂ���������B\n");
		printf("�����");
		fcgreen;
		printf("\"%s\"", sk1flaze[ac]);
		fcwhite;
		printf("�_���[�W��^���A�����̔\�͂���̉�����B\n���̔\�͂�1��̑ΐ��1��g���A�U���𖽒�������x�ɈЗ͂��㏸����B\n");
//		SG[0][0] = 10;
		SGM.SetMaxSG(10, Pla);
		break;
	case 2:
		fccyan;
		printf("\"����\"");
		fcwhite;
		printf(" ����U���𖽒��������ۂɌ��ʂ���������B\n");
		printf("�������������");
		fcgreen;
		printf("\"%s\"", sk1flaze[ac]);
		fcwhite;
		printf("�_���[�W��^���\�͂���̉�����X�L���𔭓�����B�������̓X�L�������Ɏ��s����x��%d%%�㏸����B\n���̔\�͔������ɖ������̓��Z�b�g�����B\n", MAZOKU_SKILL);
//		SG[0][0] = 10;
		SGM.SetMaxSG(10, Pla);
		break;
	case 3:
		fccyan;
		printf("\"�@�B��\"");
		fcwhite;
		printf(" �A���ōU���𖽒�������ƌ��ʂ���������B\n");
		printf("1�|�C���g�̃V�[���h���l������B\n���̒l�͘A���ōU���𖽒��������1�|�C���g���������A�ő�");
		fcgreen;
		printf("\"%d\"", (ac + 1));
		fcwhite;
		printf("��������B\n");
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
	printf("%s�̃v���t�B�[��\n", name);
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
	else if (randnum(ent3) == 0) {//���񂾋L��
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
			case 0://�]���r
				ene.SetHP(900, D_EQUAL);
				ene.SetAT(50, D_EQUAL);
//				SG[1][0] = 11;
				if (stgProgress >= 1)ene.SetSkill(3);
				SGM.SetMaxSG(11, Ene);
				break;

			case 1://����
				ene.SetHP(800, D_EQUAL);
				ene.SetAT(60, D_EQUAL);
//				SG[1][0] = 13;
				if (stgProgress >= 1)ene.SetSkill(3);
				SGM.SetMaxSG(13, Ene);
				break;

			case 2://�S�[�X�g
				ene.SetHP(pla.GetHP(), D_EQUAL);
				ene.SetAT(50, D_EQUAL);
				ene.SetShieldNum(250, D_EQUAL);
				rageHP[1][0] = ene.GetHP() + ene.GetShieldNum();
				if (stgProgress >= 2)ene.SetSkill(7);
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;

			case 3://���؎�
				ene.SetHP(1300, D_EQUAL);
				ene.SetAT(50, D_EQUAL);
				if (stgProgress >= 3)ene.SetSkill(1);
//				SG[1][0] = 11;
				SGM.SetMaxSG(11, Ene);
				break;

			case 4://�L���̖͕�
				ene.SetHP(pla.GetHP(), D_EQUAL);
				ene.SetAT(pla.GetAT(), D_EQUAL);
				ene.SetSkill(randnum(2) + 1);
//				SG[1][0] = 10;
				SGM.SetMaxSG(10, Ene);
				break;

			case 5://����
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(80, D_EQUAL);
				ene.SetPlusAT(2, D_EQUAL);
				if (stgProgress >= 5)ene.SetSkill(3);
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;

			case 6://�א_
				printf("\a_/_/Boss_/_/");
				ene.SetHP(1400, D_EQUAL);
				ene.SetAT(90, D_EQUAL);
//				SG[1][0] = 13;
				SGM.SetMaxSG(13, Ene);
				break;

			case 7://�א_�U
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
			case 0://�t���[�g
				ene.SetHP(pla.GetHP() / 2, D_EQUAL);
				ene.SetAT(pla.GetAT(), D_EQUAL);
				ene.SetSkill(5);
				ene.SetShieldNum(pla.GetHP() / 2 + pla.GetHP() % 2, D_EQUAL);
				rageHP[1][0] = ene.GetHP() * 2;
//				SG[1][0] = 12;
				SGM.SetMaxSG(12, Ene);
				break;
			case 1://�i��
				ene.SetHP(1200, D_EQUAL);
				ene.SetAT(70, D_EQUAL);
				ene.SetSkill(2);
//				SG[1][0] = 9;
				SGM.SetMaxSG(9, Ene);
				break;
			case 2://�����̇T
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(90, D_EQUAL);
				ene.SetSkill(1);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			case 3://���̐��̎g��
				ene.SetHP(1300, D_EQUAL);
				ene.SetAT(80, D_EQUAL);
				ene.SetSkill(3);
//				SG[1][0] = 13;
				SGM.SetMaxSG(13, Ene);
				break;
			case 4://�A���W�I���W�[
				ene.SetHP(1600, D_EQUAL);
				ene.SetAT(60, D_EQUAL);
				ene.SetSkill(8);
//				SG[1][0] = 16;
				SGM.SetMaxSG(16, Ene);
				break;
			case 5://�{�C�h
				ene.SetHP(1000, D_EQUAL);
				ene.SetAT(20, D_EQUAL);
				ene.SetShieldNum(1200, D_EQUAL);
				ene.SetSkill(4);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			case 6://�t�B�j�[�g
				printf("\a_/_/Boss_/_/");
				ene.SetHP(2000, D_EQUAL);
				ene.SetAT(100, D_EQUAL);
				ene.SetSkill(2);
//				SG[1][0] = 17;
				SGM.SetMaxSG(17, Ene);
				break;
			case 7://�G��
				printf("\a_/_/Boss_/_/");
				ene.SetHP(2000, D_EQUAL);
				ene.SetAT(10, D_EQUAL);
				ene.SetSkill(7);
//				SG[1][0] = 20;
				SGM.SetMaxSG(20, Ene);
				break;
			}
			break;

		case 3://�U��̊�]
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
		printf("\n��Փx����");
		fcwhite;
		printf("\n�v���C���[\n");
		fcyellow;
		printf("���O�����N�̂��ߑS�Ă̔\�͂�L��\n\n");
		fcclear;

	}
	printf("\n_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	printf("�G�f�[�^\nName:%s HP:%d  AT:%d\n", charbox, ene.GetHP(), ene.GetAT());
	printf("�X�L��:%s\n", eskname[ene.GetSkill(false)]);
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n");
	fccyan;
	printf("\"%s\" ", eskname[ene.GetSkill(false)]);
	fcwhite;
	printf("%s\n\n", eskchips[ene.GetSkill(false)]);
	fcclear;
	printf("���ʗ\�z: %s\n\n", expect[pla.ExpectResult()]);
#ifdef RELEASE
	dislike++;
#endif
	dataSave();//�r���Z�[�u
#ifdef RELEASE
	dislike--;
#endif
	timer(400);
	printf("�ΐ���n�߂܂�\n");
	startWait();
	printf("\n");
	for (a = 0; a < 12; a++) {
		addition[a] = 0;
	}
	/*�A�C�e������*/
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
		/* ���񂾋L������ */
		if ((EM.GetEi() == 8) && (data2[Etier] != tier)) {
			fcyellow;
			if (data2[Etier] == 1) {//�e�B�A2
				ene.SetHP(1000, D_EQUAL);
				ene.SetMaxHP(ene.GetHP(), D_EQUAL);
				ene.SetAT(60, D_EQUAL);
				ene.SetShieldNum(1000, D_EQUAL);
				printf("\a���񂾋L���͏��X�ɗ͂�t���Ă���c\n");
			}
			else if (data2[Etier] == 2) {//�e�B�A3
				ene.SetShield(true);
				printf("\a���񂾋L���ɃV�[���h�Đ��\�͂��t�^���ꂽ\n");
			}
			else if (data2[Etier] == 3) {//�e�B�A4
				ene.SetDmgBoost(true);
				printf("\a���񂾋L���Ƀ_���[�W�u�[�X�g���t�^���ꂽ\n");
			}
			else if (data2[Etier] == 4) {//�e�B�A5
				pla.SetSkillFlg(false);
				printf("\a�X�L�������������ꂽ�B\n");
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
				printf("���񂾋L���͂��̐g�ɐ��ȃp���[���h���Ă���c\n");
				SetColor();
			}
			else {
				ene.SetPlusAT(0, D_EQUAL);
			}
		}
		printf("\n");
		//		if (end == 1)printf("<�o�O����>\n");
		printf("�^�[��:%d\n", T.GetTurn());
		printf("_/_/_/_/_/%s�̃X�e�[�^�X HP:%d[%d](%.1lf%%) AT:%d", name, pla.GetHP(), pla.GetShieldNum(), (double)pla.GetHpPer() * 100.0, pla.GetAT());
		if (pla.GetPlusAT() > 0) {
			fcred;
			printf("+%d", pla.GetPlusAT() * PLUSNUM);
			SetColor();
		}
		if (pla.GetDmgBoost())printf(" [��]");
		if (pla.GetShield())printf(" [��]");
		if (pla.GetRevenge())printf(" [��]");
		printf(" _/_/_/_/_/");
		printf("\n_/_/_/_/_/%s�̃X�e�[�^�X HP:%d[%d](%.1lf%%) AT:%d", charbox, ene.GetHP(), ene.GetShieldNum(), (double)ene.GetHpPer() * 100.0, ene.GetAT());
		if (ene.GetPlusAT() > 0) {
			fcred;
			printf("+%d", ene.GetPlusAT() * PLUSNUM);
			SetColor();
		}
		if (ene.GetDmgBoost())printf(" [��]");
		if (ene.GetShield())printf(" [��]");
		if (ene.GetRevenge())printf(" [��]");
		if (EM.GetEi() == 8) {
			if (data2[Etier] >= 5) {
				printf(" Tier:5");
			}
			else {
				printf(" Tier:%d", data2[Etier] + 1);
			}
		}
		printf(" _/_/_/_/_/\n\n");
		/*if (end == 0)*/printf("\t%s�_���[�W�{��:\t%.0lf%%(+%.0lf%%)\t�G�_���[�W�{��:\t%.0lf%%(+%.0lf%%)\n", name, floor(pla.GetDmgPer()),floor(pla.GetDmgPerInc()), floor(ene.GetDmgPer()), floor(ene.GetDmgPerInc()));
		printf("\t      �}���{��:\t\t%d%%\t\t�G�}���{��:\t%d%%\n", pla.GetCritPer(), ene.GetCritPer());
		printf("\t      �񕜗�:\t\t%.0lf%%\t\t�񕜗�:\t\t%.0lf%%\n", floor(pla.GetHealPer()), floor(ene.GetHealPer()));
		printf("\t      ���C�x:\t\t%s\t\t���C�x:\t\t%s\n\n", sensesFlavor[(int)(pla.GetSenses() + TO_INT)], sensesFlavor[(int)(ene.GetSenses() + TO_INT)]);
		printf("%s:", name);
		pla.ResetDmgPerBef();
		ene.ResetDmgPerBef();
		for (a = 1; a <= 10; a++) {
			if (((pla.GetShieldNum() / (float)pla.GetMaxHP()) * 10.0 >= 11 - a) && (pla.GetShieldNum() > 0)) {
				fccyan;
				printf("��");
				SetColor();
			}
			else if (pla.GetHpPer() * 10.0 >= a) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
		SetColor();
		printf("  %s:", charbox);
		for (a = 1; a <= 10; a++) {
			if (((ene.GetShieldNum() / (float)ene.GetMaxHP()) * 10.0 >= 11 - a) && (ene.GetShieldNum() > 0)) {
				fccyan;
				printf("��");
				SetColor();
			}
			else if (ene.GetHpPer() * 10.0 >= a) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
		SetColor();
		printf("\n");
		printf("    SG:");
		if (SGM.GerPer(Pla) >= 1.0)fcclear;
		for (a = 1; a <= 10; a++) {
			if ((SGM.GerPer(Pla) * 100) >= ((double)a * 10))printf("��");
			else printf("�Z");
		}
		SetColor();
		if (SGM.GerPer(Ene) >= 1.0)fcclear;
		for (a = 0; a < strlen(charbox); a++) {
			printf(" ");
		}
		printf("SG:");
		for (a = 1; a <= 10; a++) {
			if ((SGM.GerPer(Ene) * 100) >= ((double)a * 10))printf("��");
			else printf("�Z");
		}
		SetColor();
		printf("\n");
		/* �s���I�� */
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
			printf("�s���I��\n�ʏ�U��");
			if (!SGM.GetSf(Pla)) {
				printf("(%.0lf)", pla.CalcAT() * NOMAL_MAGN * (ene.GetDmgPer() / 100.0));
			}
			else {
				fcyellow;
				printf("(%.0lf)", pla.CalcAT() * NOMAL_MAGN * (ene.GetDmgPer() / 100.0) * (ene.GetCritPer() / 100.0));
				SetColor();
			}
			printf(" :1 ����U��");
			if (!SGM.GetSf(Pla)) {
				printf("(%.0lf)", pla.CalcAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0));
			}
			else {
				fcyellow;
				printf("(%.0lf)", pla.CalcAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0) * (ene.GetCritPer() / 100.0));
				SetColor();
			}
			printf(" : 2 ����s��");
			if (!nsp) {
				printf("(%.0lf%%)", pla.GetAvoidPer());
			}
			else {
				printf("(0%%)");
			}
			printf(" : 3 ����U����");
			printf("(%.0lf)", ene.GetAT() * SPECL_MAGN * (ene.GetDmgPer() / 100.0));
			printf(" : 4");
			if ((pla.GetSkill(false) == 1) && (spsk1 > 0)) {
				printf(" �Ή�����:5(+%d)", data1[Mskc]);
			}
			printf("\n");
			connum_int16(&k1);
			if ((k1 == 5) && (pla.GetSkill(false) == 1) && (spsk1 > 0)) {
				break;
			}
		} while ((k1 == ak1) || (k1 < 1) || (k1 > 4));
		if (k1 == 5) {
			printf("%s�͉Ή����˂��g����!!\n", name);
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
			printf("�v���C���[��%s�͑����҂����肾!!\n", name);
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
		if ((k1 == 1) && (k2 == 0)) {//�ʏ�@�ʏ�
			ene.Atk();
			pla.Atk();
			sk1cp;
			printf("%s�̒ʏ�U��!! %s�̒ʏ�U��!!\n", name, charbox);
			pla.Decr();
			ene.Decr();
			Perform(2);
			c23ptc();
		}
		else if ((k1 == 1) && (k2 == 1)) {//�ʏ�@����
			ene.SpAtk();
			pla.Boost();
			ent;
			enttier;
			printf("%s�̒ʏ�U��!! ������%s�͋���������Ă���c\n%s�̓���U��!!\n", name, charbox, charbox);
			ene.Decr();
			decc23();
		}
		else if ((k1 == 1) && (k2 == 2)) {//�ʏ�@���
			if (randnum(100) < ene.GetAvoidPer()) {
				ene.Heal();
				if (ene.GetDmg() < 0)ene.SetDmg(ene.GetDmg() / 2, D_EQUAL);
				ene.Shield();
				pla.Boost();
				printf("%s�̒ʏ�U��!! ������%s�̉���s���ɂ���ĉ�����ꂽ�B\n", name, charbox);
				decc23();
				Perform(20);
			}
			else {
				pla.Atk();
				sk1cp;
				printf("%s�̒ʏ�U��!! %s�͉���Ɏ��s����!!\n", name, charbox);
				pla.Decr();
				Perform(2);
				Perform(21);
				c23ptc();
			}
		}
		else if ((k1 == 1) && (k2 == 3)) {//�ʏ�@��
			pla.Atk();
			sk1cp;
			printf("%s�̒ʏ�U��!! %s�͍U�����˂Ɏ��s����!!\n", name, charbox);
			pla.Decr();
			Perform(2);
			c23ptc();
		}
		/******************************************************************************************************************/
		else if ((k1 == 2) && (k2 == 0)) {//����@�ʏ�
			if (spsk1 < 0) {
				printf("%s��%s�̎ܔM�̉��ŔR�₳��Ă���!!\n", charbox, name);
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
				printf("%s�̓���U��!! %s�̍U���͋����������ē͂��Ȃ�!!\n", name, charbox);
				pla.Decr();
				Perform(2);
				c23ptc();
			}
		}
		else if ((k1 == 2) && (k2 == 1)) {//����@����
			if (spsk1 < 0) {
				printf("%s��%s�̎ܔM�̉��ŔR�₳��Ă���!!\n", charbox, name);
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
				printf("%s�̓���U��!! %s�̓���U��!!\n", name, charbox);
				pla.Decr();
				ene.Decr();
				Perform(2);
				c23ptc();
			}
		}
		else if ((k1 == 2) && (k2 == 2)) {//����@���
			if (spsk1 < 0) {
				printf("%s��%s�̎ܔM�̉��ŔR�₳��Ă���!!\n", charbox, name);
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
					printf("%s�̓���U��!! ������%s�̉���s���ɂ���ĉ�����ꂽ�B\n", name, charbox);
					decc23();
					Perform(20);
				}
				else {
					pla.SpAtk();
					if ((pla.GetSkill(false) == 2)) {
						sk2();
					}
					sk1cp;
					printf("%s�̓���U��!! %s�͉���Ɏ��s����!!\n", name, charbox);
					pla.Decr();
					Perform(2);
					Perform(21);
					c23ptc();
				}
			}
		}
		else if ((k1 == 2) && (k2 == 3)) {//����@��
			if (spsk1 < 0) {
				printf("%s��%s�̎ܔM�̉��ŔR�₳��Ă���!!\n", charbox, name);
				pla.Weak();
				pla.Decr();
				spsk1 = 0;
			}
			else {
				ene.Ref();
				if (data1[Mill] != 1)pla.Boost();
				painin();
				printf("%s�̓���U��!! ������%s�̓���U���ǂɂ���Ĕ��˂��ꂽ�B\n", name, charbox);
				decc23();
			}
		}
		/******************************************************************************************************************/
		else if ((k1 == 3) && (k2 == 0)) {//����@�ʏ�
			if (randnum(100) < (pla.GetAvoidPer()) && !nsp) {
				pla.Shield();
				pla.Heal();
				if (pla.GetDmg() < 0)pla.SetDmg(pla.GetDmg() / 2, D_EQUAL);
				ene.Boost();
				espain();
				printf("%s�̒ʏ�U��!! ������%s�͍U�����������!!\n", charbox, name);
				Perform(3);
				Perform(24);
			}
			else {
				ene.Atk();
				printf("%s�̒ʏ�U��!! %s�͉���Ɏ��s�����B\n", charbox, name);
				ene.Decr();
			}
		}
		else if ((k1 == 3) && (k2 == 1)) {//����@����
			ent;
			enttier;
			if (randnum(100) < pla.GetAvoidPer() / 2 && !nsp) {
				pla.Shield();
				pla.Heal();
				if (pla.GetDmg() < 0)pla.SetDmg(pla.GetDmg() / 3, D_EQUAL);
				ene.Boost();
				espain();
				printf("%s�̓���U��!! %s�͉������!!\n", charbox, name);
				Perform(3);
				Perform(24);
			}
			else {
				ene.SpAtk();
				printf("%s�̓���U��!! %s�͉���Ɏ��s���Ă��܂����B\n", charbox, name);
				ene.Decr();
			}
		}
		else if ((k1 == 3) && (k2 == 2)) {//����@���
			pla.Heal();
			ene.Heal();
			pla.Shield();
			ene.Shield();
			espain();
			printf("%s��%s�̉���s���c ���݂����ɂ݂����Ă���B\n", name, charbox);
			Perform(24);
		}
		else if ((k1 == 3) && (k2 == 3)) {//����@��
			pla.Shield();
			pla.Heal();
			painin();
			printf("%s�̉���s��!! %s�͓��ꔽ�˂̍\���ɓ����Ă���B\n", name, charbox);
			Perform(24);
		}
		/******************************************************************************************************************/
		else if ((k1 == 4) && (k2 == 0)) {//�ǁ@�ʏ�
			ene.Atk();
			printf("%s�͓��ꔽ�˂̍\���ɓ����Ă���c %s�̒ʏ�U��!!\n", name, charbox);
			ene.Decr();
		}
		else if ((k1 == 4) && (k2 == 1)) {//�ǁ@����
			pla.Ref();
			ene.Boost();
			printf("%s�̓���U��!! ������%s�̓��ꔽ�˕ǂɂ���Ĕ��˂���!!\n", charbox, name);
			Perform(4);
		}
		else if ((k1 == 4) && (k2 == 2)) {//�ǁ@���
			ene.Heal();
			ene.Shield();
			printf("%s�͓��ꔽ�˂̍\���ɓ����Ă���c %s�͉���^�������Ă���c\n", name, charbox);
		}
		else if ((k1 == 4) && (k2 == 3)) {//�ǁ@��
			painin();
			printf("���݂����ɂ݂����Ă���\n");
		}
		/******************************************************************************************************************/
		if ((T.TurnRemains()) <= 5 && (T.TurnRemains() >= 0)) {
			printf("\n\a�Z�b�g�܂ł���%d�^�[��\n\n", T.TurnRemains());
		}
		if (T.TurnRemains() == 0) {
			printf("\n�Z�b�g!!\n");
			set_flg = true;
		}
		if ((ak1 == 1) || (ak1 == 2))pen++; else pen = 0;
		if (pen > 4) { 
			Perform(25);
		}
		//		if ((T.GetTurn() <= 0) && (end == 1))end = 0, dmg[0] = 100000000, dmg[1] = 100000000, totalpo = totalpo + 3000, chardata[0].Dmgper = 1000, chardata[1].Dmgper = 1000, turn = 75;
		/*�G�X�L������*/
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
					printf("%s�͗͂����߂Ă���c\n", charbox);
				}
				else {
					for (a = 0, b = ene.GetAT(); a < data2[Ecnt]; a++) {
						b = (int)(b * 1.5);
					}
					data2[Ecnt] = 0;
					pla.SetDmg(ene.Dmgd(b), D_PLUS);
					printf("%s�͗͂��J�������B\n", charbox);

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
					printf("%s�̃X�L���ɂ��%s�͑��������B\n", charbox, name);
				}
				else {
					data2[Ecnt]++;
					printf("�ł̖��̔Z�x:%d%%\n", data2[Ecnt]);
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
						printf("�����ǂ����ǂ����B\n");
					}
					else if (data1[Mill] != 4) {
						timer(1);
						while ((a = randnum(3)) == (data1[Mill] - 1));
						if (a == 0) {
							illcnt = 3;
							data1[Mill] = 1;
							printf("����ǂ����ǂ����B\n");
						}
						else if (a == 1) {
							illcnt = 2;
							data1[Mill] = 2;
							printf("�f���ǂ����ǂ����B\n");
						}
						else if (a == 2) {
							illcnt = 4;
							data1[Mill] = 3;
							printf("�󎀏ǂ����ǂ����B\n");
						}
					}
					argePer -= 2;
				}
			}
			if (data1[Mill] == 1) {
				printf("�͂������Ă䂭�c\n");
				pla.SetAT(2, D_MINUS);
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					printf("����ǂ���������!!\n");
				}
			}
			else if (data1[Mill] == 2) {
				printf("�̗͂������Ă䂭�c\n");
				pla.SetDmg((int)(pla.GetHP() * 0.1), D_PLUS);
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					printf("�f���ǂ���������!!\n");
				}
			}
			else if (data1[Mill] == 3) {
				printf("�v���悤�ɑ̂������Ȃ��c\n");
				nsp = 1;
				illcnt--;
				if (illcnt <= 0) {
					data1[Mill] = 0;
					illcnt = 0;
					nsp = 0;
					printf("�󎀏ǂ����������B\n");
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
					printf("�����ǂ����������B\n");
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
				printf("���܂����Ռ��g��%s�𐁂���΂����B\n", name);
				Mres[0] = 0;
				pla.SetDmg(pla.GetHP() + pla.GetShieldNum(), D_EQUAL);
			}
			break;
		}
		pla.Revenge();
		ene.Revenge();
		/*if (end != 1)*/T.PlusTurn();//�^�[������
//		if (end == 1)turn--;//�^�[������
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
			printf("\a%s�͋���!!\n", name);
			SetColor();
			pla.Crit();
			SGM.ClearSF(Ene);
		}
		else if ((SGM.GetSf(Ene)) && ((ak2 == 0) || (ak2 == 1))) {
			SGM.ClearSF(Ene);
		}
		if ((SGM.GetSf(Pla)) && ((ak1 == 1) || (ak1 == 2)) && (ene.GetDmg() > 0)) {
			fcred;
			printf("\a%s�͋���!!\n", charbox);
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
		if (slowpain == 1)pla.SetDmg(pain, D_PLUS), printf("�ꂵ�݂�%s���P��!!\n", name);
		if (slowpain == 2)slowpain = 1;
		if ((ene.GetSkill(false) == 5) && (ene.GetDmg() > 50)) {
			printf("�G�̃X�L���ɂ��_���[�W���z�����ꂽ!!\n");
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
			printf("%s��", name);
			if (pla.GetTotalDmg() >= 200) {
				fcred;
			}
			else if (pla.GetTotalDmg() >= 100) {
				fcyellow;
			}
			printf("%d", pla.GetTotalDmg());
			SetColor();
			printf("�_���[�W!!");
		}
		else if (pla.GetTotalDmg() < 0) {
			printf("%s��", name);
			fccyan;
			printf("%d", pla.GetTotalDmg() * -1);
			SetColor();
			printf("��!!");
		}
		printf("\n");
		if (ene.GetTotalDmg() > 0) {
			printf("%s��", charbox);
			if (ene.GetTotalDmg() >= 200) {
				fcred;
			}
			else if (ene.GetTotalDmg() >= 100) {
				fcyellow;
			}
			printf("%d", ene.GetTotalDmg());
			SetColor();
			printf("�_���[�W!!");
		}
		else if (ene.GetTotalDmg() < 0) {
			printf("%s��", charbox);
			fccyan;
			printf("%d", ene.GetTotalDmg() * -1);
			SetColor();
			printf("��!!");
		}
		printf("\n");
		/*****************************************�_���[�W����************************************************/
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
			printf("�A�C�e���̔\�͂�HP����!!\n");
		}
		if ((nofi == 8) && ((pla.GetHpPer()) <= 0.2)) {
			pla.SetMaxHP(pla.GetHP(), D_EQUAL);
			nofi = 0;
			printf("�A�C�e���̔\�͂ōő�HP���Œ�!!\n");
		}
		if (pla.GetHP() + pla.GetShieldNum() < (ene.GetAT() * pla.GetDmgPer() / 100)) { Perform(7); }
		if ((rageHP[0][0] <= rageHP[0][1]) && rageflg[0] == false && pla.GetHP() > 0) {
			ene.SetDmgPer(50, D_PLUS);
			ene.SetCritper(25, D_PLUS);
			rageflg[0] = true;
			rageflg[1] = true;
			printf("\a%s�͌��{����!!\n", name);
			Perform(10);
		}
		if ((rageHP[1][0] <= rageHP[1][1]) && rageflg[1] == false && ene.GetHP() > 0) {
			pla.SetDmgPer(50, D_PLUS);
			pla.SetCritper(25, D_PLUS);
			rageflg[0] = true;
			rageflg[1] = true;
			printf("\a%s�͌��{����!!\n", charbox);
		}
		if ((ene.GetSkill(false) == 3) && (ene.GetHP() <= ene.GetMaxHP() / 2)) {
			ene.SetAT(ene.GetAT() / 2, D_PLUS);
			ene.SetMaxHP(ene.GetHP(), D_EQUAL);
			printf("%s�͕��􂵂�!!\n", charbox);
		}
		datalimit(1);
		if (reborneflg == 1)reborneflg = 0;
		if ((pla.GetHP() <= 0) && (data1[Mreborn] > 0)) {
			printf("\a%s�͕�������!!\n", name);
			pla.SetHP(1, D_EQUAL);
			data1[Mreborn] = data1[Mreborn] - 1;
			reborneflg = 1;
		}
		//bond = 0;
		/*		if (((chardata[0].Dmgper + spdp <= 0) || (chardata[1].Dmgper <= 0)) && end != 1) {
					end = 1;
					turn = turn / 4;
					printf("\a�o�O����!!\n");
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
				printf("\a�]��:\n");
				printf("\"�x�z\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetTrueDomi() < DM.GetE(1)) {
						if (DM.GetPerc(0) * 10.0 >= (float)a) {
							printf("��");
						}
						else {
							printf("��");
						}
					}
					else {
						printf("��");
					}
				}
				printf("%dpts/%dpts", (int)DM.GetTrueDomi(), DM.GetE(1));
				printf("\n\"���O\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetPerc(1) * 10 >= (float)a) {
						printf("��");
					}
					else {
						printf("��");
					}
				}
				printf("%dpts/%dpts", (int)DM.GetTena(), DM.GetE(2));
				printf("\n\"���o\":");
				for (a = 1; a <= 10; a++) {
					timer(50);
					if (DM.GetPerc(2) * 10 >= (float)a) {
						printf("��");
					}
					else {
						printf("��");
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
				/*�|�C���g�v�Z*/
				totalpo = (unsigned int)((DM.GetDomi() + DM.GetPerf() * 10) * (1.0 + DM.GetTena() / 100));
				/**************/
				if (nofi == 2)totalpo = totalpo * 2, printf("�A�C�e���̌��ʂŎ擾�o���l+100%%\n");
				if ((wl != WIN) && (b >= 3)) {
					if ((((stgProgress > 0) && (EM.GetEi() == stgProgress + 1)) || ((stgProgress == 0) && (EM.GetEi() <= 1))) && (stgProgress <= 6)) {
						stgProgress++;
						printf("���ɐi��!!\n");
					}
				}
				//				data.s0 = data.s0 + skpt;
				DM.SetData0(DM.CallData0() + skpt);
				skpt = (int)DM.CallData0();
				if ((skpt > MAX_SKPT) && (ac >= 4)) {
					skpt = MAX_SKPT;
					fcyellow;
					printf("\n\a��");
					fcclear;
					printf("�o���l�ɂ���Ă���ȏ�X�L�����x���͏オ��܂���B\n");
					fccyan;
					printf("\"�V���b�v\"");
					fcclear;
					printf("��");
					fccyan;
					printf("\"�X�L������\"");
					fcclear;
					printf("�𗘗p���Ă��������B\n\n");
				}
				else {
					while (skpt > MAX_SKPT) {
						if (ac >= 4) {
							ac = 4;
							skpt = MAX_SKPT;
							break;
						}
						printf("\a�X�L�����x�����A�b�v���܂����B\n\n");
						skpt -= MAX_SKPT;
						ac++;
					}
				}
				switch (wl) {
				case LOSE:
					printf("\a�G�̏����c �GHP:%d\n", ene.GetHP());
					wlpattern[1]++;
					break;

				case WIN:
					if ((((stgProgress > 0) && (EM.GetEi() == stgProgress + 1)) || ((stgProgress == 0) && (EM.GetEi() <= 1))) && (stgProgress <= 6)) {
						stgProgress++;
						printf("���ɐi��!!\n");
					}
					if (EM.GetEi() == 7) {//���X�e�[�W��
						printf("�L���̐[�w�ɑ���i�߂�c\n");
						nextStage();
						stage++;
					}
					if (EM.GetEi() == 8) {
						if (itemn[10] < 7)itemn[10]++;
						printf("��y�̋L������ɓ��ꂽ!!\n");
					}
					printf("\a%s�̏���!! �c��HP:%d\n", name, pla.GetHP());
					wlpattern[0]++;
					break;

				case DRAW:
					printf("\a��������\n");
					break;
				}
				if (stgProgress > 6)stgProgress = 6;
				printf("�����N: ");
				int oldRank = rank();
				printf("�敪��: ");
				fcyellow;
				printf("%d\n\n", getRankDiv());
				fcclear;
				calRankBonus();
				data1[Mxp] += totalpo;
				int oldPo = fpo;
				fpo += totalpo;
				printf("���݂̃|�C���g:%d +%d\n\n", fpo, fpo - oldPo);
				printf("�X�L�����x��:%d\n", (ac + 1));
				printf("�X�L���|�C���g:%.0f%%\n\n", (skpt / (float)MAX_SKPT * 100.0));
				skldata[pla.GetSkill(true) - 1] = ac;
				skdata[pla.GetSkill(true) - 1] = skpt;
				a = 0;
				calLV(data1[Mxp], &data1[MLV]);
				printf("���݂�LV:%d (+%d)\n\n", data1[MLV], (data1[MLV] - oldLvl));
				printf("\n");
				if (wl == WIN) {
					if (stage == 3) {
						printf("�{�X��|����!!\a\n");
						stgProgress = 0;
					}
				}
				timer(1000);
				printf("�f�[�^�̕ۑ����c\n");
				itemc(WRITE);
				dataSave();
#ifdef OUT_AI_RATE
				printf("\nAI���[�g:%d\n", APS.GetAIrate());
				printf("�ϓ�:");
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
					printf("�����N���i�܂�:");
					fcgreen;
					printf("%d\n\n", getRankChange() * -1);
					fcclear;
				}
				else {
					printf("�����N�~�i�܂�:");
					fcred;
					printf("%d\n\n", getRankChange());
					fcclear;
				}
#endif
				printf("��ѓK�p��̃����N\n");
				int newRank = rank();
				if (oldRank != newRank) {
					printf("%s", rankText[newRank]);
				}
				printf("�敪��: ");
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