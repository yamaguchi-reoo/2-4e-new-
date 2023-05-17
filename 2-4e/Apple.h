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

		bool flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float speed;		//移動速度
		int point;			//スコア加算ポイント
		int time;			//りんごが出現してからの経過時間
		int span;			//各りんごが被らないようにするための待ち時間

		//点数取得エフェクト用
		bool e_flg;			//エフェクト表示フラグ
		int e_type;			//りんご種類
		int e_x;			//りんご座標
		int e_y;			//りんご種類
		int e_color;		//文字色
		float e_speed;		//移動速度
		int e_point;		//得点数
		int e_time;			//エフェクトを開始してからの時間
		int e_limit;		//エフェクトを表示しておく時間
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
	int GetAppleLocationY();

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




