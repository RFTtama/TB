/*CharData manager made by RFTtama*/
/*RFTtama all rights recieved*/
#pragma once
#ifndef DATA_DEFINED
#define DATA_DEFINED
#define PLUSNUM 5
#define BOOSTNUM 2
#define MAX_BOOST 10
#define D_EQUAL 0
#define D_PLUS 1
#define D_MINUS 2
#define MAXDMG 200
#define NOMAL_MAGN 1.0
#define SPECL_MAGN 1.25
#define RESULT_FREE 5
#define RESULT_FREE2 10
#define DMG_RESISTANCE 50.0
#endif

class Skills {
private:
	float skillStrength[2][E_SKILL_NUM] = {
		{0, 4, 4, 4},
		{0, 5, 4, 4, 5, 5, 7, 3, 7, 5, 7, 7 }
	};
public:
	float GetSkillStrength(int identify, int skillIden) {
		if (identify == 0 && ac > 4) {
			return (this->skillStrength[identify][skillIden] + 2);
		}
		else {
			return this->skillStrength[identify][skillIden];
		}
	}
};

Skills SC;

class Data
{

	private:
		/*Character Data*/
		int identify;
		int hp;
		int at;
		int avoid;
		int avoidCnt;
		bool dmgBoost;
		bool shield;
		bool revenge;
		int shieldNum;
		int skill;
		double dmgPer;
		short int spDmgPer;
		short int critPer;
		int plusAt;
		int maxHp;
		int boostAt;
		float senses;
		float strength;
		int nowPtn;
		bool sklflg;
		double dmgPerBef;
		bool critFlg;
		double dmgResistance;
		
		int dmg;
		int calcDmg;
		int kPattern[4];
		int kDmg[4];
		Data* companion;

	public:
		/*Data Management*/
		void SetIdentify(int identify) {
			this->identify = identify;
		}

		int GetIdentify(void) {
			return this->identify;
		}

		void SetComp(Data* comp) {
			this->companion = comp;
		}

		int CalcAT(void) {
			int trueAT = this->at;
			trueAT += PLUSNUM * (this->plusAt + this->boostAt);
			return trueAT;
		}

		void AppHPlimit(void) {
			if (this->hp > this->maxHp) {
				this->hp = this->maxHp;
			}
		}

		void SetHP(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->hp = value;
				break;
			case D_PLUS:
				this->hp += value;
				break;
			case D_MINUS:
				this->hp -= value;
				break;
			}
		}

		int GetHP(void) {
			return this->hp;
		}

		void SetMaxHP(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->maxHp = value;
				break;
			case D_PLUS:
				this->maxHp -= value;
				break;
			case D_MINUS:
				this->maxHp -= value;
				break;
			}
			if (this->maxHp < 1) {
				this->maxHp = 1;
			}
		}

		int GetMaxHP(void) {
			return this->maxHp;
		}

		float GetHpPer(void) {
			return this->hp / (float)this->maxHp;
		}

		void SetAT(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->at = value;
				break;
			case D_PLUS:
				this->at += value;
				break;
			case D_MINUS:
				this->at -= value;
				break;
			}
			if (this->at <= 0) {
				this->at = 1;
			}
		}

		int GetAT(void) {
			return this->at;
		}

		void SetPlusAT(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->plusAt = value;
				break;
			case D_PLUS:
				this->plusAt += value;
				break;
			case D_MINUS:
				this->plusAt -= value;
				break;
			}
			if (this->plusAt < 0) {
				this->plusAt = 0;
			}
		}

		int GetPlusAT(void) {
			return this->plusAt + this->boostAt;
		}

		void SetSpDmgPer(short int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->spDmgPer = value;
				break;
			case D_PLUS:
				this->spDmgPer += value;
				break;
			case D_MINUS:
				this->spDmgPer -= value;
				break;
			}
		}

		short int GetSpDmgPer(void) {
			return this->spDmgPer;
		}

		int Dmgd(int at) {
			float per;
			per = (float)at - (float)this->hp / this->maxHp * at;
			return  (at - randnum((int)per));
		}

		void ResetDmg(void) {
			this->dmg = 0;
			this->calcDmg = 0;
		}

		void Dmg(void) {
			if (this->calcDmg > 0) {
				this->kDmg[companion->GetNowPtn()] += this->calcDmg;
			}
			if ((this->shieldNum > 0) && (this->calcDmg - this->shieldNum > 0) && (this->calcDmg > 0)) {
				this->calcDmg -= this->shieldNum;
				this->shieldNum = 0;
			}
			else if ((this->shieldNum > 0) && (this->calcDmg > 0)) {
				this->shieldNum -= this->calcDmg;
				this->calcDmg = 0;
			}
			this->hp -= this->calcDmg;
		}

		void SetDmg(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->dmg = value;
				break;
			case D_PLUS:
				this->dmg += value;
				break;
			case D_MINUS:
				this->dmg -= value;
				break;
			}
		}

		void CalDmg(void) {
			this->calcDmg = this->dmg;
			if (this->calcDmg > 0) {
				this->calcDmg = (int)((this->calcDmg * (this->dmgPer + this->spDmgPer)) / 100);
				if ((this->calcDmg > MAXDMG) && (this->senses > 0.0)) {
					this->calcDmg = MAXDMG;
					this->senses -= 1.0;
				}
				else if ((this->calcDmg >= 100) && (this->senses > 0.0)) {
					this->senses -= (float)0.2;
				}
				if (this->senses < 0.0) {
					this->senses = 0.0;
				}
				if (this->calcDmg <= 0) {
					this->calcDmg = 1;
				}
				this->SetDmgPer(this->calcDmg / dmgResistance, D_PLUS);
				if (this->critFlg == true) {
					this->SetDmgPer(this->calcDmg / dmgResistance, D_PLUS);
					this->critFlg = false;
				}
			}
		}

		void SetDmgResistance(double value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->dmgResistance = value;
				break;

			case D_PLUS:
				this->dmgResistance += value;
				break;

			case D_MINUS:
				this->dmgResistance -= value;
				if (this->dmgResistance < 1.0) {
					this->dmgResistance = 1.0;
				}
				break;
			}
		}

		void SetDmgPerBef(double value) {
			this->dmgPerBef += value;
		}

		double GetDmgPerInc(void) {
			return this->dmgPerBef;
		}

		int GetTotalDmg(void) {
			return this->calcDmg;
		}

		int GetDmg(void) {
			return this->dmg;
		}

		void SetDmgBoost(bool Bool) {
			this->dmgBoost = Bool;
		}

		bool GetDmgBoost(void) {
			return this->dmgBoost;
		}

		void SetShield(bool Bool) {
			this->shield = Bool;
		}

		bool GetShield(void) {
			return this->shield;
		}

		void SetShieldNum(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->shieldNum = value;
				break;
			case D_PLUS:
				this->shieldNum += value;
				break;
			case D_MINUS:
				this->shieldNum -= value;
				break;
			}
			if (this->shieldNum > 10000) {
				this->shieldNum = 10000;
			}
			if (this->shieldNum < 0) {
				this->shieldNum = 0;
			}
		}

		int GetShieldNum(void) {
			return this->shieldNum;
		}

		void Decr(void) {
			if (boostAt > 0) {
				boostAt = 0;
			}
		}

		void SetAvoidTurn(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->avoid = value;
				break;
			case D_PLUS:
				this->avoid += value;
				break;
			case D_MINUS:
				this->avoid -= value;
			}
			if (this->avoid < 1) {
				this->avoid = 1;
			}
		}

		int GetAvoid(void) {
			return this->avoid;
		}

		void ResetAvoidCnt(void) {
			avoidCnt = 0;
		}

		void PlusAvoidCnt(void) {
			if (++this->avoidCnt > this->avoid) {
				this->avoidCnt = this->avoid;
			}
		}

		double GetAvoidPer(void) {
			double per = 100.0;
			for (int i = 0; i < this->avoid; i++) {
				per /= 2.0;
			}
			for (int i = 0; i < this->avoidCnt; i++) {
				per *= 2.0;
			}
			return per;
		}

		double GetHealPer(void) {
			double per = 100.0;
			for (int i = 0; i < this->avoid; i++) {
				per /= 2.0;
			}
			for (int i = 0; i < this->avoidCnt; i++) {
				per *= 2.0;
			}
			return per;
		}

		void SetAvoid(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->avoid = value;
				break;
			case D_PLUS:
				this->avoid += value;
				break;
			case D_MINUS:
				this->avoid -= value;
				break;
			}
		}

		void SetDmgPer(double value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->dmgPer = value;
				break;
			case D_PLUS:
				this->SetDmgPerBef(value);
				this->dmgPer += value;
				break;
			case D_MINUS:
				this->dmgPer -= value;
			}
		}

		double GetDmgPer(void) {
			return this->dmgPer;
		}

		void SetCritper(int value, int formula) {
			switch (formula) {
			case D_EQUAL:
				this->critPer = value;
				break;
			case D_PLUS:
				this->critPer += value;
				break;
			case D_MINUS:
				this->critPer -= value;
				break;
			}
			if (this->critPer < 100) {
				this->critPer = 100;
			}
		}

		int GetCritPer(void) {
			return this->critPer;
		}

		void SetSkill(int value) {
			this->skill = value;
		}

		int GetSkill(bool truely) {
			if (!truely && !GetSkillFlg()) {
				return 0;
			}
			else {
				return this->skill;
			}
		}

		float GetSenses(void) {
			return this->senses;
		}

		void CalcStrength(void) {
			this->strength = (float)this->hp / 100;
			this->strength += this->shieldNum / 100;
			this->strength += (this->at + this->plusAt) / (float)7.5;
			this->strength += this->dmgBoost * 2;
			this->strength += this->shield * 2;
			this->strength += this->revenge * 3;
			this->strength += SC.GetSkillStrength(this->GetIdentify(), GetSkill(false));
		}

		float GetStrength(void) {
			return this->strength;
		}

		float CompStrength(void) {
			return this->GetStrength() - companion->GetStrength();
		}

		int ExpectResult(void) {
			if (this->strength > companion->GetStrength() + RESULT_FREE) {
				return 2;
			}
			else if (this->strength > companion->GetStrength()) {
				return 1;
			}
			else if (this->strength + RESULT_FREE < companion->GetStrength()) {
				return 4;
			}
			else if (this->strength < companion->GetStrength()) {
				return 3;
			}
			else {
				return 0;
			}
		}

		void SetRevenge(bool Bool) {
			this->revenge = Bool;
		}

		bool GetRevenge(void) {
			return this->revenge;
		}

		void PatternPlus(int ptn) {
			this->kPattern[ptn]++;
			this->nowPtn = ptn;
		}

		int GetTotalPattern(int ptn) {
			return this->kPattern[ptn];
		}

		double GetTotalPatternPer(int ptn) {
			double sum = 0;
			for (int cnt = 0; cnt < 4; cnt++) {
				sum += this->kPattern[cnt];
			}
			return this->kPattern[ptn] / sum;
		}

		int GetPatternDmg(int ptn) {
			return this->kDmg[ptn];
		}

		double GetPatternDmgPer(int ptn) {
			double sum = 0;
			for (int cnt = 0; cnt < 4; cnt++) {
				sum += this->kDmg[cnt];
			}
			return this->kDmg[ptn] / sum;
		}

		int GetNowPtn(void) {
			return this->nowPtn;
		}

		bool GetSkillFlg(void) {
			return this->sklflg;
		}

		void SetSkillFlg(bool flg) {
			this->sklflg = flg;
		}

		void AdjestStrong(void) {
			bool nsklflg[3] = { false, false, false };
			const float strength = CompStrength();
			const char cname[2][11] = { "プレイヤー", "敵" };
			if (strength <= -7) {
				SetRevenge(true);
				SetDmgBoost(true);
				SetShield(true);
				for (int i = 0; i < 3; i++) {
					nsklflg[i] = true;
				}
			}
			else if (strength <= -4) {
				SetDmgBoost(true);
				SetShield(true);
				nsklflg[0] = true;
				nsklflg[1] = true;
			}
			else if (strength <= -2) {
			switch (randnum(2)) {
				case 0:
					SetDmgBoost(true);
					nsklflg[0] = true;
					break;
				case 1:
					SetShield(true);
					nsklflg[1] = true;
					break;
				}
			}
			if (nsklflg[0] || nsklflg[1] || nsklflg[2]) {
				fcyellow;
				printf("\n難易度調整");
				fcwhite;
				printf("\n%s\n", cname[this->GetIdentify()]);
				fcyellow;
				if (nsklflg[0]) {
					printf("ダメージブースト[△]有効\n");
				}
				if (nsklflg[1]) {
					printf("シールドブースト[□]有効\n");
				}
				if (nsklflg[2]) {
					printf("リベンジブースト[▽]有効\n");
				}
				printf("\n");
				fcclear;
			}
		}

		/*Command Method*/
		void Weak(void) {
			this->SetAT(1, D_EQUAL);
			this->SetDmgBoost(false);
			this->SetShield(false);
			this->SetShieldNum(0, D_EQUAL);
			this->Decr();
			this->SetPlusAT(0, D_EQUAL);
			this->SetDmgPer(500.0, D_PLUS);
			this->SetAvoid(5, D_PLUS);
			this->ResetAvoidCnt();
		}

		void Boost(void) {
			if (this->dmgBoost == true) {
				if (this->boostAt + BOOSTNUM > MAX_BOOST) {
					this->boostAt = MAX_BOOST;
				}
				else {
					this->boostAt += BOOSTNUM;
				}
			}
		}

		void Heal(void) {
			this->SetDmg(((int)((this->GetAT() * this->GetHealPer()) / 100) * -1), D_PLUS);
			this->SetAvoidTurn(1, D_PLUS);
			this->ResetAvoidCnt();
		}

		void Shield(void) {
			if (this->shield == true) {
				this->shieldNum += 10;
			}
		}

		void Atk(void) {
			companion->SetDmg(Dmgd((int)(CalcAT() * NOMAL_MAGN)), D_PLUS);
		}

		void SpAtk(void) {
			companion->SetDmg(Dmgd((int)(CalcAT() * SPECL_MAGN)), D_PLUS);
		}

		void Ref(void) {
			companion->SetDmg(companion->Dmgd((int)(companion->GetAT() * SPECL_MAGN)), D_PLUS);
		}

		void Crit(void) {
			float fdmg = (float)this->dmg;
			if (fdmg > 0) {
				fdmg *= GetCritPer() / (float)100.0;
				this->SetDmg((int)fdmg, D_EQUAL);
				this->critFlg = true;
			}
		}

		void Revenge(void) {
			if (this->revenge == true && GetHpPer() < 0.3) {
				this->SetDmgBoost(false);
				this->boostAt = 0;
				this->SetShield(false);
				this->SetDmg(-10, D_PLUS);
			}
		}

		void ResetDmgPerBef(void) {
			this->dmgPerBef = 0;
		}

		Data() {//constructor
			this->hp = 1000;
			this->at = 50;
			this->avoid = 1;
			this->avoidCnt = 1;
			this->dmgBoost = false;
			this->shield = false;
			this->revenge = false;
			this->shieldNum = 0;
			this->skill = 0;
			this->dmgPer = 100;
			this->spDmgPer = 0;
			this->critPer = 100;
			this->plusAt = 0;
			this->maxHp = 10000;
			this->boostAt = 0;
			this->senses = 2.0;
			this->strength = 0;
			this->companion = NULL;
			this->dmg = 0;
			this->identify = -1;
			this->calcDmg = 0;
			for (int a = 0; a < 4; a++) {
				this->kPattern[a] = 0;
				this->kDmg[a] = 0;
			}
			this->nowPtn = 0;
			this->sklflg = true;
			this->dmgPerBef = 0;
			this->critFlg = false;
			this->dmgResistance = DMG_RESISTANCE;
		}

};

Data pla;
Data ene;