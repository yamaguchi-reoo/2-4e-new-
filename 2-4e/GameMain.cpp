#include "DxLib.h"
#include <math.h>
#include "GameMain.h"
#include "Result.h"
#include "PadInput.h"
#include "FpsController.h"

GameMain::GameMain()
{
	//初期化
	frame = 0;
	Time = 60;
	Timer = 0;
	TotalScore = 0;

	for (int i = 0; i < 4; i++) {
		gGetApple[i] = 0;
	}
	for (int i = 0; i < 7; i++) {
		CheckSpawn[i] = FALSE;
	}

	gGetAppleType = 0;
	PauseFlashTime = 0;
	GetPsAppleTime = 0;
	SpawnPos = 0;
	a_Count = 0;
	SpawnCount = 0;
	SpawnApple = 0;

	SpawnFlg = FALSE;
	PauseFlashFlg = FALSE;
	GetPsAppleFlg = FALSE;
	PlayerDispFlg = TRUE;
	PauseFlg = FALSE;

	TimerColor = GetColor(0, 0, 0);

	//オブジェクト化
	player = new Player();
	for (int i = 0; i < MAX_APPLE; i++) {
		apple[i] = new Apple();
	}
	fps = new FpsController();

	//フォントの追加
	MainFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 30, 6, DX_FONTTYPE_ANTIALIASING);
	MainFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 40, 6, DX_FONTTYPE_ANTIALIASING);
	MainFont3 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 20, 6, DX_FONTTYPE_ANTIALIASING);

	//画像の読み込み
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//りんご画像の読み込み
	if ((gAppleImg[0] = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/Apple_Red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/Apple_Blue.png")) == -1)
	{
		throw "Resource/Images/Apple_Blue.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/Apple_Gold.png")) == -1)
	{
		throw "Resource/Images/Apple_Gold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/Apple_Poison.png")) == -1)
	{
		throw "Resource/Images/Apple_Poison.png";
	}

	//BGMの読み込み
	if ((MainBGM = LoadSoundMem("Resource/sounds/BGM/seiya.wav")) == -1)
	{
		throw "Resource/sounds/BGM/seiya.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(160, MainBGM);

	//SEの読込
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
	ChangeVolumeSoundMem(140, StartSE);
	ChangeVolumeSoundMem(140, AppleSE);
	ChangeVolumeSoundMem(140, PoisonAppleSE);

	//画面切替時SE
	if (CheckSoundMem(StartSE) == 0)
	{
		PlaySoundMem(StartSE, DX_PLAYTYPE_BACK);
	}
}

GameMain::~GameMain()
{
	//オブジェクトの削除
	delete player;
	for (int i = 0; i < MAX_APPLE; i++) {
		delete apple[i];
	}
	
	StopSoundMem(MainBGM);
	//サウンド削除
	DeleteSoundMem(StartSE);
	DeleteSoundMem(AppleSE);
	DeleteSoundMem(PoisonAppleSE);

	//フォント削除
	DeleteFontToHandle(MainFont1);
	DeleteFontToHandle(MainFont2);
	DeleteFontToHandle(MainFont3);

}

AbstractScene* GameMain::Update()
{
	//ポーズフラグ切り替え処理
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
		StopSoundMem(MainBGM);
	}

	//ポーズ中でないなら
	if (PauseFlg == FALSE) {
		//BGM
		if (CheckSoundMem(MainBGM) == 0)
		{
			PlaySoundMem(MainBGM, DX_PLAYTYPE_LOOP, FALSE);
		}

		//処理の更新
		player->UpDate();

		for (int i = 0; i < MAX_APPLE; i++) 
		{
			apple[i]->UpDate();
			//りんごがスポーンしてから一定時間立っていれば
			if (apple[i]->GetAppleFlg() == TRUE && apple[i]->GetAppleTime() == apple[i]->GetAppleSpan())
			{
				//スポーン可能に
				CheckSpawn[apple[i]->GetAppleLocationX()/ APPLE_DISTANCE] = FALSE;
			}

			//りんごとプレイヤーが接触して、プレイヤーが点滅状態でないならりんご取得処理へ
			if (apple[i]->HitBox(player) == TRUE && GetPsAppleTime == 0)
			{
				AppleGet(i);
				//画面にあるりんごの個数を減少
				a_Count--;
			}
			//りんごのYが1000以上なら削除（リセット）
			if (apple[i]->GetAppleLocationY() >= 1000)
			{
				//りんごをリセット
				apple[i]->AppleReset();
				//画面にあるりんごの個数を減少
				a_Count--;
			}

		}
		//25フレーム毎にりんご生成処理
		if (++frame >= 25)
		{
			SpawnCount = 0;
			//一回にスポーン出来るりんごの数だけ繰り返し
			for (int i = 0; i < ceil((MAX_APPLE-a_Count)/2); i++)
			{
				//生成処理
				AppleSpawn();
			}
			//画面にあるりんごの個数を増加
			a_Count+=SpawnCount;
			//25フレーム数えなおし
			frame = 0;
		}
		//点滅中の処理
		if (GetPsAppleFlg == TRUE)
		{
			if (++GetPsAppleTime % 20 == 0)
			{
				PlayerDispFlg = !PlayerDispFlg;
			}
			if (GetPsAppleTime >= 120)
			{
				GetPsAppleFlg = FALSE;
				GetPsAppleTime = 0;
			}
		}
		//制限時間減少
		if (++Timer >= 28)
		{
			--Time;
			Timer = 0;
		}
	}

	//一時停止中
	if (PauseFlg == TRUE)
	{
		if (++PauseFlashTime >= 10)
		{
			PauseFlashFlg = !PauseFlashFlg;
			PauseFlashTime = 0;
		}
	}
	//時間切れ後のリザルト移行処理
	if (Time <= 0)
	{
		return new Result(gGetApple,TotalScore);
	}

	//制限時間が１０秒を切ったら残り時間に応じて文字色を変えていく
	if (Time <= 10) {
		TimerColor = GetColor(255,0,0);
	}

	return this;
	
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, ForestImg, TRUE);

	// スコアの描画
	DrawBox(1000, 0, 1280, 720, 0xffffff, TRUE);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(1080 + i * 60, 370, 0.5f, 0, gAppleImg[i], TRUE, FALSE);
		DrawFormatStringToHandle(1067 + i * 60, 320, 0x000000,MainFont3, "%.2d", gGetApple[i]);
	}

	DrawStringToHandle(1105, 450, "得点", 0x000000,MainFont1);
	DrawFormatStringToHandle(1095, 500, 0x000000, MainFont1,"%.5d", TotalScore);

	//取得りんご
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);

	//制限時間
	DrawStringToHandle(1075, 150, "制限時間", 0x000000,MainFont1);

	//5秒を切ると文字が揺れる
	if (Time <= 10) {
		DrawFormatStringToHandle(1120+GetRand(10-Time), 200+GetRand(10-Time), TimerColor,MainFont2, "%2.2d", Time);
	}
	else {
		DrawFormatStringToHandle(1120, 200, TimerColor, MainFont2, "%.2d", Time);
	}

	//プレイヤーの描画
	if (PlayerDispFlg == TRUE) {
		player->Draw();
	}

	//リンゴの描画
	for (int i = 0; i < 10; i++) {
		apple[i]->Draw();
	}

	//一時停止中の描画
	if (PauseFlg == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		if (PauseFlashFlg == TRUE) {
			DrawStringToHandle(370, 370, "---ポーズ中---", 0x000000, MainFont1, TRUE);
		}
		else{
			DrawStringToHandle(370, 370, "---ポーズ中---", 0xffffff, MainFont1, TRUE);
		}
		DrawStringToHandle(370, 520, "Startボタンで再開", 0xffffff, MainFont1,TRUE);
	}
}

void GameMain::AppleGet(int i)
{
	//取ったりんごの種類を取得して対応する値を加算する
	gGetAppleType = apple[i]->GetAppleType();
	gGetApple[gGetAppleType]++;
	//取ったりんごの得点を取得
	TotalScore += apple[i]->GetApplePoint();
	apple[i]->EffectSet();
	//りんごリセット
	apple[i]->AppleReset();
	//もし取得したりんごが毒なら、
	if (gGetAppleType == 3)
	{
		//プレイヤーの点滅処理を開始する
		GetPsAppleFlg = TRUE;
		PlaySoundMem(PoisonAppleSE, DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundMem(AppleSE, DX_PLAYTYPE_BACK);
	}
	//得点の下限を０にする
	if (TotalScore < 0)
	{
		TotalScore = 0;
	}
}

void GameMain::AppleSpawn()
{
	//スポーンできる場所があるかチェック
	SpawnFlg = FALSE;
	for (int i = 0; i < 7; i++)
	{
		if (CheckSpawn[i] == FALSE)
		{
			SpawnFlg = TRUE;
		}
	}
	//一つでもスポーンできる場所があるなら
	if (SpawnFlg == TRUE)
	{
		SpawnApple = -1;
		//スポーンできるりんごがあるかチェック
		for (int i = 0; i < MAX_APPLE; i++)
		{
			//スポーンできるりんごが見つかったら
			if (apple[i]->GetAppleFlg() == FALSE)
			{
				//格納してforを抜ける
				SpawnApple = i;
				break;
			}
		}
		//スポーン出来るりんごがあれば
		if (SpawnApple != -1) {
			//スポーンできる場所が見つかるまでRandを繰り返す
			do {
				SpawnPos = GetRand(6);
			} while (CheckSpawn[SpawnPos] == TRUE);
			//りんご生成
			apple[SpawnApple]->Spawn();
			//りんごの座標決定
			apple[SpawnApple]->SetLocation(SpawnPos * APPLE_DISTANCE+5);
			//りんご生成済チェックをいれる
			CheckSpawn[SpawnPos] = TRUE;
			//画面にあるりんごの個数を後で増加させるために数えておく
			SpawnCount++;
		}
	}
}

