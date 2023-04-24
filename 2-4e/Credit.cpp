#include "Credit.h"
#include"PadInput.h"
#include"Title.h"

//--------------------------------
// コンストラクタ
//--------------------------------
Credit::Credit() {
	//クレジット画面表示
	if ((CreditImage = LoadGraph("Resource/Images/Credit.png")) == -1)
	{
		throw "Resource/Images/Credit.png";
	}

	//BGMの読み込み
	if ((CreditBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, CreditBGM);

	//SEの読み込み
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(125, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(CreditBGM) == 0) {
		PlaySoundMem(CreditBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

//--------------------------------
// デストラクタ
//--------------------------------
Credit::~Credit()
{
	//サウンドの削除
	DeleteSoundMem(CreditBGM);
	DeleteSoundMem(DecisionSE);
}

//--------------------------------
// 更新
//--------------------------------
AbstractScene* Credit::Update()
{


	//Aボタンでタイトルに戻る
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		StopSoundMem(CreditBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new Title();
	}
	return this;
}

//--------------------------------
// 描画
//--------------------------------
void Credit::Draw()const {
	DrawGraph(0, 0, CreditImage, FALSE);
}