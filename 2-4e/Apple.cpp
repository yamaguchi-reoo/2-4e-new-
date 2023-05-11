#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

//コンストラクタ
Apple::Apple()
{
	//初期化
	flg = FALSE;
	type = -1;			//タイプ
	img = 0;			//画像
	location.x = 0;		//x座標
	location.y = 0;		//y座標
	erea.rate = 0;		//大きさ（当たり判定用）
	speed = 0;			//移動速度
	point = 0;			//スコア加算ポイント
	time = 0;			//りんごが出現してからの経過時間
	span = 0;			//各りんごが被らないようにするための待ち時間

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
	//もしりんごがスポーン済なら
	if (flg == TRUE)
	{
		//各りんごの速度の数だけY座標を加算する
		location.y += speed;

		//りんごが画面内にいる時間を計る
		time += 1;

		//Yが1000以上なら削除処理
		if (location.y >= 1000)
		{
			AppleDelete();
		}
	}	
}
//描画
void Apple::Draw() const
{
	if (flg == TRUE)
	{
		DrawGraph(location.x, location.y,img, TRUE);
		//当たり判定表示用
		DrawBox(location.x - (APPLE_SIZE * erea.rate), location.y - (APPLE_SIZE * erea.rate), location.x + (APPLE_SIZE * erea.rate) + APPLE_SIZE, location.y + (APPLE_SIZE * erea.rate) + APPLE_SIZE, 0x000000, FALSE);
	}
}

//スポーン処理
void Apple::Spawn()
{
	if (flg == FALSE)
	{
		//りんごの種類を抽選する
		switch (Rand())
		{
			case 0:
				flg = TRUE;
				type = 0;						//タイプ
				img = gAppleImg[0];				//画像
				location.x = GetRand(6)*150;	//x座標
				location.y = 0;					//y座標
				erea.rate = 0.1;					//大きさ（当たり判定用）
				speed = 1;						//移動速度
				point = 100;						//スコア加算ポイント
				time = 0;						//りんごが出現してからの経過時間
				span = 100;						//各りんごが被らないようにするための待ち時間						//一度にスポーンさせたりんごを計測する
				break;
			case 1:
				flg = TRUE;
				type = 1;						//タイプ
				img = gAppleImg[1];				//画像
				location.x = GetRand(6) * 150;	//x座標
				location.y = 0;					//y座標
				erea.rate = 0.1;					//大きさ（当たり判定用）
				speed = 2;						//移動速度
				point = 200;						//スコア加算ポイント
				time = 0;						//りんごが出現してからの経過時間
				span = 100;						//各りんごが被らないようにするための待ち時間
				break;
			case 2:
				flg = TRUE;
				type = 2;						//タイプ
				img = gAppleImg[2];				//画像
				location.x = GetRand(6) * 150;	//x座標
				location.y = 0;					//y座標
				erea.rate = 0.1;					//大きさ（当たり判定用）
				speed = 3.5;						//移動速度
				point = 500;						//スコア加算ポイント
				time = 0;						//りんごが出現してからの経過時間
				span = 100;						//各りんごが被らないようにするための待ち時間
				break;
			case 3:
				flg = TRUE;
				type = 3;						//タイプ
				img = gAppleImg[0];				//画像
				location.x = GetRand(6) * 150;	//x座標
				location.y = 0;					//y座標
				erea.rate = -0.1;					//大きさ（当たり判定用）
				speed = 0.5;						//移動速度
				point = -750;						//スコア加算ポイント
				time = 0;						//りんごが出現してからの経過時間
				span = 100;						//各りんごが被らないようにするための待ち時間
				break;
		}
	}
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
}
//りんごの削除
void Apple::AppleDelete() 
{
	//取得されたりんごをリセット
	flg = FALSE;
	type = 0;			//タイプ
	img = 0;			//画像
	location.x = 0;
	location.y = 0;			//座標
	erea.rate = 0;			//大きさ（当たり判定用）
	speed = 0;			//移動速度
	point = 0;			//スコア加算ポイント
	time = 0;			//りんごが出現してからの経過時間
	span = 0;			//各りんごが被らないようにするための待ち時間
}
//りんごの取得
int Apple::AppleGet()
{
	//戻り値（取得する得点数）を避難
	int t = type;
	
	//取得されたりんごをリセット
	flg = FALSE;
	type = 0;			//タイプ
	img = 0;			//画像
	location.x = 0;
	location.y = 0;			//座標
	erea.rate = 0;			//大きさ（当たり判定用）
	speed = 0;		//移動速度
	point = 0;			//スコア加算ポイント
	time = 0;			//りんごが出現してからの経過時間
	span = 0;			//各りんごが被らないようにするための待ち時間

	return t;
}
