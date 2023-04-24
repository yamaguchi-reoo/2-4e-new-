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

	//フォントの追加
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//画像の読み込み
	if ((EndImage = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
End::~End()
{
	//フォントの削除
	DeleteFontToHandle(HeadLineFont);
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
	DrawGraph(0, 0, EndImage, TRUE);

	DrawStringToHandle(370, 270, "Thank You For ", 0xf3704b, HeadLineFont);
	DrawStringToHandle(340, 370, "Playing Game !!", 0xf3704b, HeadLineFont);
}