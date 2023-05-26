#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

Apple::Apple()
{
	//初期化
	Flg = FALSE;		//フラグ
	Type = -1;			//タイプ(0は赤りんごなので-1に初期化)
	Img = 0;			//画像
	location.x = 0;		//x座標
	location.y = 0;		//y座標
	erea.rate = 0;		//大きさ（当たり判定用）
	Speed = 0;			//移動速度
	Point = 0;			//スコア加算ポイント
	Time = 0;			//りんごが出現してからの経過時間
	Span = 0;			//各りんごが被らないようにするための待ち時間

	eFlg = FALSE;				//エフェクト表示フラグ
	eType = 0;					//りんご種類
	eX = 0;					//りんごX座標保存用
	eY = 0;					//りんごY座標保存用
	eColor = GetColor(0,0,0);	//文字色
	eSpeed = 0.0;				//移動速度
	ePoint = 0;				//表示する得点数
	eTime = 0;					//エフェクトを開始してからの経過時間
	eLimit = 50;				//エフェクトを表示しておく時間

	//りんご画像の読み込み
	if ((gAppleImg[0] = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/Apple_Red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/Apple_Blue.png")) == -1)
	{
		throw "Resource/Images/Apple_Blue.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/Apple_Gold.png")) == -1)
	{
		throw "Resource/Images/Apple_Gold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/Apple_Poison.png")) == -1)
	{
		throw "Resource/Images/Apple_Poison.png";
	}
}

Apple::~Apple()
{

}

void Apple::UpDate()
{
	//もしりんごがスポーン済なら
	if (Flg == TRUE)
	{
		//各りんごの速度の数だけY座標を加算する
		location.y += Speed;

		//りんごが画面内にいる時間を計る
		Time++;
	}	

	//エフェクト描画処理
	if (eFlg == TRUE)
	{
		//文字を上に動かす
		eY -= eSpeed;
		//文字が出ている時間を計る
		eTime++;
		//一定時間経ったら
		if (eTime > eLimit)
		{
			//エフェクトを消す
			eFlg = FALSE;
			//経過時間リセット		
			eTime = 0;					
		}
	}
}
void Apple::Draw() const
{
	//りんごの描画
	if (Flg == TRUE)
	{
		DrawGraph(location.x, location.y,Img, TRUE);
	}

	//エフェクトの描画
	if (eFlg == TRUE)
	{
		SetFontSize(24);
		//赤、青、金りんご取得エフェクト描画
		if (eType != 3)
		{
			DrawFormatString(eX, eY, eColor, "+%d", ePoint);
		}
		//毒りんご取得エフェクト描画（文字が震える）
		else
		{
			DrawFormatString(eX + GetRand(10)-5, eY + GetRand(10)-5 , eColor, "%d", ePoint);
		}
	}
}

void Apple::Spawn()
{
	int GetRand = Rand();			//りんご種類抽選

	//どのりんごでも変わらない項目はここで初期化
	Flg = TRUE;						//フラグ
	Type = GetRand;					//タイプ
	Img = gAppleImg[Type];			//画像
	location.y = 0;					//y座標
	Time = 0;						//りんごが出現してからの経過時間

	//りんごの種類に応じた初期化
	switch (GetRand)
	{
	case 0:	
		erea.rate = 0.1;				//大きさ（当たり判定用）
		Speed = 1;						//移動速度
		Point = 100;					//スコア加算ポイント
		Span = 100;						//各りんごが被らないようにするための待ち時間						//一度にスポーンさせたりんごを計測する
		break;
	case 1:
		erea.rate = 0.1;				//大きさ（当たり判定用）
		Speed = 2;						//移動速度
		Point = 200;					//スコア加算ポイント
		Span = 50;						//各りんごが被らないようにするための待ち時間
		break;
	case 2:
		erea.rate = 0.1;				//大きさ（当たり判定用）
		Speed = 3.5;					//移動速度
		Point = 500;					//スコア加算ポイント
		Span = 25;						//各りんごが被らないようにするための待ち時間
		break;
	case 3:
		erea.rate = -0.1;				//大きさ（当たり判定用）
		Speed = 0.5;					//移動速度
		Point = -750;					//スコア加算ポイント
		Span = 200;						//各りんごが被らないようにするための待ち時間
		break;
	}
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
	else if (rand >= 12 && rand <= 16)
	{
		return 1;
	}
	//randが17～18なら金色（１０％）
	else if (rand >= 17 && rand <= 18)
	{
		return 2;
	}
	//randが19なら紫色（毒）（５％）
	else if (rand == 19)
	{
		return 3;
	}
}

void Apple::SetLocation(int x)
{
	location.x = x;
}

int Apple::GetAppleFlg()
{
	return Flg;
}

int Apple::GetAppleType()
{
	return Type;
}

int Apple::GetAppleLocationX()
{
	return location.x;
}

int Apple::GetAppleLocationY()
{
	return location.y;
}

int Apple::GetApplePoint()
{
	return Point;
}

int Apple::GetAppleTime()
{
	return Time;
}

int Apple::GetAppleSpan()
{
	return Span;
}

void Apple::AppleReset()
{
	Flg = FALSE;		//フラグ
	Type = -1;			//タイプ
	Img = 0;			//画像
	location.x = 0;		//X座標
	location.y = 0;		//Y座標
	erea.rate = 0;		//大きさ（当たり判定用）
	Speed = 0;			//移動速度
	Point = 0;			//スコア加算ポイント
	Time = 0;			//りんごが出現してからの経過時間
	Span = 0;			//各りんごが被らないようにするための待ち時間
}

void Apple::EffectSet()
{
	eFlg = TRUE;				//フラグ（エフェクト）
	eType = Type;				//タイプ（エフェクト）
	eX = location.x;			//X座標（エフェクト）				
	eY = location.y;			//Y座標（エフェクト）		
	eColor = gAppleColor[Type];//文字色（エフェクト）
	//毒りんご以外ならりんごのスピードに応じた速度で文字が進む
	if (Type != 3)				
	{ eSpeed = Speed; }
	//毒りんごなら他のりんごと逆方向へ文字が進む
	else 
	{ eSpeed = -1; }
	ePoint = Point;			//ポイント（エフェクト）	
}