#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"
#include"Result.h"


#define TIME_LIMIT 100;

// --------------------------------
// コンストラクタ
//---------------------------------
Result::Result()
{
	//初期化
	WaitTime = TIME_LIMIT;
	ResultFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 70, 8, DX_FONTTYPE_ANTIALIASING);
	ResultFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 50, 8, DX_FONTTYPE_ANTIALIASING);

	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((ResultImg = LoadGraph("Resource/Images/Result1.png")) == -1)
	{
		throw "Resource/Images/Result.png";
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
		return new DrawRanking;
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
	DrawFormatStringToHandle(270, 200, 0xff0000, ResultFont2, "赤りんご：%.2d", GameMain::R_Apple[0]);
	DrawFormatStringToHandle(270, 260, 0x0000ff, ResultFont2, "青りんご：%.2d", GameMain::R_Apple[1]);
	DrawFormatStringToHandle(270, 320, 0xffff00, ResultFont2, "金りんご：%.2d", GameMain::R_Apple[2]);
	DrawFormatStringToHandle(270, 380, 0xff00ff, ResultFont2, "毒りんご：%.2d", GameMain::R_Apple[3]);
	DrawFormatStringToHandle(270, 440, 0xffffff, ResultFont2, "スコア：%.5d", GameMain::getScore);
	//SetFontSize(24);
}