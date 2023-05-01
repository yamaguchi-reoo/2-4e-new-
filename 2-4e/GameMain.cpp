#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"
#include "PadInput.h"

#define TIMER 180

GameMain::GameMain()
{
	//初期化
	TotalScore = 0;
	PauseFlg = FALSE;
	PauseFlash = 0;

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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
	}

	if (PauseFlg == FALSE) {
		//処理の更新
		player->UpDate();
		apple->UpDate();
		fps->All();
		for (int i = 0; i < MAX_APPLE; i++)
		{
			apple->SetLocation(i);
			if (apple->HitBox(player) == true)
			{
				TotalScore += apple->AppleGet(i);
				//得点の下限を０にする
				if (TotalScore < 0)
				{
					TotalScore = 0;
				}
			}
		}

	}

	if (PauseFlg == TRUE)
	{
		PauseFlash++;
		if (PauseFlash > 20)
		{
			PauseFlash = 0;
		}
	}
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
	//仮のスコア描画	
	DrawFormatString(1070, 100, 0x000000, "%d",TotalScore);

	//リンゴの描画
	apple->Draw();

	if (PauseFlg == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(30);
		if (PauseFlash <= 10) {
			DrawString(370, 370, "---ポーズ中---", 0x000000, TRUE);
		}
		else if (PauseFlash > 10) {
			DrawString(370, 370, "---ポーズ中---", 0xffffff, TRUE);
		}
		SetFontSize(20);
		DrawString(390, 420, "Startボタンで再開", 0xffffff, TRUE);
	}
}

