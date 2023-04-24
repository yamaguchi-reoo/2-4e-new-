#include "Credit.h"
#include"PadInput.h"
#include"Title.h"

//--------------------------------
// �R���X�g���N�^
//--------------------------------
Credit::Credit() {
	//�N���W�b�g��ʕ\��
	if ((CreditImage = LoadGraph("Resource/Images/Credit.png")) == -1)
	{
		throw "Resource/Images/Credit.png";
	}

	//BGM�̓ǂݍ���
	if ((CreditBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, CreditBGM);

	//SE�̓ǂݍ���
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(125, DecisionSE);

	//BGM�̍Đ�
	if (CheckSoundMem(CreditBGM) == 0) {
		PlaySoundMem(CreditBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
Credit::~Credit()
{
	//�T�E���h�̍폜
	DeleteSoundMem(CreditBGM);
	DeleteSoundMem(DecisionSE);
}

//--------------------------------
// �X�V
//--------------------------------
AbstractScene* Credit::Update()
{


	//A�{�^���Ń^�C�g���ɖ߂�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		StopSoundMem(CreditBGM);
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new Title();
	}
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void Credit::Draw()const {
	DrawGraph(0, 0, CreditImage, FALSE);
}