#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE		 10			//りんごスポーン上限
#define APPLE_SIZE		 85			//りんごの大きさ
#define APPLE_DISTANCE	150			//りんご同士の間隔


class Apple :public BoxCollider
{
private:
	int gAppleImg[4];	//画像用変数
	int gAppleColor[4]={0xff0000,0x00ff00,0xffff00,0xdd00dd};	//りんご色データ格納用変数

	bool Flg;			//使用フラグ
	int Type;			//タイプ
	int Img;			//画像
	float Speed;		//移動速度
	int Point;			//スコア加算ポイント
	int Time;			//りんごが出現してからの経過時間
	int Span;			//各りんごが被らないようにするための待ち時間

	//点数取得エフェクト用
	bool eFlg;			//エフェクト表示フラグ
	int eType;			//りんご種類
	int eX;			//りんご座標
	float eY;			//りんご種類
	int eColor;		//文字色
	float eSpeed;		//移動速度
	int ePoint;		//得点数
	int eTime;			//エフェクトを開始してからの時間
	int eLimit;		//エフェクトを表示しておく時間

public:

	//コンストラクタ
	Apple();

	//デストラクタ
	~Apple();

	//描画以外の更新を実行
	void UpDate();

	//描画に関することを実装
	void Draw() const;

	//スポーン処理
	void Spawn();

	//スポーンするりんごの種類抽選
	int Rand();

	//スポーンするりんごのX座標設定
	void SetLocation(int x);

	//りんごが現在スポーン中か取得
	int GetAppleFlg();

	//りんごの種類取得
	int GetAppleType();

	//りんごのX座標取得
	int GetAppleLocationX();

	//りんごのY座標取得
	float GetAppleLocationY();

	//りんごの点数取得
	int GetApplePoint();

	//りんごがスポーンしてからの経過時間取得
	int GetAppleTime();

	//各りんごのスポーン待機時間取得
	int GetAppleSpan();

	//りんごリセット
	void AppleReset();

	//エフェクト開始用設定
	void EffectSet();
};




