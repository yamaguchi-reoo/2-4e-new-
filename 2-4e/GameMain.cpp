#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"
#include "PadInput.h"

GameMain::GameMain()
{
	//初期化
	TotalScore = 0;
	PauseFlg = FALSE;
	PauseFlash = 0;
	Time = 3599;
	GetTxAppleTime = 0;
	PlayerDispFlg = TRUE;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		GetApple[i] = 0;
	}

	//オブジェクト化
	player = new Player();
	apple = new Apple();
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
	delete score;

}

AbstractScene* GameMain::Update()
{
	//ポーズフラグ切り替え処理
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
	}
	//ポーズ中でないなら
	if (PauseFlg == FALSE) {
		//処理の更新
		player->UpDate();
		apple->UpDate();

		for (int i = 0; i < MAX_APPLE; i++)
		{
			apple->SetLocation(i);
			if (apple->HitBox(player) == true && GetTxAppleTime == 0)
			{
				//もし取得したりんごが毒なら、
				if (apple->AppleTypeGet(i) == 3)
				{
					//プレイヤーの点滅処理を開始する
					GetTxAppleTime = 1;
				}
				TotalScore += apple->AppleGet(i);
				//得点の下限を０にする
				if (TotalScore < 0)
				{
					TotalScore = 0;
				}
			}
		}
		//点滅中の処理
		if (GetTxAppleTime > 0)
		{
			if (++GetTxAppleTime % 20 == 0)
			{
				PlayerDispFlg = !PlayerDispFlg;
			}
			if (GetTxAppleTime >= 120)
			{
				GetTxAppleTime = 0;
			}
		}
		//制限時間減少
		Time--;
	}

	if (PauseFlg == TRUE)
	{
		PauseFlash++;
		if (PauseFlash > 20)
		{
			PauseFlash = 0;
		}
	}
	if (Time <= 0)
	{
		//ここでリザルト画面へ移行（スコアはTotarScoreに、どのりんごをいくつ取得したかの内訳はGetApple[]に入っている）
		Time = 600;	//リザルト移行処理が出来たら消していい
	}
	return this;
	
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, mori_img, TRUE);

	//プレイヤーの描画
	if (PlayerDispFlg == TRUE) {
		player->Draw();
	}

	//スコアの描画
	score->Draw();
	//仮のスコア描画	
	SetFontSize(30);
	DrawString(1105, 450, "得点", 0x000000);
	DrawFormatString(1095, 500, 0x000000, "%.5d",TotalScore);
	SetFontSize(24);

	//制限時間
	SetFontSize(30);
	DrawString(1075, 150, "制限時間", 0x000000);
	SetFontSize(40);
	//5秒を切ると文字が揺れる
	if (Time <= 300) {
		DrawFormatString(1120+GetRand(10-Time/30), 200+GetRand(10-Time/30), 0x000000, "%2.2d", Time / 60 + 1);
	}
	else {
		DrawFormatString(1120, 200, 0x000000, "%.2d", Time / 60 + 1);
	}
	SetFontSize(24);

	//リンゴの描画
	apple->Draw();

	//一時停止中の描画
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
		SetFontSize(24);
	}
}

