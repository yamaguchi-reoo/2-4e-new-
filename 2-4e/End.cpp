#pragma once
#include"DxLib.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 300
#define MOVE_SPEED 7
// --------------------------------
// コンストラクタ
//---------------------------------
End::End() {
	//初期化
	WaitTime = TIME_LIMIT;
	MoveString = 0;

	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//BGMの読み込み
	if ((EndBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, EndBGM);

	//SEの読み込み
	if ((EndSE = LoadSoundMem("Resource/sounds/SE/End.wav")) == -1)
	{
		throw "Resource/sounds/SE/End.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(70, EndSE);

	//BGMの再生
	if (CheckSoundMem(EndBGM) == 0)
	{
		PlaySoundMem(EndBGM, DX_PLAYTYPE_BACK);
	}
	//画面切替時SE
	if (CheckSoundMem(EndSE) == 0)
	{
		PlaySoundMem(EndSE, DX_PLAYTYPE_BACK);
	}

}

//--------------------------------
// デストラクタ
//--------------------------------
End::~End()
{
	//サウンドの削除
	DeleteSoundMem(EndBGM);
	DeleteSoundMem(EndSE);
}
//--------------------------------
// 更新
//--------------------------------
AbstractScene* End::Update() {
	if (WaitTime-- < 0) {
		return nullptr;
	}
	if (++MoveString >= 200) { 
		MoveString = 200; 
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void End::Draw()const {
	//ゲーム終了画面
	DrawGraph(0, 0, ForestImg, TRUE);

	SetFontSize(70);							 //大きさ70に変更
	SetFontThickness(3);                         //太さを3に変更
	ChangeFont("HGS創英角ﾎﾟｯﾌﾟ体");              //HGS創英角ﾎﾟｯﾌﾟ体に変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_16X16);	 //アンチエイリアシング エッジ付き16x16
	DrawString(500, 780 - MoveString * MOVE_SPEED, "SE & BGM", 0x0000ff);

	SetFontSize(50);							//大きさ50に変更
	DrawString(540, 880 - MoveString * MOVE_SPEED, "OtoLogic", 0x000000);
	DrawString(515, 940 - MoveString * MOVE_SPEED, "無料効果音", 0x000000);
	DrawString(470, 1000 - MoveString * MOVE_SPEED, "甘茶の音楽工房", 0x000000);

	SetFontSize(70);							//大きさ70に変更
	DrawString(505, 1200 - MoveString * MOVE_SPEED, "画像素材", 0xff0000);

	SetFontSize(50);							//大きさ50に変更
	DrawString(510, 1300 - MoveString * MOVE_SPEED, "イラスト屋", 0x000000);

	SetFontSize(90);							//大きさ90に変更
	DrawString(340, 2000 - MoveString * (MOVE_SPEED+1.5), "Thank You For ", 0x000000);
	DrawString(310, 2100 - MoveString * (MOVE_SPEED+1.5), "Playing Game !!", 0x000000);
}