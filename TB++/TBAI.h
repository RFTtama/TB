#pragma once
/*AI Pattern Systems made by RFTtama*/
/*RFTtama all rights recieved*/

/*define*/
//#define CHECK_AI_RATE
#define OUT_AI_RATE

#define PLUS 0
#define MINU 1
#define PRECISION 1000//To increase this value increases precision
#define AI_THINK 31//Ability of think. Increase this value makes AI weaker //dont change this value
#define AI_WIN_POINT 75.0//point
#define AI_LOST_POINT 60.0
#define AI_RATE_MAX 3000
#define AI_RATE_MIN 700
#define RESULT_RATIO 0.10
#define AIADJ_MIN 0.00
#define STREAK_POINTS 5
#define DECIDE_NUM 21
/********/

/* AI pattern systems new*/
class APSN {

private:
	unsigned _int64 logAI[4][4];
	unsigned _int64 firstCont;
	short int* ak1;
	short int* ak2;
	short int* ak;
	unsigned int kp[4];
	int AIrate;
	int oldRate;
	int rateClass;
	int AIacc;
	int AItotal;
	double AIaccTotal;
	bool rateCallFlg;
	bool AIoutputFlg;
	int streak;
	int maxRate;
	int* AIdecide;
	bool maxDecideSerched;
	int maxDecideValue;
	int maxDecideIden;
	bool screw[4][4] = {
	/*ene*/
	/*pla*/	{false, false, false, true},
			{true, false, false, false},
			{false, false, false, false},
			{false, true, false, false}
	};

	double CalAvoid(void) {
		bool strike = SGM.GetSf(Pla);
		double avd = ene.GetAvoidPer();
		double ratio = 0.1;
		if (screw[*ak1 - 1][*ak2] == true) {
			ratio += 1.0;
		}
		unsigned int max[2] = { 999, 0 };
		for (int i = 0; i < 4; i++) {
			if (max[1] < this->kp[i]) {
				max[0] = i;
				max[1] = this->kp[i];
			}
		}
		if (max[0] <= 1 && strike) {
			ratio += 4.0;
		}
		if (avd < 100) {
			ratio -= 1.0;
		}
		if (ratio < 0.0)ratio = 0.0;
		return ratio;
	}

	short int GetAk(int tag) {
		short int* k;
		switch (tag) {
		case 0:
			k = this->ak;
			break;
		case 1:
			k = this->ak1;
			break;
		case 2:
			k = this->ak2;
			break;
		default:
			k = NULL;
			strcpy_s(erstr, "Unknown argment(program error)");
			errorOutput();
			startWait();
			exit(1);
		}
		if (tag < 2) {
			return *k - 1;
		}
		else {
			return *k;
		}
	}

	void ReadAIdata(void) {
		unsigned __int64 samp;
		unsigned char a;
		if (T.GetTurn() > 0) {
			samp = this->logAI[GetAk(1)][GetAk(2)];
			for (a = 0; a < 4; a++) {
				this->kp[a] = samp & 0xffff;
				samp = samp >> 16;
			}
		}
	}

	void ReadAIdata(int k1, int k2) {
		unsigned __int64 samp;
		unsigned char a;
		if (T.GetTurn() > 0) {
			samp = this->logAI[k1][k2];
			for (a = 0; a < 4; a++) {
				this->kp[a] = samp & 0xffff;
				samp = samp >> 16;
			}
		}
	}

	void ResetStreak(void) {
		this->streak = 0;
	}

	void PlusStreak(void) {
		this->streak++;
	}

	void MinusStreak(void) {
		this->streak--;
	}

	void SerchMaxDecide(void) {
		if (!maxDecideSerched) {
			for (int i = DECIDE_NUM - 1; i >= 0; i--) {
				if (this->GetAIdecide(i) > this->maxDecideValue && this->GetAIdecide(i) > 0) {
					this->maxDecideIden = i;
					this->maxDecideValue = this->GetAIdecide(i);
				}
			}
			maxDecideSerched = true;
		}
	}

public:
	void SetAIdata(short int ak1, short int ak2, unsigned _int64 data) {
		this->logAI[ak1][ak2] = data;
	}

	void SetAk(short int* ak1p, short int* ak2p, short int* akp) {
		this->ak1 = ak1p;
		this->ak2 = ak2p;
		this->ak = akp;
	}

	short int AIpat(void) {
		unsigned int total, T;
		double pat[4] = { 0, 0, 0, 0 };
		unsigned char a;
		short int ak1;
		short int ak2;
		unsigned int kpi[4] = { 0, 0, 0, 0 };
		int rate2;
		ak1 = GetAk(1);
		ak2 = GetAk(2);
		ReadAIdata();
		kpi[0] = this->kp[3];
		if (ak2 != 1) {
			kpi[1] = this->kp[0];
		}
		else {
			kpi[0] = this->kp[0];
		}
		if (ak2 != 3) {
			kpi[3] = this->kp[1];
		}
		else {
			kpi[1] = this->kp[1];
		}
		kpi[ak2] = 0;
		int max = 0;
		for (int i = 1; i < 4; i++) {
			if (kpi[i] > kpi[max])max = i;
		}
		kpi[2] = (int)(kpi[max] * this->CalAvoid());
		kpi[ak2] = 0;
		for (a = 0, total = 0; a < 4; a++) {
			total = total + kpi[a];
		}
		rate2 = (int)((rate - 1000) * 0.015);//max:3000 :: 2000 * 0.015 = 30 ::31 /  31 - 1 = 0 :: max strength 
		if (rate2 > -1) {
			for (a = 0; a < 4; a++) {
				kpi[a] += total * (AI_THINK / (1 + rate2) - 1);
#ifdef OVER_WEIGHT_MODE
				kpi[a] *= kpi[a];
#endif
			}
		}
		else {
			for (a = 0; a < 4; a++) {
				kpi[a] += total * (AI_THINK / 1 - 1);
#ifdef OVER_WEIGHT_MODE
				kpi[a] *= kpi[a];
#endif
			}
		}
		kpi[ak2] = 0;
		for (a = 0, total = 0; a < 4; a++) {
			total = total + kpi[a];
		}
		for (a = 0; a < 4; a++) {
			pat[a] = (double)kpi[a] / total * PRECISION;
		}
		if (AIoutputFlg) {
			for (a = 0; a < 4; a++) {
				printf("%d :%.0lf%%, ", a + 1, pat[a] / 10.0);
			}
			printf("\n");
		}
		T = randnum(PRECISION) + 1;
		if (pat[0] > (float)T && ak2 != 0) {
			return 0;
		}
		else if (pat[0] + pat[1] >= (float)T && ak2 != 1) {
			return 1;
		}
		else if (pat[0] + pat[1] + pat[2] >= (float)T && ak2 != 2) {
			return 2;
		}
		if (pat[0] + pat[1] + pat[2] + pat[3] >= (float)T && ak2 != 3) {
			return 3;
		}
		else {
			strcpy_s(erstr, "AI process failed");
			errorOutput();
			exit(1);
		}
	}

	void SaveAI(void) {
		short int ak;
		short int ak1;
		int maxadr[4] = { 0, 0, 0, 0 };
		int ind = 0;
		ak = GetAk(0);
		ak1 = GetAk(1);
		ReadAIdata();
		maxadr[0] = 0;
		AItotal++;
		for (int i = 1; i < 4; i++) {
			if (kp[i] == kp[maxadr[ind]]) {
				maxadr[ind + 1] = i;
				ind++;
			}
			if (kp[i] > kp[maxadr[0]]) {
				maxadr[0] = i;
				ind = 0;
			}
		}
		for (int i = 0; i < ind + 1; i++) {
			if (maxadr[i] == ak) {
				AIacc++;
			}
		}
		this->kp[ak]++;
		unsigned _int64 samp = 0;
		unsigned char a;
		if (T.GetTurn() > 0) {
			for (a = 0; a < 3; a++) {//kp3 kp2 kp1 kp0
				samp = samp + (unsigned _int64)kp[3 - a];
				samp = samp << 16;
			}
			samp = samp + kp[0];
			this->logAI[GetAk(1)][GetAk(2)] = samp;
		}
	}

	void ResetAI(void) {
		int a, b;
		for (a = 0; a < 4; a++) {
			for (b = 0; b < 4; b++) {
				this->logAI[a][b] = 0x0001000100010001;
			}
		}
	}

	unsigned _int64 AIout(short int ak1, short int ak2) {
		return this->logAI[ak1][ak2];
	}

	void SetAIrate(int rate) {
		if (initFlg) {
			this->oldRate = 1000;
		}
		else if (rate < AI_RATE_MIN) {
			oldRate = AI_RATE_MIN;
		}
		else {
			this->oldRate = rate;
		}
	}

	int GetOldRate(void) {
		return this->oldRate;
	}

	int GetAIrate(void) {
		if (this->AIrate == 0) {
			return this->oldRate;
		}
		else {
			return this->AIrate;
		}
	}

	void SetRateClass(int value) {
		double mem1, mem3 = 0;
		if (value == LOSE)value = -1;
		if (value == WIN)value = 1;
		if (value == DRAW)value = 0;
		if (value == 1) {
			mem1 = value * AI_WIN_POINT;
		}
		else if (value == -1) {
			mem1 = value * AI_LOST_POINT;
		}
		else {
			mem1 = value;
		}
		if (GetStreak() > 1) {
			mem1 += GetStreak() * STREAK_POINTS;
		}
#ifdef CHECK_AI_RATE
		printf("Base:%.1lf\n", mem1);
#endif
		for (int i = 1; i < 3; i++) {
			if (DM.GetPerc(i) <= 1.0) {
				mem3 += DM.GetPerc(i);
			}
			else {
				mem3 += 1.0;
			}
		}
		mem3 /= 2.0;//calc average of performance
#ifdef CHECK_AI_RATE
		printf("Perform ratio:%.2lf\n", mem3);
#endif
		if (value != 0) {
			if (DM.GetPerc(0) <= 1.0) {
				mem3 *= DM.GetPerc(0);
			}
			else {
				mem3 *= 1.0;
			}
		}
#ifdef CHECK_AI_RATE
		printf("Dom:%.2lf\n", DM.GetPerc(0));
		printf("Perform ratio included dom:%.2lf\n", mem3);
#endif
		if (value == -1) {
			mem1 *= 1.0 - mem3;
		}
		else {
			mem1 *= mem3;
		}
#ifdef CHECK_AI_RATE
		printf("Base included perform ratio:%.2lf\n", mem1);
#endif
		AIaccTotal = (double)AIacc / AItotal;
		if (AIaccTotal <= 0.15) {
			ResetAI();
		}
#ifdef CHECK_AI_RATE
		printf("Accrate:%.2lf\n", AIaccTotal);
		printf("Final points:%.2lf\n", mem1);
#endif
		double aiAdj = 1.0;
		if (value == 1) {//advt
			aiAdj -= pla.CompStrength() * RESULT_RATIO;
		}
		else if (value == -1) {//dadv
			aiAdj += pla.CompStrength() * RESULT_RATIO;
		}
		if (aiAdj < AIADJ_MIN) {
			aiAdj = AIADJ_MIN;
		}
		mem1 *= aiAdj;
#ifdef CHECK_AI_RATE
		printf("Included advt: % .2lf\n", mem1);
#endif
		this->rateClass = (int)mem1;
		this->rateCallFlg = true;
	}

	void CalAIrate(void) {
		if (this->rateCallFlg) {
			int result = 0;
			int rateDiv = (this->oldRate - 1000) / 300;
			result += this->oldRate;
			result += this->rateClass;
			if (result > AI_RATE_MAX) {
				this->AIrate = AI_RATE_MAX;//determine AIrate
			}
			else if (result < AI_RATE_MIN) {
				this->AIrate = AI_RATE_MIN;
			}
			else {
				this->AIrate = result;
			}
			if (this->AIrate > 1000) {
				if ((this->oldRate - 1000) % 300 != 299 && this->rateClass > 0 && ((this->AIrate - 1000) / 300) != rateDiv) {
					rateDiv = (this->AIrate - 1000) / 300;
					AIrate = 1000 + 300 * rateDiv - 1;
				}
				else if ((this->oldRate - 1000) % 300 != 0 && this->rateClass < 0 && ((this->AIrate - 1000) / 300) != rateDiv) {
					AIrate = 1000 + 300 * rateDiv;
				}
			}
			if (this->AIrate > GetMaxRate()) {
				SetMaxRate(this->AIrate);
			}
			this->AddAIdecideData();
		}
	}

	int GetAIDiff(void) {
		return (this->AIrate - this->oldRate);
	}

	double GetAIacc(void) {
		return this->AIaccTotal;
	}

	void SetAIoutputFlg(bool boolean) {
		this->AIoutputFlg = boolean;
	}

	double GetReleasePer(void) {
		double per;
		per = (GetAIrate() - 1000.0) / 2000.0;
		if (per < 0.0) {
			per = 0.0;
		}
		return per;
	}

	void SetFirstCont(unsigned _int64 fc) {
		this->firstCont = fc;
	}

	unsigned _int64 GetFirstCont(void) {
		return this->firstCont;
	}

	void SetStreak(int stre) {
		this->streak = stre;
	}

	int GetStreak(void) {
		return this->streak;
	}

	void CalcStreak(int wl) {
		if (this->streak == 0) {
			if (wl == WIN) {
				PlusStreak();
			}
			else if (wl == LOSE) {
				MinusStreak();
			}
		}
		else if (this->streak > 0) {
			if (wl == WIN) {
				PlusStreak();
			}
			else if (wl == LOSE) {
				ResetStreak();
				MinusStreak();
			}
			else {
				ResetStreak();
			}
		}
		else if (this->streak < 0) {
			if (wl == WIN) {
				ResetStreak();
				PlusStreak();
			}
			else if (wl == LOSE) {
				MinusStreak();
			}
			else {
				ResetStreak();
			}
		}
		else {
			ResetStreak();
		}
	}

	void SetMaxRate(int value) {
		this->maxRate = value;
	}

	int GetMaxRate(void) {
		return this->maxRate;
	}

	void SetAIdecide(int* pt) {
		this->AIdecide = pt;
	}

	int GetAIdecide(int args) {
		return *(this->AIdecide + args);
	}

	void AddAIdecideData(void) {
		if (this->GetAIrate() >= 1000) {
			if (*(this->AIdecide + ((this->GetAIrate() - 1000) / 100)) < 20) {
				*(this->AIdecide + ((this->GetAIrate() - 1000) / 100)) += 1;
			}
		}
	}

	int GetMaxAIdecideRate(void) {
		SerchMaxDecide();
		return (1000 + this->maxDecideIden * 100);
	}

	int GetMaxAIdecideRateValue(void) {
		SerchMaxDecide();
		return this->maxDecideValue;
	}

	int GetMaxAIdecide(void) {
		SerchMaxDecide();
		return this->maxDecideIden;
	}

	void InitAIdecide(void) {
		for (int i = 0; i < DECIDE_NUM; i++) {
			*(AIdecide + i) = 0;
		}
	}

	int GetMaxAIdecideRank(void) {
		int rate = this->GetMaxAIdecideRate();
		if (rate >= 1000) {
			return ((rate - 1000) / 300 + 1);
		}
		else {
			return 0;
		}
	}

	int GetMaxAIdecideRankDiv(void) {
		int rate = this->GetMaxAIdecideRate();
		if (rate >= 1000) {
			return ((rate - 1000) % 300 / 100 + 1);
		}
		else {
			return 0;
		}
	}

	APSN() {//constructor
		this->AIaccTotal = 0;
		this->AIrate = 0;
		this->ak = NULL;
		this->ak1 = NULL;
		this->ak2 = NULL;
		this->AIacc = 0;
		this->AItotal = 0;
		this->oldRate = 1000;
		this->rateCallFlg = false;
		this->AIoutputFlg = false;
		this->rateClass = 0;
		this->firstCont = 0x0001000100010001;
		for (int a = 0; a < 4; a++) {
			this->kp[a] = 0;
			for (int b = 0; b < 4; b++) {
				this->logAI[a][b] = 0x0001000100010001;
			}
		}
		this->streak = 0;
		this->maxRate = 0;
		this->AIdecide = NULL;
		this->maxDecideSerched = false;
		this->maxDecideValue = -1;
		this->maxDecideIden = -1;
	}
};

APSN APS;