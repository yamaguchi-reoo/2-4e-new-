#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

Help::Help() 
{
	//ヘルプ画面読み込み
	if ((HelpImg = LoadGraph("Resource/Images/Help.png")) == -1)
	{
		throw "Resource/Images/Help.png";
	}

	//BGMの読み込み
	if ((HelpBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, HelpBGM);

	//SEの読み込み
	if ((HelpSE = LoadSoundMem("Resource/sounds/SE/Help.wav")) == -1)
	{
		throw "Resource/sounds/SE/Help.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision02.wav")) == -1) //選択SE
	{
		throw "Resource/sounds/SE/Decision02.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(140, HelpSE);
	ChangeVolumeSoundMem(140, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_LOOP);
	}
	//画面切替時SE
	if (CheckSoundMem(HelpSE) == 0)
	{
		PlaySoundMem(HelpSE, DX_PLAYTYPE_BACK);
	}
}

Help::~Help()
{

	StopSoundMem(HelpBGM);
	//サウンドの削除
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(HelpSE);
}

AbstractScene* Help::Update()
{
	//Bボタンでタイトルへ戻る
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		PlaySoundMem(DecisionSE,DX_PLAYTYPE_BACK);
		return new Title();
	}
	//Aボタンでゲームを始める
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new GameMain();
	}
	return this;
}

void Help::Draw()const
{
	//画像の描画
	DrawGraph(0, 0, HelpImg, TRUE);

}