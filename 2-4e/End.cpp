#pragma once
#include"DxLib.h"
#include"Title.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 900;
// --------------------------------
// コンストラクタ
//---------------------------------
End::End() {
	//初期化
	WaitTime = TIME_LIMIT;
	MoveString = 0;
	BackTitle = FALSE; //TRUEにしたらBボタンでタイトルへ戻れるようになる

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
	if (++MoveString >= 700) { 
		MoveString = 700; 
	}
	if (BackTitle==TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		return new Title();
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void End::Draw()const {
	//ゲーム終了画面
	DrawGraph(0, 0, ForestImg, TRUE);

	/*SetFontSize(50);
	DrawString(170, 100, "SE & BGM", 0x0000ff);
	DrawString(860, 100, "画像素材", 0xff0000);
	SetFontSize(30);
	DrawString(200, 160, "OtoLogic", 0x000000);
	DrawString(190, 195, "無料効果音", 0x000000);
	DrawString(160, 230, "甘茶の音楽工房", 0x000000); 
	DrawString(880, 160, "イラスト屋", 0x000000); 
	SetFontSize(90);
	DrawString(340, 430, "Thank You For ", 0x000000);
	DrawString(310, 530, "Playing Game !!", 0x000000);*/

	if (BackTitle == TRUE) {
		SetFontSize(20);
		DrawBox(1130,700,1280,750,0xffffff,TRUE);
		DrawString(1135, 700, "Bボタンで戻る", 0xff0000);
		DrawBox(0, 700, 195, 750, 0xffffff, TRUE);
		DrawString(0, 700, "ゲーム終了まで  秒", 0xff0000);
		DrawFormatString(147, 701, 0x000000, "%.2d", WaitTime/60+1);
	}
	/*for (int i = 0; i < 1280; i++)
	{
		if (i % 128==0)DrawLine(i, 0, i, 780, 0x000000, TRUE);
	}*/

	SetFontSize(70);
	DrawString(500, 780 - MoveString * 2, "SE & BGM", 0x0000ff);
	SetFontSize(50);
	DrawString(540, 880 - MoveString * 2, "OtoLogic", 0x000000);
	DrawString(515, 940 - MoveString * 2, "無料効果音", 0x000000);
	DrawString(470, 1000 - MoveString * 2, "甘茶の音楽工房", 0x000000);

	SetFontSize(70);
	DrawString(505, 1200 - MoveString * 2, "画像素材", 0xff0000);
	SetFontSize(50);
	DrawString(510, 1300 - MoveString * 2, "イラスト屋", 0x000000);

	SetFontSize(90);
	DrawString(340, 2000 - MoveString * 2.5, "Thank You For ", 0x000000);
	DrawString(310, 2100 - MoveString * 2.5, "Playing Game !!", 0x000000);
}