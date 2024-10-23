#pragma once

#define G1 700
#define G2 90
#define G3 250

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