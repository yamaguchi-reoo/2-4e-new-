#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE	 10	//リンゴスポーン上限
#define APPLE_SIZE	100//リンゴの大きさ

class Apple :public BoxCollider
{
private:

	int a_Count;	//同時にスポーンしているりんごの数

	int frame;	//フレーム
	int Count;	//一度にスポーンしたリンゴの計測


	int gAppleImg[4];	//画像用変数
	int gGetApple[4];	//カウント用変数

	int CheckSpawn[10];	//りんごが重ならないかチェックする用

	int cnt;

	struct AppleData {
		int flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float x, y;			//座標
		float rate;			//大きさ（当たり判定用）
		float speed;		//移動速度
		int point;			//スコア加算ポイント
		int time;			//りんごが出現してからの経過時間
		int span;			//各りんごが被らないようにするための待ち時間
	};
public:
	//ランキングデータの変数宣言
	struct AppleData	g_Apple[MAX_APPLE] = { FALSE };
private:
	//imgに仮で色データをいれている
	struct AppleData	g_AppleRd = { TRUE,0,	    0,10000 ,0,  0.1, 1.0, 100,0, 90};
	struct AppleData	g_AppleBr = { TRUE,1,0x0000ff,10000 ,0,  0.1, 2.0, 200,0, 45};
	struct AppleData	g_AppleGr = { TRUE,2,0xffff00,10000 ,0,  0.1, 3.5, 500,0, 30};
	struct AppleData	g_AppleTx = { TRUE,3,0xff00ff,10000 ,0, -0.1, 0.5,-750,0,180};
	struct AppleData	g_AppleNl = {FALSE,4,	    0,10000 ,0,    0,   0,   0,0,  0};

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

	//スポーンする位置の抽選
	int AppleSpawnPos();

	//りんごの削除
	void AppleDelete(int i);

	//りんごの取得
	int AppleGet(int i);

	//取得したりんごの種類の判別
	int AppleTypeGet(int i);

	//BoxColliderに渡す数値の設定
	void SetLocation(int i);
};




