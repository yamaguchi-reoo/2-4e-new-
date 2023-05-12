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

	e_flg = FALSE;				//エフェクト表示フラグ
	e_type = 0;					//りんご種類
	e_x = 0;					//りんごX座標
	e_y = 0;					//りんごY
	e_color = GetColor(0,0,0);	//文字色
	e_speed = 0.0;				//移動速度
	e_point = 0;				//得点数
	e_time = 0;					//エフェクトを開始してからの時間
	e_limit = 0;				//エフェクトを表示しておく時間

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
		time++;
	}	

	//エフェクトが描画中なら
	if (e_flg == TRUE)
	{
		e_y -= e_speed;
		e_time++;
		if (e_time > e_limit)
		{
			e_flg = FALSE;
		}
	}
}
//描画
void Apple::Draw() const
{
	//りんごの描画
	if (flg == TRUE)
	{
		DrawGraph(location.x, location.y,img, TRUE);
		//当たり判定表示用
		DrawBox(location.x - (APPLE_SIZE * erea.rate), location.y - (APPLE_SIZE * erea.rate), location.x + (APPLE_SIZE * erea.rate) + APPLE_SIZE, location.y + (APPLE_SIZE * erea.rate) + APPLE_SIZE, 0x000000, FALSE);
	}
	//エフェクトの描画
	if (e_flg == TRUE)
	{
		if (e_type != 3)
		{
			DrawFormatString(e_x, e_y, e_color, "+%d", e_point);
		}
		else
		{
			DrawFormatString(e_x + GetRand(10)-5, e_y + GetRand(10)-5 , e_color, "%d", e_point);
		}
	}
}

//スポーン処理
void Apple::Spawn()
{
	int GetRand = Rand();			//りんご種類抽選
	flg = TRUE;						//フラグ
	type = GetRand;					//タイプ
	img = gAppleImg[type];			//画像
	location.y = 0;					//y座標
	time = 0;						//りんごが出現してからの経過時間

	//りんごの種類を抽選する
	switch (GetRand)
	{
	case 0:	
		erea.rate = 0.1;				//大きさ（当たり判定用）
		speed = 1;						//移動速度
		point = 100;					//スコア加算ポイント
		span = 100;						//各りんごが被らないようにするための待ち時間						//一度にスポーンさせたりんごを計測する
		break;
	case 1:
		erea.rate = 0.1;				//大きさ（当たり判定用）
		speed = 2;						//移動速度
		point = 200;					//スコア加算ポイント
		span = 50;						//各りんごが被らないようにするための待ち時間
		break;
	case 2:
		erea.rate = 0.1;				//大きさ（当たり判定用）
		speed = 3.5;					//移動速度
		point = 500;					//スコア加算ポイント
		span = 25;						//各りんごが被らないようにするための待ち時間
		break;
	case 3:
		erea.rate = -0.1;				//大きさ（当たり判定用）
		speed = 0.5;					//移動速度
		point = -750;					//スコア加算ポイント
		span = 150;						//各りんごが被らないようにするための待ち時間
		break;
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

//りんごのY座標設定
void Apple::SetLocation(int x)
{
	location.x = x;
}

//りんごが現在スポーン中か取得
int Apple::GetAppleFlg()
{
	return flg;
}

//りんごの種類取得
int Apple::GetAppleType()
{
	return type;
}

//りんごのX座標取得
int Apple::GetAppleLocationX()
{
	return location.x;
}

//りんごのY座標取得
int Apple::GetAppleLocationY()
{
	return location.y;
}

//りんごの点数取得
int Apple::GetApplePoint()
{
	return point;
}

//りんごがスポーンしてからの経過時間取得
int Apple::GetAppleTime()
{
	return time;
}

//各りんごのスポーン待機時間取得
int Apple::GetAppleSpan()
{
	return span;
}

//りんごリセット
void Apple::AppleReset()
{
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
}

//エフェクト開始用設定
void Apple::EffectSet()
{
	e_flg = TRUE;
	e_type = type;					
	e_x = location.x;					
	e_y = location.y;					
	e_color = gAppleColor[type];
	e_speed = speed;
	if (type == 3)e_speed = -1;
	e_point = point;
	e_time = 0;	
	e_limit = 50;
}