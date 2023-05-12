#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE		 10			//りんごスポーン上限
#define APPLE_SIZE		 85			//りんごの大きさ
#define APPLE_RED		 255,0,0	//赤りんごの色情報
#define APPLE_BLUE		 0,255,0	//青りんごの色情報
#define APPLE_GOLD		 255,255,0  //金りんごの色情報
#define APPLE_POISON	 255,0,255  //毒りんごの色情報

class Apple :public BoxCollider
{
private:
	int gAppleImg[4];	//画像用変数

		bool flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float speed;		//移動速度
		int point;			//スコア加算ポイント
		int time;			//りんごが出現してからの経過時間
		int span;			//各りんごが被らないようにするための待ち時間

		//点数取得エフェクト用
		bool e_flg;			//エフェクト表示フラグ
		int e_type;			//
		int e_point;
		int e_time;
		int e_limit;
public:

	//コンストラクタ
	Apple();

	//デストラクタ
	~Apple();

	//更新
	void UpDate();

	//描画
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
	int GetAppleLocationY();

	//りんごの点数取得
	int GetApplePoint();

	//りんごがスポーンしてからの経過時間取得
	int GetAppleTime();

	//各りんごのスポーン待機時間取得
	int GetAppleSpan();

	//りんごリセット
	void AppleReset();
};




