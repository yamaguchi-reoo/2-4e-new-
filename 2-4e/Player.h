#pragma once
#include "BoxCollider.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100
#define WALK_SPEED  4

enum class PLAYER_STATE {
	IDOL = 0,
	WALK_RIGHT,
	WALK_LEFT,

};

class Player :public BoxCollider
{
private:

	PLAYER_STATE PlayerState;	// プレイヤーの現在の状態を制御

	int Speed;			//移動速度
	int AccelerationRight;	//加速度（右）
	int AccelerationLeft;	//加速度（左）


private:

	int PlayerWalkImg[9];		//プレイヤー歩行画像格納用
	int Cnt;		//アニメーション切り替え用
	int CntWait;	//アニメーション切り替え待ち時間測定用
	int Vector;
	int FrontImg;

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void UpDate();

	//描画
	void Draw() const;
};


