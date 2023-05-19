#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

//--------------------------------
// コンストラクタ
//--------------------------------
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
	//SEの音量変更
	ChangeVolumeSoundMem(125, HelpSE);

	//BGMの再生
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_BACK, TRUE);
	}
	//画面切替時SE
	if (CheckSoundMem(HelpSE) == 0)
	{
		PlaySoundMem(HelpSE, DX_PLAYTYPE_BACK);
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
Help::~Help()
{

	//サウンドの削除
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(HelpSE);
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
		return new Title();
	}
	//Aボタンでゲームを始める
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		StopSoundMem(HelpBGM);
		return new GameMain();
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void Help::Draw()const
{
	//画像の描画
	DrawGraph(0, 0, HelpImg, TRUE);

}