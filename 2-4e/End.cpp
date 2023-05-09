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
	//DrawGraph(0, 0, EndImage, TRUE);

	DrawString(370, 270, "Thank You For ", 0xf3704b);
	DrawString(340, 370, "Playing Game !!", 0xf3704b);
}