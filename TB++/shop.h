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
		char name[ALLITEMS][25] = { "奇妙な石", "瓶に入った血液", "期限の切れた薬品", "幸せの断片", "復活薬",
		"回復薬","琥珀のかけら","救急キット","お医者さんキット","魔法のおまじない"};
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
			printf("point:%d\n***商品***\n1::不思議な箱:: %dポイント\n", fpo, MYSTERY_BOX_PRICE);
			printf("2::気まぐれショップ:: ??ポイント\n");
			if ((skpt >= MAX_SKPT + (MAX_SKPT * stage)) && (ac >= 4))printf("3::スキル強化\n");
			connum(&spcnt);
			if ((spcnt == 1) && (fpo >= MYSTERY_BOX_PRICE)) {//アイテムスロット
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
					printf("全アイテムを最大個数所持していたため、返金処理を行いました\n");
				}
				else {
					switch (spcnt) {
					case 0:
						printf("** Legendary **\n\a");
						printf("Item:奇妙な石\n\n");
						printf("奇妙な力を受けて震えている。 水切りをするには手ごろな形。\n*ダメージ倍率が10%%減少する。バトル中のHPが0未満になったとき、2度だけ復活できる。*\n");
						itemn[0]++;
						printf("所持数:%x\n", itemn[0]);
						break;
					case 1:
						printf("** Epiq **\n\a");
						printf("Item:瓶に入った血液\n\n");
						printf("銀色に光る血。 多分おいしくない。\n*力を増強する。取得経験値及び、取得ポイントが100%%上昇する。*\n");
						itemn[1]++;
						printf("所持数:%x\n", itemn[1]);
						break;
					case 2:
						printf("** Epiq **\n\a");
						printf("Item:期限の切れた薬品\n\n");
						printf("賞味期限だからまだ大丈夫…\n*回復率が20%%上昇する。*\n");
						itemn[2]++;
						printf("所持数:%x\n", itemn[2]);
						break;
					case 3:
						printf("** Super Rea **\n\a");
						printf("Item:幸せの断片\n\n");
						printf("失った幸せの断片。\n*霞んだ記憶の出現確率がとてつもなく上昇する。*\n");
						itemn[3]++;
						printf("所持数:%x\n", itemn[3]);
						break;
					case 4:
						printf("** Super Rea **\n\a");
						printf("Item:復活薬\n\n");
						printf("復活するための薬。 ほっぺたが落ちるほどの不味さ。 \n*バトル中のHPが0未満になったとき、2度だけ復活できる。*\n");
						itemn[4]++;
						printf("所持数:%x\n", itemn[4]);
						break;
					case 5:
						printf("** Rea **\n");
						printf("Text:回復薬\n\n");
						printf("飲むと回復した気になれる薬(実は青汁)。\n*HPが50%%減少した際に10%%回復する。*\n");
						itemn[5]++;
						printf("所持数:%x\n", itemn[5]);
						break;
					case 6:
						printf("** Rea **\n");
						printf("Text:琥珀のかけら\n\n");
						printf("きれいな琥珀のかけら。\n*急所攻撃に必要なSGが1減る。*\n");
						itemn[6]++;
						printf("所持数:%x\n", itemn[6]);
						break;
					case 7:
						printf("** Rea **\n");
						printf("Text:救急キット\n\n");
						printf("簡易的な救急キット。\n*HPが20%%以下になった時にHPを固定する。*\n");
						itemn[7]++;
						printf("所持数:%x\n", itemn[7]);
						break;
					case 8:
						printf("** Un common **\n");
						printf("Text:お医者さんキット\n\n");
						printf("子供のごっこ遊び用キット。 …風邪薬が入ってたりする。\n*HPが10%%増加する*\n");
						itemn[8]++;
						printf("所持数:%x\n", itemn[8]);
						break;
					case 9:
						printf("** Un common **\n");
						printf("Text:魔法のおまじない\n\n");
						printf("懐かしいおまじない…\n*少しの確率で1回だけ復活できるかもしれない。*\n");
						itemn[9]++;
						printf("所持数:%x\n", itemn[9]);
						break;
					}//ここまで
					for (spcnt = 0; spcnt < 18; spcnt++) {/*アイテム総数18個まで*/
						if (itemn[spcnt] > 7)/*保有できるアイテムの最大値 unsigned _int64 int = 8byte = 64bitなので、32/18=3.5 = 3bit*/
							itemn[spcnt] = 7;/*約3bitを1つのアイテムに使用できます。3bit=7個なのでアイテムの最大保有数は7個になります。*/
					}
				}
			}
			else if (spcnt == 2) {
				printf("今回のアイテム: %s\n価格: %d\n", id.name[nowItem], id.itemPrice[nowItem]);
				printf("残りのポイント: %d 購入しますか?\nはい:1\n", fpo);
				connum(&spcnt);
				if ((spcnt == 1) && (fpo >= id.itemPrice[nowItem]) && (itemn[nowItem] < 7)) {
					fpo -= id.itemPrice[nowItem];
					itemn[nowItem]++;
				}
			}
			else if (spcnt == 3 && ((skpt >= MAX_SKPT + (MAX_SKPT * stage)) && (ac >= 4))) {
				printf("ポイントを消費してスキルをさらに強化します。\n");
				printf("現在の強化費用: ");
				fcred;
				printf("%d\n", (ac - 3) * SKILL_POWER_UP_PRICE);
				fcclear;
				printf("\n強化しますか?\nはい:1\n");
				connum(&spcnt);
				if (spcnt == 1) {
					if (ac >= 9) {
						printf("このスキルはこれ以上強化できないようです…\n");
					}
					else if (fpo >= (ac - 3) * SKILL_POWER_UP_PRICE) {
						fpo -= (ac - 3) * SKILL_POWER_UP_PRICE;
						ac++;
						printf("スキルレベルが1上がった!!\n");
					}
					else if (fpo < (ac - 3) * SKILL_POWER_UP_PRICE) {
						printf("ポイントが足りません!!\n");
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