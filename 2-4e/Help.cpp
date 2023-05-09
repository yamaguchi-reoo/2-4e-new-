#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

//--------------------------------
// �R���X�g���N�^
//--------------------------------
Help::Help() {
	//�w���v��ʓǂݍ���
	if ((HelpImg = LoadGraph("Resource/Images/Gamepad.png")) == -1)
	{
		throw "Resource/Images/Gamepad.png";
	}
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}

	//BGM�̓ǂݍ���
	if ((HelpBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, HelpBGM);

	//SE�̓ǂݍ���
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(125, DecisionSE);

	//BGM�̍Đ�
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
Help::~Help()
{
	//�T�E���h�̍폜
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(DecisionSE);
}

//--------------------------------
// �X�V
//--------------------------------
AbstractScene* Help::Update()
{


	//B�{�^���Ń^�C�g���֖߂�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new Title();
	}
	//A�{�^���ŃQ�[�����n�߂�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		StopSoundMem(HelpBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new GameMain();
	}
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void Help::Draw()const
{
	DrawGraph(0, 0, ForestImg, FALSE);
	DrawGraph(120, 320, HelpImg, TRUE);

	SetFontSize(100);
	DrawString(450, 50,"������@" ,0x000000);

}