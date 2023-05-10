#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

//コンストラクタ
Apple::Apple()
{
	//初期化
	a_Count = 0;		
	frame = 0;	

	for (int i = 0; i < 10; i++) {
		CheckSpawn[i] = 0;
		e_Apple[i].point = 0;
		e_Apple[i].pointeffect = 0;
	}
	for (int i = 0; i < 4; i++) {
		gGetApple[i] = 0;
	}

	//りんご画像の読み込み
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple red.png")) == -1)
	{
		throw "Resource/Images/apple red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/BlueApple.png")) == -1)
	{
		throw "Resource/Images/BlueApple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/applegold.png")) == -1)
	{
		throw "Resource/Images/applegold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/applepoison.png")) == -1)
	{
		throw "Resource/Images/applepoison.png";
	}
}
//デストラクタ
Apple::~Apple()
{

}

//更新
void Apple::UpDate()
{
	//一画面に存在出来るりんごの個数分繰り返す
	for (int i = 0; i < MAX_APPLE; i++)
	{
		//もしりんごがスポーン済なら
		if (g_Apple[i].flg == TRUE)
		{
			//各りんごの速度の数だけY座標を加算する
			g_Apple[i].y += g_Apple[i].speed;

			//りんごが画面内にいる時間を計る
			g_Apple[i].time += 1;

			//Yが1000以上なら削除処理
			if (g_Apple[i].y >= 1000)
			{
				AppleDelete(i);
			}
		}
		//点数取得演出用
		if (e_Apple[i].effectflg == TRUE)
		{
			if (--e_Apple[i].y <= e_Apple[i].pointeffect)
			{
				e_Apple[i].effectflg == FALSE;
			}

		}
	}	
	//25フレーム毎にりんごのスポーン処理
	if (++frame >= 25)
	{
		Spawn();
		frame = 0;
	}
}
//描画
void Apple::Draw() const
{
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			//りんごの画像がアップされたらDrawGraphの方に変更
				DrawGraph(g_Apple[i].x, g_Apple[i].y, g_Apple[i].img, TRUE);
				DrawBox(g_Apple[i].x - (APPLE_SIZE * 0.1), g_Apple[i].y - (APPLE_SIZE * 0.1), 
					(g_Apple[i].x - (APPLE_SIZE * 0.1)) + APPLE_SIZE, (g_Apple[i].y - (APPLE_SIZE * 0.1)) + APPLE_SIZE, 0x000000, FALSE);
		}
		//点数取得演出
		if (e_Apple[i].effectflg == TRUE)
		{
			DrawFormatString(e_Apple[i].x, e_Apple[i].y, 0x000000, "+%d", e_Apple[i].point);
		}
	}

	//取得したりんごの個数表示
	for (int i = 0; i < 3; i++) {
		DrawFormatString(1067+i*60, 320, 0x000000, "%.2d", gGetApple[i]);
	}
}

//スポーン処理
void Apple::Spawn()
{
	Count = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count < ceil(MAX_APPLE - a_Count) / 2)
		{

			//ランダムなスポーンできるエリアを取得する
			int Spawn = AppleSpawnPos();

			//どこにもスポーンできない場合以外はりんごのスポーン処理へはいる
			if (Spawn != -1) {

				//りんごの種類を抽選する
				switch (Rand())
				{
				case 0:
					g_Apple[i] = g_AppleRd;			//指定された色のりんごの情報を格納する
					g_Apple[i].img = gAppleImg[0];	//imgに画像を格納する
					g_Apple[i].x = Spawn;			//スポーンする場所の抽選
					Count++;						//一度にスポーンさせたりんごを計測する
					break;
				case 1:
					g_Apple[i] = g_AppleBr;
					g_Apple[i].img = gAppleImg[1];
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 2:
					g_Apple[i] = g_AppleGr;
					g_Apple[i].img = gAppleImg[2];
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 3:
					g_Apple[i] = g_AppleTx;
					g_Apple[i].img = gAppleImg[3];
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
//スポーンするりんごの種類の抽選
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
	else if (rand > 18)
	{
		return 3;
	}
	//randが0～19以外の数値なら白色（想定外）
	else
	{
		return -1;
	}
}
//スポーンする位置の抽選
int Apple::AppleSpawnPos()
{
	int SpawnPos;				// スポーンエリア
	int SpawnFlg = 1;			// スポーン出来るか判断する
	int Check[7] = {};		// どこがスポーン出来ないかチェックする
	int Count = 0;				// 計測用		

	while (1) {

		do {
			SpawnPos = GetRand(6);
		} while (Check[SpawnPos] == 1);

		for (int i = 0; i < MAX_APPLE; i++)
		{
			//スポーンしようとしているレーンにもうりんごがある＆スポーンしてから一定時間経っていなければ
			if (g_Apple[i].x == SpawnPos * 150 && g_Apple[i].time <= g_Apple[i].span)
			{
				//スポーン出来ないのでチェックをいれる
				Check[SpawnPos] = 1;
			}
		}
		//スポーンしようとしているレーンが空いていればそこにスポーンさせる
		if (Check[SpawnPos] == 0)
		{
			return SpawnPos * 150;
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
//りんごの削除
void Apple::AppleDelete(int i) {
	g_Apple[i] = g_AppleNl;
	a_Count--;
}
//りんごの取得
int Apple::AppleGet(int i)
{
	//戻り値（取得する得点数）を避難
	int p = g_Apple[i].point;
	//取得したりんごの種類を判別
	gGetApple[g_Apple[i].type]++;
	//取得演出開始
	e_Apple[i].effectflg = TRUE;
	e_Apple[i].point = g_Apple[i].point;
	e_Apple[i].pointeffect = g_Apple[i].y - 50;
	e_Apple[i].x = g_Apple[i].x;
	e_Apple[i].y = g_Apple[i].y;

	if (g_Apple[i].type == 3) {
		//毒リンゴを取得したときの処理
	
	}
	else
	{
		//毒リンゴ以外のりんごを取った時の処理
	}
	//取得されたりんごをリセット
	g_Apple[i] = g_AppleNl;
	//場に存在しているりんごの個数を減少
	a_Count--;
	return p;
}
//取得したりんごの種類の判別
int Apple::AppleTypeGet(int i)
{
	return g_Apple[i].type;
}
//BoxColliderに渡す数値の設定
void Apple::SetLocation(int i)
{
	//BoxColliderに渡す値の設定
	location.x = g_Apple[i].x;
	location.y = g_Apple[i].y;
	erea.rate = g_Apple[i].rate;
}