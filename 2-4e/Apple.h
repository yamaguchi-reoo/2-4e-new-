#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE	 10	//リンゴスポーン上限
#define APPLE_SIZE	100//リンゴの大きさ

class Apple :public BoxCollider
{
private:

	int a_Count;	//同時にスポーンしているりんごの数
	int AppleScore;	//得点数

	int frame;	//フレーム
	int Count;	//一度にスポーンしたリンゴの計測

	int gAppleImg[4];

	int CheckSpawn[10];	//りんごが重ならないかチェックする

	struct AppleData {
		int flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float x, y;			//座標
		float rate;			//大きさ（当たり判定用）
		float speed;		//移動速度
		int point;			//スコア加算ポイント
		int span;			//画像被りをなくす用
	};
public:
	//ランキングデータの変数宣言
	struct AppleData	g_Apple[MAX_APPLE] = { FALSE };
private:
	//imgに仮で色データをいれている
	struct AppleData	g_AppleRd = { TRUE,0,		0,0 ,0, 1.1, 1.0, 100,0};
	struct AppleData	g_AppleBr = { TRUE,1,0x0000ff,0	,0, 1.1, 2.0, 200,0 };
	struct AppleData	g_AppleGr = { TRUE,2,0xffff00,0 ,0, 1.1, 3.5, 500,0 };
	struct AppleData	g_AppleTx = { TRUE,3,0xff00ff,0 ,0, 0.9, 0.5,-750,0 };
	struct AppleData	g_AppleNl = { FALSE,4,	    0,0 ,0, 0  , 0  , 0 };

public:
	//コンストラクタ
	Apple();

	//デストラクタ
	~Apple();

	//更新
	void UpDate();

	//描画
	void Draw() const;

	//りんごのスポーン
	void Spawn();

	//りんごのスポーン確率用
	int Rand();

	//りんごがスポーン可能か判断
	int AppleSpawn();

	//りんご削除
	void AppleDelete(int i);

	//りんご入手
	int AppleGet(int i);

	//BoxColliderで使う用の箱に格納する
	void SetLocation(int i);
};




