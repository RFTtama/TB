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
		printf("\n�R�}���h���[�h�N��. Ver%s\n", cmdVer);
		printf("\"Help\"�R�}���h���g�p���邱�ƂŁA�ł��邱�Ƃ��m�F�ł��܂�\n\n");
		while (mode != 1) {
			printf("�R�}���h�����->");
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
				printf("���Ȃ���AIrate�� %d �ł�\n", APS.GetAIrate());
				break;

			case 3:
				remove("LV.tb");
				remove("LV2.tb");
				exit(1);
				break;

			case 4:
				int len;
				do{
					printf("�V�������O�����->");
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
				printf("%s �œo�^����܂���\n", name);
				break;

			case 5:
				fccyan;
				printf("\n�R�}���h��\t\t | �ڍ�\n");
				fcclear;
				printf("Hello\t\t\t | �R���s���[�^�Ɉ��A���܂�\n");
				printf("Exit\t\t\t | �R�}���h���[�h���I�����܂�\n");
				printf("ShowAIrate\t\t | AIrate��\�����܂�\n");
				printf("RemoveData\t\t | �Q�[���f�[�^���폜���܂�\n");
				printf("ChangePlayerName\t | �v���C���[����ύX���܂�\n");
				printf("ShowInfo\t\t | �Q�[������\�����܂�\n");
				printf("UnlockDeveloper\t\t | �A�����b�N�L�[����͂��ĊJ���҃��[�h���A�N�e�B�u�ɂ��܂�\n");
				printf("ShowRankDistribution\t | ���Ȃ��̃����N���z��\�����܂�\n");
				printf("SetDistributionFrequency | �����N�̍ő�p�x�\����ύX���܂�  \"ShowRankDistribution\"\n");
				printf("ShowMaxRate\t\t | ���Ȃ��̍ő哞�BAIrate��\�����܂�\n");
				printf("Reboot\t\t\t | �Q�[�����ċN�����܂�\n");
				printf("ShowCPachN\t\t | �R�}���h���[�h�̕ύX�p�b�`�m�[�g��\�����܂�\n");
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
				printf("�ő� %d ��\n", APS.GetMaxAIdecideRateValue());
				printf("%d �ȉ��̕p�x��\��\n", distributionFrequency);
				printf("*���ꂼ��̃����N�ɂ͕ǂ����݂��܂�\n");
				for (int i = 0; i < DECIDE_NUM; i++) {
					for (int j = 1; j <= 10; j++) {
						if (j <= ((APS.GetAIdecide(i) / (double)distributionFrequency) * 10.0)) {
							fcgreen;
							printf("����");
						}
						else {
							fcclear;
							printf("����");
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
				printf("���݂̕p�x�\���� %d �ł�\n", distributionFrequency);
				printf("�\���������p�x����͂��Ă�������->");
				connum(&distributionFrequency);
				tmr = clock();
				printf("%d �ɕp�x��ݒ肵�܂���\n", distributionFrequency);
				break;

			case 10:
				printf("���Ȃ��̍ő�AIrate�� %d �ł�\n", APS.GetMaxRate());
				break;

			case 11:
				exit(1);
				break;

			case 12:
				fccyan;
				printf("\nVer 1.1.0\n");
				fcclear;
				printf("�E�\���������{��ɕύX\n");
				printf("�E\"ShowCPachN\"�R�}���h��ǉ�\n");
				printf("\n");
				break;

			default:
				printf("�s���ȃR�}���h\n");
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