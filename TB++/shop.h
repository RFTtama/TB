#pragma once

#define ALLITEMS 10

#define COMMON 30
#define UN_COMMON 24
#define REA 12
#define SUPER_REA 8
#define EPIQ 5
#define LEGENDARY 1
#define MYSTERY_BOX_PRICE 10000
#define SKILL_POWER_UP_PRICE 100000

class shopManager
{
private:
	int abip = 6;
	struct itemdata {
		char name[ALLITEMS][25] = { "��Ȑ�", "�r�ɓ��������t", "�����̐؂ꂽ��i", "�K���̒f��", "������",
		"�񕜖�","���߂̂�����","�~�}�L�b�g","����҂���L�b�g","���@�̂��܂��Ȃ�"};
		unsigned char itemper[ALLITEMS] = {
			LEGENDARY, EPIQ, EPIQ, SUPER_REA, SUPER_REA, REA,
			REA, REA, UN_COMMON, UN_COMMON
		};
		int itemPrice[ALLITEMS] = {
			40000, 50000, 36000, 40000, 30000, 25000, 32000, 16000, 16000, 14000
		};
	}id;
	void resetItemPer(void) {
		for (int cnt = 0; cnt < ALLITEMS; cnt++) {
			if (itemn[cnt] >= 7) {
				id.itemper[cnt] = 0;
			}
		}
	}
public:
	void shopFunc(void) {
		int spcnt, spcnt2, spcnt3;
		int nowItem = randnum(ALLITEMS);
		while (1) {
			printf("point:%d\n***���i***\n1::�s�v�c�Ȕ�:: %d�|�C���g\n", fpo, MYSTERY_BOX_PRICE);
			printf("2::�C�܂���V���b�v:: ??�|�C���g\n");
			if ((skpt >= MAX_SKPT + (MAX_SKPT * stage)) && (ac >= 4))printf("3::�X�L������\n");
			connum(&spcnt);
			if ((spcnt == 1) && (fpo >= MYSTERY_BOX_PRICE)) {//�A�C�e���X���b�g
				fpo = fpo - MYSTERY_BOX_PRICE;
				timer(1000);
				printf("3\a");
				timer(1000);
				printf("\r2\a");
				timer(1000);
				printf("\r1\a");
				timer(1000);
				printf("\ropen!!\n\n");
				resetItemPer();
				spcnt = 0;
				for (spcnt2 = 0; spcnt2 < ALLITEMS; spcnt2++) {
					spcnt = spcnt + id.itemper[spcnt2];
				}
				spcnt3 = randnum(spcnt);
				spcnt = 0;
				for (spcnt2 = 0; spcnt2 < ALLITEMS; spcnt2++) {
					spcnt = spcnt + id.itemper[spcnt2];
					if (spcnt3 < spcnt) {
						spcnt = spcnt2;
						break;
					}
				}
				if (spcnt2 >= ALLITEMS) {
					fpo += 5000;
					printf("�S�A�C�e�����ő���������Ă������߁A�ԋ��������s���܂���\n");
				}
				else {
					switch (spcnt) {
					case 0:
						printf("** Legendary **\n\a");
						printf("Item:��Ȑ�\n\n");
						printf("��ȗ͂��󂯂Đk���Ă���B ���؂������ɂ͎育��Ȍ`�B\n*�_���[�W�{����10%%��������B�o�g������HP��0�����ɂȂ����Ƃ��A2�x���������ł���B*\n");
						itemn[0]++;
						printf("������:%x\n", itemn[0]);
						break;
					case 1:
						printf("** Epiq **\n\a");
						printf("Item:�r�ɓ��������t\n\n");
						printf("��F�Ɍ��錌�B �������������Ȃ��B\n*�͂𑝋�����B�擾�o���l�y�сA�擾�|�C���g��100%%�㏸����B*\n");
						itemn[1]++;
						printf("������:%x\n", itemn[1]);
						break;
					case 2:
						printf("** Epiq **\n\a");
						printf("Item:�����̐؂ꂽ��i\n\n");
						printf("�ܖ�����������܂����v�c\n*�񕜗���20%%�㏸����B*\n");
						itemn[2]++;
						printf("������:%x\n", itemn[2]);
						break;
					case 3:
						printf("** Super Rea **\n\a");
						printf("Item:�K���̒f��\n\n");
						printf("�������K���̒f�ЁB\n*���񂾋L���̏o���m�����ƂĂ��Ȃ��㏸����B*\n");
						itemn[3]++;
						printf("������:%x\n", itemn[3]);
						break;
					case 4:
						printf("** Super Rea **\n\a");
						printf("Item:������\n\n");
						printf("�������邽�߂̖�B �ق��؂���������قǂ̕s�����B \n*�o�g������HP��0�����ɂȂ����Ƃ��A2�x���������ł���B*\n");
						itemn[4]++;
						printf("������:%x\n", itemn[4]);
						break;
					case 5:
						printf("** Rea **\n");
						printf("Text:�񕜖�\n\n");
						printf("���ނƉ񕜂����C�ɂȂ���(���͐`)�B\n*HP��50%%���������ۂ�10%%�񕜂���B*\n");
						itemn[5]++;
						printf("������:%x\n", itemn[5]);
						break;
					case 6:
						printf("** Rea **\n");
						printf("Text:���߂̂�����\n\n");
						printf("���ꂢ�����߂̂�����B\n*�}���U���ɕK�v��SG��1����B*\n");
						itemn[6]++;
						printf("������:%x\n", itemn[6]);
						break;
					case 7:
						printf("** Rea **\n");
						printf("Text:�~�}�L�b�g\n\n");
						printf("�ȈՓI�ȋ~�}�L�b�g�B\n*HP��20%%�ȉ��ɂȂ�������HP���Œ肷��B*\n");
						itemn[7]++;
						printf("������:%x\n", itemn[7]);
						break;
					case 8:
						printf("** Un common **\n");
						printf("Text:����҂���L�b�g\n\n");
						printf("�q���̂������V�їp�L�b�g�B �c���ז򂪓����Ă��肷��B\n*HP��10%%��������*\n");
						itemn[8]++;
						printf("������:%x\n", itemn[8]);
						break;
					case 9:
						printf("** Un common **\n");
						printf("Text:���@�̂��܂��Ȃ�\n\n");
						printf("�����������܂��Ȃ��c\n*�����̊m����1�񂾂������ł��邩������Ȃ��B*\n");
						itemn[9]++;
						printf("������:%x\n", itemn[9]);
						break;
					}//�����܂�
					for (spcnt = 0; spcnt < 18; spcnt++) {/*�A�C�e������18�܂�*/
						if (itemn[spcnt] > 7)/*�ۗL�ł���A�C�e���̍ő�l unsigned _int64 int = 8byte = 64bit�Ȃ̂ŁA32/18=3.5 = 3bit*/
							itemn[spcnt] = 7;/*��3bit��1�̃A�C�e���Ɏg�p�ł��܂��B3bit=7�Ȃ̂ŃA�C�e���̍ő�ۗL����7�ɂȂ�܂��B*/
					}
				}
			}
			else if (spcnt == 2) {
				printf("����̃A�C�e��: %s\n���i: %d\n", id.name[nowItem], id.itemPrice[nowItem]);
				printf("�c��̃|�C���g: %d �w�����܂���?\n�͂�:1\n", fpo);
				connum(&spcnt);
				if ((spcnt == 1) && (fpo >= id.itemPrice[nowItem]) && (itemn[nowItem] < 7)) {
					fpo -= id.itemPrice[nowItem];
					itemn[nowItem]++;
				}
			}
			else if (spcnt == 3 && ((skpt >= MAX_SKPT + (MAX_SKPT * stage)) && (ac >= 4))) {
				printf("�|�C���g������ăX�L��������ɋ������܂��B\n");
				printf("���݂̋�����p: ");
				fcred;
				printf("%d\n", (ac - 3) * SKILL_POWER_UP_PRICE);
				fcclear;
				printf("\n�������܂���?\n�͂�:1\n");
				connum(&spcnt);
				if (spcnt == 1) {
					if (ac >= 9) {
						printf("���̃X�L���͂���ȏ㋭���ł��Ȃ��悤�ł��c\n");
					}
					else if (fpo >= (ac - 3) * SKILL_POWER_UP_PRICE) {
						fpo -= (ac - 3) * SKILL_POWER_UP_PRICE;
						ac++;
						printf("�X�L�����x����1�オ����!!\n");
					}
					else if (fpo < (ac - 3) * SKILL_POWER_UP_PRICE) {
						printf("�|�C���g������܂���!!\n");
					}
				}
			}
			else {
				return;
			}
			printf("\n\n");
			itemc(WRITE);
			dataSave();
			itemc(READ);
		}
	}
}shop;