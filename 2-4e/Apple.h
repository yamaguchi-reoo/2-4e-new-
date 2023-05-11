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

		int flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float speed;		//移動速度
		int point;			//スコア加算ポイント
		int time;			//りんごが出現してからの経過時間
		int span;			//各りんごが被らないようにするための待ち時間
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

	//スポーンするりんごの種類の抽選
	int Rand();

	//りんごの削除
	void AppleDelete();

	//りんごの取得
	int AppleGet();
};




