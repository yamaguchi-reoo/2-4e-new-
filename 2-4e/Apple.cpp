#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"

Apple::Apple()
{
	images[1] = LoadGraph("Images/Apple.red.png");
	colorimage[1] = LoadGraph("Images/apple.gold");
	colorimage[2] = LoadGraph("Images/apple.poson");
	a_Count = 0;
	frame = 0;
	CheckSpawn[10] = { 0 };
}
Apple::~Apple()
{

}
void Apple::UpDate()
{
	Count = 0;
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			g_Apple[i].y += g_Apple[i].speed;
			g_Apple[i].span += 1;
			Count++;
		}
		if (g_Apple[i].y >= 500)
		{
			g_Apple[i] = g_AppleNl;
			a_Count--;
		}
	}
	if (++frame >= 25)
	{
		Spawn();
		frame = 0;
	}
}
void Apple::Draw() const
{
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			DrawCircle(g_Apple[i].x + APPLE_SIZE / 2, g_Apple[i].y + APPLE_SIZE / 2, APPLE_SIZE / 2, g_Apple[i].img, TRUE);
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x + APPLE_SIZE, g_Apple[i].y + APPLE_SIZE, 0x000000, FALSE);
		}
	}
}

void Apple::Spawn()
{
	Count = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count < ceil(MAX_APPLE - a_Count) / 2)
		{

			//ランダムなスポーンできるエリアを取得する
			int Spawn = AppleSpawn();

			//どこにもスポーンできない場合以外はりんごのスポーン処理へはいる
			if (Spawn != -1) {

				//りんごの種類を抽選する
				switch (Rand())
				{
				case 0:
					g_Apple[i] = g_AppleRd;
					g_Apple[i].x = Spawn;
					Count++;	//一度にスポーンさせたりんごを計測する
					break;
				case 1:
					g_Apple[i] = g_AppleBr;
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 2:
					g_Apple[i] = g_AppleGr;
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 3:
					g_Apple[i] = g_AppleTx;
					g_Apple[i].x = Spawn;
					Count++;
					break;
				default:	//想定していない数値が入ると白色に
					g_Apple[i] = g_AppleRd;
					g_Apple[i].img = 0xffffff;
					g_Apple[i].x = Spawn;
					break;
				}
			}
		}
	}
	a_Count += Count;	//一回で出したリンゴの個数を合計に足す
}

int Apple::Rand()
{
	int rand = GetRand(19);
	//randが0～11なら赤色（６０％）
	if (rand >= 0 && rand <= 11)
	{
		return 0;
	}
	//randが12～16なら青色（２５％）
	else if (rand > 11 && rand <= 16)
	{
		return 1;
	}
	//randが17～18なら金色（１０％）
	else if (rand > 16 && rand <= 18)
	{
		return 2;
	}
	//randが19なら紫色（毒）（５％）
	else if (rand == 19)
	{
		return 3;
	}
	//randが0～19以外の数値なら白色（想定外）
	else
	{
		return -1;
	}
}

int Apple::AppleSpawn()
{
	int SpawnPos;				// スポーンエリア
	int SpawnFlg = 1;			// スポーン出来るか判断する
	int Check[7] = { 0 };		// どこがスポーン出来ないかチェックする
	int Count = 0;				// 計測用		

	while (1) {

		do {
			SpawnPos = GetRand(6) * 150;
		} while (Check[SpawnPos / 150] == 1);

		for (int i = 0; i < MAX_APPLE; i++)
		{
			//スポーンしようとしているレーンにもうりんごがある＆スポーンしてから一定時間経っていなければ
			if (g_Apple[i].x == SpawnPos && g_Apple[i].span <= 90)
			{
				//スポーン出来ないのでチェックをいれる
				Check[SpawnPos / 150] = 1;
			}
		}
		//スポーンしようとしているレーンが空いていればそこにスポーンさせる
		if (Check[SpawnPos / 150] == 0)
		{
			return SpawnPos;
		}

		//どのレーンがスポーンできないか調べる
		for (int i = 0; i < 7; i++)
		{
			if (Check[i] == 1)
			{
				Count++;
			}
		}
		//全部のレーンでスポーン不可なら
		if (Count >= 7)
		{
			return -1;	//スポーン失敗
		}
	}
}