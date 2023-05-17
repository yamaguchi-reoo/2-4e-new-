#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"
#include"Result.h"
#include"InputRankingScene.h"


#define TIME_LIMIT 2000;

// --------------------------------
// コンストラクタ
//---------------------------------
Result::Result()
{
	//初期化
	WaitTime = TIME_LIMIT;



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
	if (WaitTime-- < 0) {
		return new Title;
	}
	return this;
}
AbstractScene* Result::ChangeScene()
{
	if (PAD_INPUT::OnButton(PAD_INPUT_A)) {
		return new InputRankingScene();
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