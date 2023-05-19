#include"DxLib.h"
#include "Help.h"
#include"Title.h"
#include "PadInput.h"
#include"GameMain.h"

//--------------------------------
// �R���X�g���N�^
//--------------------------------
Help::Help() 
{
	//�w���v��ʓǂݍ���
	if ((HelpImg = LoadGraph("Resource/Images/Help.png")) == -1)
	{
		throw "Resource/Images/Help.png";
	}

	//BGM�̓ǂݍ���
	if ((HelpBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, HelpBGM);

	//SE�̓ǂݍ���
	if ((HelpSE = LoadSoundMem("Resource/sounds/SE/Help.wav")) == -1)
	{
		throw "Resource/sounds/SE/Help.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(125, HelpSE);

	//BGM�̍Đ�
	if (CheckSoundMem(HelpBGM) == 0) {
		PlaySoundMem(HelpBGM, DX_PLAYTYPE_BACK, TRUE);
	}
	//��ʐؑ֎�SE
	if (CheckSoundMem(HelpSE) == 0)
	{
		PlaySoundMem(HelpSE, DX_PLAYTYPE_BACK);
	}
}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
Help::~Help()
{

	//�T�E���h�̍폜
	DeleteSoundMem(HelpBGM);
	DeleteSoundMem(HelpSE);
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
		return new Title();
	}
	//A�{�^���ŃQ�[�����n�߂�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		StopSoundMem(HelpBGM);
		return new GameMain();
	}
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void Help::Draw()const
{
	//�摜�̕`��
	DrawGraph(0, 0, HelpImg, TRUE);

}