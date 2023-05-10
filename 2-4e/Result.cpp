#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"
#include"Result.h"

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


//--------------------------------
// 描画
//--------------------------------
void Result::Draw()const
{
	//ゲーム終了画面
	DrawGraph(0, 0, ForestImg, TRUE);

	SetFontSize(30);
	DrawString(1105, 450, "得点", 0x000000);
	DrawFormatString(1095, 500, 0x000000, "%.5d", GameMain::getScore);
	SetFontSize(24);
}