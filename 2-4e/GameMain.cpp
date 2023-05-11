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
	GetPsAppleTime = 0;
	PlayerDispFlg = TRUE;
	TimerColor = GetColor(0,0,0);
	Soundflg = 0;

	//オブジェクト化
	player = new Player();
	apple = new Apple();
	score = new Score();

	//画像の読み込み
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//BGMの読み込み
	if ((MainBGM = LoadSoundMem("Resource/sounds/BGM/seiya.wav")) == -1)
	{
		throw "Resource/sounds/BGM/seiya.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(90, MainBGM);

	//サウンド読込
	if ((StartSE = LoadSoundMem("Resource/sounds/SE/Start.wav")) == -1) 
	{
		throw "Resource/sounds/SE/Start.wav";
	}
	if ((AppleSE = LoadSoundMem("Resource/sounds/SE/Apple.wav")) == -1) 
	{
		throw "Resource/sounds/SE/Apple.wav";
	}
	if ((PoisonAppleSE = LoadSoundMem("Resource/sounds/SE/ToxicApple.wav")) == -1) 
	{
		throw "Resource/sounds/SE/ToxicAplle.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(70, StartSE);
	ChangeVolumeSoundMem(100, AppleSE);
	ChangeVolumeSoundMem(100, PoisonAppleSE);


}

GameMain::~GameMain()
{
	//オブジェクトの削除
	delete player;
	delete apple;
	delete score;

	//サウンド削除
	DeleteSoundMem(MainBGM);
	DeleteSoundMem(StartSE);
	DeleteSoundMem(AppleSE);
	DeleteSoundMem(PoisonAppleSE);


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
			if (apple->HitBox(player) == true && GetPsAppleTime == 0)
			{
				//もし取得したりんごが毒なら、
				if (apple->AppleTypeGet(i) == 3)
				{
					//プレイヤーの点滅処理を開始する
					GetPsAppleTime = 1;
					PlaySoundMem(PoisonAppleSE, DX_PLAYTYPE_BACK);

				}
				else
				{
					PlaySoundMem(AppleSE, DX_PLAYTYPE_BACK);
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
		if (GetPsAppleTime > 0)
		{
			if (++GetPsAppleTime % 20 == 0)
			{
				PlayerDispFlg = !PlayerDispFlg;
			}
			if (GetPsAppleTime >= 120)
			{
				GetPsAppleTime = 0;
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
		//ここでリザルト画面へ移行（スコアはTotalScoreに、どのりんごをいくつ取得したかの内訳はGetApple[]に入っている）
		Time = 600;	//リザルト移行処理が出来たら消していい
	}
	if (Time <= 600) {
		TimerColor = GetColor(255-Time/3,0,0);
	}

	//BGM
	if (CheckSoundMem(MainBGM) == 0)
	{
		PlaySoundMem(MainBGM, DX_PLAYTYPE_BACK);
	}

	//画面切替時SE
	if (CheckSoundMem(StartSE) == 0)
	{
		if (Soundflg++ == 1)
		{
			PlaySoundMem(StartSE, DX_PLAYTYPE_BACK);
		}
	}
	return this;
	
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, ForestImg, TRUE);

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
		DrawFormatString(1120+GetRand(10-Time/30), 200+GetRand(10-Time/30), TimerColor, "%2.2d", Time / 60 + 1);
	}
	else {
		DrawFormatString(1120, 200, TimerColor, "%.2d", Time / 60 + 1);
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

