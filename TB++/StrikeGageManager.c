#include "StrikeGageManager.h"

/* �v���g�^�C�v�錾									*/
static void ClearNowSG(int);
static void SetMaxSG(short, int);
static short GetMaxSG(int);
static void MinusMaxSG(int);
static void PlusMaxSG(int);
static void PlusNowSG(short, int);
static short GetNowSG(int);
static double GetPercentage(int);
static unsigned char GetStrikeFlg(int);
static void ClearStrikeFlg(int);

/* �ϐ��֘A											*/
static short maxSG[2] = { -1, -1 };
static short nowSG[2] = { -1, -1 };
static unsigned char strikeFlg[2] = { 0, 0 };

/* �w�肵���^�O�̌��݂�SG���N���A����				*/
static void ClearNowSG(int tag)
{
	switch (tag) {
	case SGM_ALL:
		nowSG[0] = 0;
		nowSG[1] = 0;
		break;

	case SGM_PLA:
		nowSG[0] = 0;
		break;

	case SGM_ENE:
		nowSG[1] = 0;
		break;

	default:
		break;
	}
}

/* �ő�SG��ݒ肷��									*/
static void SetMaxSG(short value, int tag)
{
	switch (tag) {
	case SGM_ALL:
		maxSG[0] = value;
		maxSG[1] = value;
		//�����̕������O���Q�ƂȂ̂ŁA�ύX����K�v����
		pla.SetCritper(100 + value * 5, D_EQUAL);
		ene.SetCritper(100 + value * 5, D_EQUAL);
		break;

	case SGM_PLA:
		maxSG[0] = value;
		ene.SetCritper(100 + value * 5, D_EQUAL);
		break;

	case SGM_ENE:
		maxSG[1] = value;
		pla.SetCritper(100 + value * 5, D_EQUAL);
		break;

	default:
		break;
	}
}

/* �ő��SG���擾����								*/
static short GetMaxSG(int tag)
{
	switch (tag) {
	case SGM_PLA:
		return maxSG[0];
	case SGM_ENE:
		return maxSG[1];
	default:
		return -1;
	}
}

/* �ő�SG������										*/
static void MinusMaxSG(int tag)
{
	switch (tag) {
	case SGM_ALL:
		maxSG[0]--;
		maxSG[1]--;
		break;

	case SGM_PLA:
		maxSG[0]--;
		break;

	case SGM_ENE:
		maxSG[1]--;
		break;

	default:
		break;
	}
}

/* �ő�SG�𑫂�										*/
static void PlusMaxSG(int tag)
{
	switch (tag) {
	case SGM_ALL:
		maxSG[0]--;
		maxSG[1]--;
		break;

	case SGM_PLA:
		maxSG[0]--;
		break;

	case SGM_ENE:
		maxSG[1]--;
		break;

	default:
		break;
	}
	if (maxSG[0] <= 0)maxSG[0] = 1;
	if (maxSG[1] <= 0)maxSG[1] = 1;
}

/* �w�肳�ꂽ���l���������݂�SG�𑫂�				*/
static void PlusNowSG(short value, int tag)
{
	switch (tag) {
	case SGM_ALL:
		nowSG[0] += value;
		nowSG[1] += value;
		break;

	case SGM_PLA:
		nowSG[0] += value;
		break;

	case SGM_ENE:
		nowSG[1] += value;
		break;

	default:
		break;
	}
	if (nowSG[0] > maxSG[0])nowSG[0] = maxSG[0];
	if (nowSG[1] > maxSG[1])nowSG[1] = maxSG[1];
	if (nowSG[0] <= -1)nowSG[0] = -1;
	if (nowSG[1] <= -1)nowSG[1] = -1;
}

/* ���݂�SG�l���擾����								*/
static short GetNowSG(int tag)
{
	switch (tag) {
	case SGM_PLA:
		return nowSG[0];
		break;

	case SGM_ENE:
		return nowSG[1];
		break;

	default:
		return 0;
	}
}

/* ���݂�SG���ő�̉�%�����v�Z����					*/
static double GetPercentage(int tag)
{
	return (double)nowSG[tag - 1] / maxSG[tag - 1];
}

/* �X�g���C�N�t���O���I���ɂȂ��Ă��邩���擾����	*/
static unsigned char GetStrikeFlg(int tag)
{
	switch (tag) {
	case SGM_PLA:
		if (maxSG[0] == nowSG[0]) {
			strikeFlg[0] = 1;
		}
		break;

	case SGM_ENE:
		if (maxSG[1] == nowSG[1]) {
			strikeFlg[1] = 1;
		}
		break;

	default:
		break;
	}
	return strikeFlg[tag - 1];
}

/* �X�g���C�N�t���O���N���A����						*/
static void ClearStrikeFlg(int tag)
{
	switch (tag) {
	case SGM_ALL:
		strikeFlg[0] = 0;
		strikeFlg[1] = 0;
		nowSG[0] = -1;
		nowSG[1] = -1;
		break;

	case SGM_PLA:
		strikeFlg[0] = 0;
		nowSG[0] = -1;
		break;

	case SGM_ENE:
		strikeFlg[1] = 0;
		nowSG[1] = -1;
		break;

	default:
		break;
	}
}