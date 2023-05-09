#pragma once
#include"DxLib.h"
#include"End.h"

#define TIME_LIMIT 180;
// --------------------------------
// コンストラクタ
//---------------------------------
End::End() {
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
End::~End()
{

}
//--------------------------------
// 更新
//--------------------------------
AbstractScene* End::Update() {
	if (WaitTime-- < 0) {
		return nullptr;
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void End::Draw()const {
	//ゲーム終了画面
	DrawGraph(0, 0, ForestImg, TRUE);

	SetFontSize(50);
	DrawString(190, 100, "SE:BGM", 0x0000ff);
	DrawString(860, 100, "画像素材", 0xff0000);
	SetFontSize(30);
	DrawString(200, 160, "OtoLogic", 0x000000);
	DrawString(190, 195, "無料効果音", 0x000000);
	DrawString(160, 230, "甘茶の音楽工房", 0x000000); 
	DrawString(880, 160, "イラスト屋", 0x000000); 
	SetFontSize(90);
	DrawString(340, 430, "Thank You For ", 0x000000);
	DrawString(310, 530, "Playing Game !!", 0x000000);
}