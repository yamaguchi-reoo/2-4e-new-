#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

//--------------------------------
// コンストラクタ
//--------------------------------
Help::Help() {

	HelpFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 90, 9, DX_FONTTYPE_NORMAL);
	HelpFont1 = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 40, 20, DX_FONTTYPE_NORMAL);
	//ヘルプ画面読み込み
	if ((HelpImg = LoadGraph("Resource/Images/Gamepad.png")) == -1)
	{
		throw "Resource/Images/Gamepad.png";
	}
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}

	//BGMの読み込み
	if ((HelpBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, HelpBGM);

	//SEの読み込み
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(125, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
Help::~Help()
{
	//サウンドの削除
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(DecisionSE);
}

//--------------------------------
// 更新
//--------------------------------
AbstractScene* Help::Update()
{


	//Bボタンでタイトルへ戻る
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new Title();
	}
	//Aボタンでゲームを始める
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new GameMain();
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void Help::Draw()const
{
	DrawGraph(0, 0, ForestImg, TRUE);
	DrawGraph(420, 200, HelpImg, TRUE);

	//DrawBox(700, 100, 1000, 620, 0xffffff, TRUE);

	//SetFontSize(90);
	DrawStringToHandle(450, 50,"操作説明" ,0xffffff,HelpFont);

}