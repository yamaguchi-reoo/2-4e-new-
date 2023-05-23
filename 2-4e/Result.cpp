#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include "End.h"
#include "Result.h"
#include "Ranking.h"
#include "InputRankingScene.h"

#define TIME_LIMIT 200;

// --------------------------------
// コンストラクタ
//---------------------------------
Result::Result(int *GetApple,int Score)
{
	//初期化
	WaitTime = TIME_LIMIT;
	for (int i = 0; i < 4; i++)
	{
		R_GetApple[i] = GetApple[i];
	}
	R_Score = Score;
	//フォントの追加
	ResultFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 70, 8, DX_FONTTYPE_ANTIALIASING);
	ResultFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 50, 8, DX_FONTTYPE_ANTIALIASING);

	Ranking::ReadRanking();

	//画像読み込み
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((ResultImg = LoadGraph("Resource/Images/Result1.png")) == -1)
	{
		throw "Resource/Images/Result.png";
	}
	//BGMの読み込み
	if ((ResultBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, ResultBGM);
	//BGMの再生
	if (CheckSoundMem(ResultBGM) == 0)
	{
		PlaySoundMem(ResultBGM, DX_PLAYTYPE_BACK);
	}

}

//--------------------------------
// デストラクタ
//--------------------------------
Result::~Result()
{
	// フォント削除
	DeleteFontToHandle(ResultFont1);
	DeleteFontToHandle(ResultFont2);

	//サウンド削除
	DeleteSoundMem(ResultBGM);

	StopSoundMem(ResultBGM);

}
//--------------------------------
// 更新
//--------------------------------
AbstractScene* Result::Update() {
	if (WaitTime-- < 0)
	{
		if (R_Score > Ranking::GetData(RANK - 1).score)
		{
			//名前入力処理へ移行
			return new InputRankingScene(R_Score);
		}
		else
		{
			//ランキング描画処理へ移行
			return new DrawRanking;
		}
	}
	return this;
}


//--------------------------------
// 描画
//--------------------------------
void Result::Draw()const
{
	//ゲーム終了画面
	DrawGraph(0, 0, ForestImg, TRUE);
	DrawGraph(120, 160, ResultImg, TRUE);

	// スコアの描画
	DrawStringToHandle(220,90,"りざると",0xffffff,ResultFont1);
	DrawFormatStringToHandle(270, 200, 0xff0000, ResultFont2, "赤りんご：%.2d", R_GetApple[0]);
	DrawFormatStringToHandle(270, 260, 0x0000ff, ResultFont2, "青りんご：%.2d", R_GetApple[1]);
	DrawFormatStringToHandle(270, 320, 0xffff00, ResultFont2, "金りんご：%.2d", R_GetApple[2]);
	DrawFormatStringToHandle(270, 380, 0xff00ff, ResultFont2, "毒りんご：%.2d", R_GetApple[3]);
	DrawFormatStringToHandle(270, 440, 0xffffff, ResultFont2, "スコア：%.5d", R_Score);
	//SetFontSize(24);
}