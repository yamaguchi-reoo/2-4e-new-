#pragma once
#include"DxLib.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 300
#define MOVE_SPEED 7
// --------------------------------
// �R���X�g���N�^
//---------------------------------
End::End() {
	//������
	WaitTime = TIME_LIMIT;
	MoveString = 0;

	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//BGM�̓ǂݍ���
	if ((EndBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, EndBGM);

	//SE�̓ǂݍ���
	if ((EndSE = LoadSoundMem("Resource/sounds/SE/End.wav")) == -1)
	{
		throw "Resource/sounds/SE/End.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(70, EndSE);

	//BGM�̍Đ�
	if (CheckSoundMem(EndBGM) == 0)
	{
		PlaySoundMem(EndBGM, DX_PLAYTYPE_BACK);
	}
	//��ʐؑ֎�SE
	if (CheckSoundMem(EndSE) == 0)
	{
		PlaySoundMem(EndSE, DX_PLAYTYPE_BACK);
	}

}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
End::~End()
{
	//�T�E���h�̍폜
	DeleteSoundMem(EndBGM);
	DeleteSoundMem(EndSE);
}
//--------------------------------
// �X�V
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
// �`��
//--------------------------------
void End::Draw()const {
	//�Q�[���I�����
	DrawGraph(0, 0, ForestImg, TRUE);

	SetFontSize(70);							 //�傫��70�ɕύX
	SetFontThickness(3);                         //������3�ɕύX
	ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_16X16);	 //�A���`�G�C���A�V���O �G�b�W�t��16x16
	DrawString(500, 780 - MoveString * MOVE_SPEED, "SE & BGM", 0x0000ff);

	SetFontSize(50);							//�傫��50�ɕύX
	DrawString(540, 880 - MoveString * MOVE_SPEED, "OtoLogic", 0x000000);
	DrawString(515, 940 - MoveString * MOVE_SPEED, "�������ʉ�", 0x000000);
	DrawString(470, 1000 - MoveString * MOVE_SPEED, "�Ò��̉��y�H�[", 0x000000);

	SetFontSize(70);							//�傫��70�ɕύX
	DrawString(505, 1200 - MoveString * MOVE_SPEED, "�摜�f��", 0xff0000);

	SetFontSize(50);							//�傫��50�ɕύX
	DrawString(510, 1300 - MoveString * MOVE_SPEED, "�C���X�g��", 0x000000);

	SetFontSize(90);							//�傫��90�ɕύX
	DrawString(340, 2000 - MoveString * (MOVE_SPEED+1.5), "Thank You For ", 0x000000);
	DrawString(310, 2100 - MoveString * (MOVE_SPEED+1.5), "Playing Game !!", 0x000000);
}