#pragma once
#define G1 700
#define G2 90
#define G3 250
#define MAX_TURN 80

class TurnMan
{
private:
	int turn;
	int setturn;
	
public:
	void PlusTurn()
	{
		this->turn++;
	}
	
	int GetTurn()
	{
		return this->turn;
	}
	
	int GetSetTurn()
	{
		return this->setturn;
	}
	
	int TurnRemains()
	{
		return this->setturn - this->turn;
	}

	TurnMan() {
		this->turn = 0;
		this->setturn = MAX_TURN;
	}
};

TurnMan T;

class EnemyManage
{
private:
	int EnemyIden;
	char entityname[3][11][ENAMES] = { "ゾンビ", "狂犬", "ゴースト", "裏切者", "記憶の模倣", "悪夢", "邪神", "邪神Ⅱ", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 0*/
		"フロート", "ナル", "実験体Ⅰ","あの世の使者", "アルジオロジー", "ボイド","フィニート" ,"エル", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 1*/
		"偽りの希望", "", "", "", "", "", "", "", "霞んだ記憶", "確認不能", "闇の猟犬",/*stage 2*/
	};
public:
	int GetEi();
	void SetEI(int);
	void GetEn(int, char[ENAMES]);
};

int EnemyManage::GetEi()
{
	return this->EnemyIden;
}

void EnemyManage::SetEI(int Iden) {
	this->EnemyIden = Iden;
}

void EnemyManage::GetEn(int tag, char charbox[ENAMES]) {
	int i;
	for (i = 0; entityname[tag][this->EnemyIden][i] != '\0'; i++) {
		charbox[i] = entityname[tag][this->EnemyIden][i];
	}
	charbox[i] = '\0';
}

EnemyManage EM;

#define All 0
#define Pla 1
#define Ene 2

class SGManage {
private:
	short int MaxSG[2];
	short int NowSG[2];
	bool SF[2];
public:
	void ClearNowSG(int);
	void SetMaxSG(short int, int);
	short int GetMaxSG(int);
	void MinuMaxSG(int);
	void PlusMaxSG(int);
	void PlusNowSG(short int, int);
	short int GetNowSg(int);
	double GerPer(int);
	bool GetSf(int);
	void ClearSF(int);
};

void SGManage::ClearNowSG(int tag) {
	switch (tag) {
	case All:
		this->NowSG[0] = 0;
		this->NowSG[1] = 0;
		break;

	case Pla:
		this->NowSG[0] = 0;
		break;

	case Ene:
		this->NowSG[1] = 0;
		break;

	default:
		break;
	}
}

void SGManage::SetMaxSG(short int value, int tag) {
	switch (tag) {
	case All:
		this->MaxSG[0] = value;
		this->MaxSG[1] = value;
		pla.SetCritper(100 + value * 5, D_EQUAL);
		ene.SetCritper(100 + value * 5, D_EQUAL);
		break;

	case Pla:
		this->MaxSG[0] = value;
		ene.SetCritper(100 + value * 5, D_EQUAL);
		break;

	case Ene:
		this->MaxSG[1] = value;
		pla.SetCritper(100 + value * 5, D_EQUAL);
		break;

	default:
		break;
	}
}

short int SGManage::GetMaxSG(int tag) {
	switch (tag) {
	case Pla:
		return this->MaxSG[0];
	case Ene:
		return this->MaxSG[1];
	default:
		return -1;
	}
}

void SGManage::MinuMaxSG(int tag) {
	switch (tag) {
	case All:
		this->MaxSG[0]--;
		this->MaxSG[1]--;
		break;

	case Pla:
		this->MaxSG[0]--;
		break;

	case Ene:
		this->MaxSG[1]--;
		break;

	default:
		break;
	}
}

void SGManage::PlusMaxSG(int tag) {
	switch (tag) {
	case All:
		this->MaxSG[0]--;
		this->MaxSG[1]--;
		break;

	case Pla:
		this->MaxSG[0]--;
		break;

	case Ene:
		this->MaxSG[1]--;
		break;

	default:
		break;
	}
	if (MaxSG[0] <= 0)MaxSG[0] = 1;
	if (MaxSG[1] <= 0)MaxSG[1] = 1;
}

void SGManage::PlusNowSG(short int value, int tag) {
	switch (tag) {
	case All:
		this->NowSG[0] += value;
		this->NowSG[1] += value;
		break;

	case Pla:
		this->NowSG[0] += value;
		break;

	case Ene:
		this->NowSG[1] += value;
		break;

	default:
		break;
	}
	if (this->NowSG[0] > this->MaxSG[0])this->NowSG[0] = this->MaxSG[0];
	if (this->NowSG[1] > this->MaxSG[1])this->NowSG[1] = this->MaxSG[1];
	if (this->NowSG[0] <= -1)this->NowSG[0] = -1;
	if (this->NowSG[1] <= -1)this->NowSG[1] = -1;
}

short int SGManage::GetNowSg(int tag) {
	switch (tag) {
	case Pla:
		return this->NowSG[0];
		break;

	case Ene:
		return this->NowSG[1];
		break;

	default:
		return 0;
	}
}

double SGManage::GerPer(int tag) {
	return (double)this->NowSG[tag - 1] / this->MaxSG[tag - 1];
}

bool SGManage::GetSf(int tag) {
	switch (tag) {
	case Pla:
		if (this->MaxSG[0] == this->NowSG[0]) {
			this->SF[0] = true;
		}
		break;

	case Ene:
		if (this->MaxSG[1] == this->NowSG[1]) {
			this->SF[1] = true;
		}
		break;

	default:
		break;
	}
	return this->SF[tag - 1];
}

void SGManage::ClearSF(int tag) {
	switch (tag) {
	case All:
		this->SF[0] = false;
		this->SF[1] = false;
		this->NowSG[0] = -1;
		this->NowSG[1] = -1;
		break;

	case Pla:
		this->SF[0] = false;
		this->NowSG[0] = -1;
		break;

	case Ene:
		this->SF[1] = false;
		this->NowSG[1] = -1;
		break;

	default:
		break;
	}
}

SGManage SGM;

class DifferentManager {
private:
	int total_b;
	int E1;
	int E2;
	int E3;
	struct ScoreManager {
		float Dominate;
		float Tenacity;
		int Perform;
		float Data0;
		int Data1t3[3];
	}Score;
	bool InitFlg = false;
public:
	void SetTotal_b(int);
	void PlusTotal_b(void);
	int GetTotal_b(void);
	void SetDomi(float);
	void SetTena(float);
	void SetPerf(int);
	void InitData(void);
	void InitE(int, int, int);
	void SetData0(float);
	void SetData(int);
	void CalcData(void);
	float GetDomi(void);
	float GetTena(void);
	int GetPerf(void);
	float CallData0(void);
	int CallData(int);
	int GetE(int);
	float GetPerc(int);
	float GetTrueDomi(void);
	DifferentManager() {
		total_b = 0;
		E1 = 0;
		E2 = 0;
		E3 = 0;
		Score.Dominate = 0;
		Score.Tenacity = 0;
		Score.Perform = 0;
		Score.Data0 = 0;
		for (int a = 0; a < 3; a++) {
			Score.Data1t3[a] = 0;
		}
	}
};

void DifferentManager::SetTotal_b(int value) {
	this->total_b = value;
}

void DifferentManager::PlusTotal_b(void) {
	this->total_b++;
}

int DifferentManager::GetTotal_b(void) {
	return this->total_b;
}

void DifferentManager::SetDomi(float value) {
	this->Score.Dominate = value;
}

void DifferentManager::SetTena(float value) {
	this->Score.Tenacity = value;
}

void DifferentManager::SetPerf(int value) {
	this->Score.Perform += value;
	if (this->Score.Perform < 0)this->Score.Perform = 0;
}

void DifferentManager::InitData(void) {
	this->Score.Data0 = 0.0;
	this->Score.Data1t3[0] = 1;
	this->Score.Data1t3[1] = 1;
	this->Score.Data1t3[2] = 1000;
	this->Score.Perform = 0;
}

void DifferentManager::InitE(int e1, int e2, int e3) {
	E1 = e1;
	E2 = e2;
	E3 = e3;
}

void DifferentManager::SetData0(float value) {
	this->Score.Data0 = value;
}

void DifferentManager::SetData(int tag) {
	this->Score.Data1t3[tag - 1]++;
}

void DifferentManager::CalcData(void) {
	SetData0((float)CallData(1) / CallData(2));
	SetData0(CallData0() * CallData(3));
	SetDomi(CallData0());
}

float DifferentManager::GetDomi(void) {
	return this->Score.Dominate;
}

float DifferentManager::GetTena(void) {
	return this->Score.Tenacity;
}

int DifferentManager::GetPerf(void) {
	return this->Score.Perform;
}

float DifferentManager::CallData0(void) {
	return this->Score.Data0;
}

int DifferentManager::CallData(int tag) {
	return this->Score.Data1t3[tag - 1];
}

int DifferentManager::GetE(int tag) {
	switch (tag) {
	case 1:
		return E1;

	case 2:
		return E2;

	case 3:
		return E3;

	default:
		return 0;
	}
}

float DifferentManager::GetPerc(int tag) {
	switch (tag) {
	case 0:
		return (float)GetTrueDomi() / this->E1;

	case 1:
		return (float)GetTena() / this->E2;

	case 2:
		return (float)GetPerf() / this->E3;

	default:
		return 0.0;
	}
}

float DifferentManager::GetTrueDomi(void) {
	if (GetDomi() > 1000) {
		return this->Score.Dominate - 1000;
	}
	else {
		return 0.0;
	}
}

DifferentManager DM;