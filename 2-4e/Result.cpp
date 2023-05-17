#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include "End.h"
#include "Result.h"
#include "Ranking.h"


#define TIME_LIMIT 200;

// --------------------------------
// コンストラクタ
//---------------------------------
Result::Result()
{
	//初期化
	WaitTime = TIME_LIMIT;
	Ranking::ReadRanking();
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
Result::~Result()
{

}
//--------------------------------
// 更新
//--------------------------------
AbstractScene* Result::Update() {
	if (WaitTime-- < 0)
	{
		if (GameMain::getScore > Ranking::GetData(4).score)
		{
			//名前入力処理へ移行
			return new Title;
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

	// スコアの描画
	DrawBox(256, 144, 1024, 576, 0xffffff, TRUE);
	SetFontSize(50);
	DrawFormatString(270, 200, 0x000000, "赤りんご：%.2d", GameMain::R_Apple[0]);
	DrawFormatString(270, 260, 0x000000, "青りんご：%.2d", GameMain::R_Apple[1]);
	DrawFormatString(270, 320, 0x000000, "金りんご：%.2d", GameMain::R_Apple[2]);
	DrawFormatString(270, 380, 0x000000, "毒りんご：%.2d", GameMain::R_Apple[3]);
	DrawFormatString(270, 440, 0x000000, "スコア：%.5d", GameMain::getScore);
	SetFontSize(24);
}