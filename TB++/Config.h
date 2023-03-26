#pragma once
#define TB_COMMAND_NUM 13
class tb_config {
private:

	FILE* cfgfile;
	const char cmdVer[6] = "1.1.0";
	const char commandList[TB_COMMAND_NUM][30] = { "HELLO", "EXIT", "SHOWAIRATE", "REMOVEDATA",
	"CHANGEPLAYERNAME", "HELP", "SHOWINFO", "UNLOCKDEVELOPER", "SHOWRANKDISTRIBUTION",
	"SETDISTRIBUTIONFREQUENCY", "SHOWMAXRATE", "REBOOT", "SHOWCPACHN"};
	bool unlocked;
	int distributionFrequency = -1;

	void drawLine(void) {
		printf("--------------------------------------\n");
	}

public:

	void TB_cmd_mode(void) {
		char str[256];
		int mode = -1;
		clock_t tmr;
		drawLine();
		printf("\nコマンドモード起動. Ver%s\n", cmdVer);
		printf("\"Help\"コマンドを使用することで、できることが確認できます\n\n");
		while (mode != 1) {
			printf("コマンドを入力->");
			gets_s(str, sizeof(str));
			tmr = clock();
			for (int cnt = 0; str[cnt] != '\0'; cnt++) {
				if (str[cnt] >= 97 && str[cnt] <= 122) {
					str[cnt] -= 32;
				}
			}
			for (mode = 0; mode < TB_COMMAND_NUM; mode++) {
				if (strcmp(str, commandList[mode]) == 0) {
					break;
				}
			}

			switch (mode) {
			case 0:
				printf("Hello World!!\n");
				break;

			case 1:
				printf("Bye!!\n");
				break;

			case 2:
				printf("あなたのAIrateは %d です\n", APS.GetAIrate());
				break;

			case 3:
				remove("LV.tb");
				remove("LV2.tb");
				exit(1);
				break;

			case 4:
				int len;
				do{
					printf("新しい名前を入力->");
					gets_s(name, sizeof(name));
					len = (int)strlen(name);
				} while (len > 6);
				tmr = clock();
				for (len = 0; len < 6; len++) {
					if (name[len] == '\0') {
						for (int a = len; a < 6; a++) {
							name[a] = ' ';
						}
						break;
					}
					name[6] = '\0';
				}
				printf("%s で登録されました\n", name);
				break;

			case 5:
				fccyan;
				printf("\nコマンド名\t\t | 詳細\n");
				fcclear;
				printf("Hello\t\t\t | コンピュータに挨拶します\n");
				printf("Exit\t\t\t | コマンドモードを終了します\n");
				printf("ShowAIrate\t\t | AIrateを表示します\n");
				printf("RemoveData\t\t | ゲームデータを削除します\n");
				printf("ChangePlayerName\t | プレイヤー名を変更します\n");
				printf("ShowInfo\t\t | ゲーム情報を表示します\n");
				printf("UnlockDeveloper\t\t | アンロックキーを入力して開発者モードをアクティブにします\n");
				printf("ShowRankDistribution\t | あなたのランク分布を表示します\n");
				printf("SetDistributionFrequency | ランクの最大頻度表示を変更します  \"ShowRankDistribution\"\n");
				printf("ShowMaxRate\t\t | あなたの最大到達AIrateを表示します\n");
				printf("Reboot\t\t\t | ゲームを再起動します\n");
				printf("ShowCPachN\t\t | コマンドモードの変更パッチノートを表示します\n");
				break;

			case 6:
				printf("Game Version: %d\n", VERSION);
				printf("Command mode Version: %s\n", cmdVer);
				break;

			case 7:
				char key[256];
				int ikey;
				if (this->unlocked == false) {
					printf("Enter your unlock key->");
					gets_s(key, sizeof(key));
					tmr = clock();
					ikey = atoi(key);
					if (ikey == unlock_key) {
						this->unlocked = true;
						printf("Developer mode unlocked\n");
					}
					else {
						printf("Wrong unlock key\n");
					}
				}
				else {
					printf("You are already unlocked developer mode\n");
				}
				break;

			case 8:
				if (distributionFrequency < 0) {
					distributionFrequency = APS.GetMaxAIdecideRateValue();
				}
				printf("最大 %d 回\n", APS.GetMaxAIdecideRateValue());
				printf("%d 以下の頻度を表示\n", distributionFrequency);
				printf("*それぞれのランクには壁が存在します\n");
				for (int i = 0; i < DECIDE_NUM; i++) {
					for (int j = 1; j <= 10; j++) {
						if (j <= ((APS.GetAIdecide(i) / (double)distributionFrequency) * 10.0)) {
							fcgreen;
							printf("━━");
						}
						else {
							fcclear;
							printf("━━");
						}
					}
					fcclear;
					if (i >= 20) {
						printf("\t<-- %d\t%s  div%d", 1000 + 100 * i, rankName[i / 3 + 1], i % 3 + 1);
					}
					else {
						printf("\t<-- %d - %d\t%s  div%d", 1000 + 100 * i, 1000 + 100 * (i + 1) - 1, rankName[i / 3 + 1], i % 3 + 1);
					}
					if (APS.GetMaxAIdecide() == i) {
						fcyellow;
						printf(" <--you");
						fcclear;
					}
					printf("\n");
				}
				break;

			case 9:
				if (distributionFrequency < 0) {
					distributionFrequency = APS.GetMaxAIdecideRateValue();
				}
				printf("現在の頻度表示は %d です\n", distributionFrequency);
				printf("表示したい頻度を入力してください->");
				connum(&distributionFrequency);
				tmr = clock();
				printf("%d に頻度を設定しました\n", distributionFrequency);
				break;

			case 10:
				printf("あなたの最大AIrateは %d です\n", APS.GetMaxRate());
				break;

			case 11:
				exit(1);
				break;

			case 12:
				fccyan;
				printf("\nVer 1.1.0\n");
				fcclear;
				printf("・表示言語を日本語に変更\n");
				printf("・\"ShowCPachN\"コマンドを追加\n");
				printf("\n");
				break;

			default:
				printf("不明なコマンド\n");
				break;
			}
			printf("(%dms)\n", clock() - tmr);
			printf("\n");
		}
		drawLine();
	}

	void setUnlocked(int num) {
		if (num == 1) {
			this->unlocked = true;
		}
		else {
			this->unlocked = false;
		}
	}

	int getUnlocked(void) {
		if (this->unlocked == true) {
			return 1;
		}
		else {
			return 0;
		}
	}

	tb_config() {
	}

};
tb_config cfg;