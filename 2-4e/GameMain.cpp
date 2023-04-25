#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"

#define TIMER 180

GameMain::GameMain()
{
	//初期化
	TotalScore = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		GetApple[i] = 0;
	}

	//オブジェクト化
	player = new Player();
	apple = new Apple();
	fps = new FpsController();
	score = new Score();

	//画像の読み込み
	if ((mori_img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}

}

GameMain::~GameMain()
{
	//オブジェクトの削除
	delete player;
	delete apple;
	delete fps;
	delete score;

}

AbstractScene* GameMain::Update()
{
	//処理の更新
	player->UpDate();
	apple->UpDate();
	fps->All();

	return this;
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, mori_img, TRUE);

	//プレイヤーの描画
	player->Draw();

	fps->Disp();

	//スコアの描画
	score->Draw();

	//リンゴの描画
	apple->Draw();
}

