#pragma once
#include"DxLib.h"
#include"Title.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 900;
// --------------------------------
// �R���X�g���N�^
//---------------------------------
End::End() {
	//������
	WaitTime = TIME_LIMIT;
	MoveString = 0;
	BackTitle = FALSE; //TRUE�ɂ�����B�{�^���Ń^�C�g���֖߂��悤�ɂȂ�

	SEflg = 0;

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
	if (++MoveString >= 700) { 
		MoveString = 700; 
	}
	if (BackTitle==TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		return new Title();
	}
	//��ʐؑ֎�SE
	if (CheckSoundMem(EndSE) == 0)
	{
		if (SEflg++ == 1)
		{
			PlaySoundMem(EndSE, DX_PLAYTYPE_BACK);
		}
	}
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void End::Draw()const {
	//�Q�[���I�����
	DrawGraph(0, 0, ForestImg, TRUE);

	/*SetFontSize(50);
	DrawString(170, 100, "SE & BGM", 0x0000ff);
	DrawString(860, 100, "�摜�f��", 0xff0000);
	SetFontSize(30);
	DrawString(200, 160, "OtoLogic", 0x000000);
	DrawString(190, 195, "�������ʉ�", 0x000000);
	DrawString(160, 230, "�Ò��̉��y�H�[", 0x000000); 
	DrawString(880, 160, "�C���X�g��", 0x000000); 
	SetFontSize(90);
	DrawString(340, 430, "Thank You For ", 0x000000);
	DrawString(310, 530, "Playing Game !!", 0x000000);*/

	if (BackTitle == TRUE) {
		SetFontSize(20);
		DrawBox(1130,700,1280,750,0xffffff,TRUE);
		DrawString(1135, 700, "B�{�^���Ŗ߂�", 0xff0000);
		DrawBox(0, 700, 195, 750, 0xffffff, TRUE);
		DrawString(0, 700, "�Q�[���I���܂�  �b", 0xff0000);
		DrawFormatString(147, 701, 0x000000, "%.2d", WaitTime/60+1);
	}
	/*for (int i = 0; i < 1280; i++)
	{
		if (i % 128==0)DrawLine(i, 0, i, 780, 0x000000, TRUE);
	}*/

	SetFontSize(70);							 //�傫��70�ɕύX
	SetFontThickness(3);                         //������3�ɕύX
	ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_16X16);	 //�A���`�G�C���A�V���O �G�b�W�t��16x16
	DrawString(500, 780 - MoveString * 2, "SE & BGM", 0x0000ff);

	SetFontSize(50);							//�傫��50�ɕύX
	DrawString(540, 880 - MoveString * 2, "OtoLogic", 0x000000);
	DrawString(515, 940 - MoveString * 2, "�������ʉ�", 0x000000);
	DrawString(470, 1000 - MoveString * 2, "�Ò��̉��y�H�[", 0x000000);

	SetFontSize(70);							//�傫��70�ɕύX
	DrawString(505, 1200 - MoveString * 2, "�摜�f��", 0xff0000);

	SetFontSize(50);							//�傫��50�ɕύX
	DrawString(510, 1300 - MoveString * 2, "�C���X�g��", 0x000000);

	SetFontSize(90);							//�傫��90�ɕύX
	DrawString(340, 2000 - MoveString * 2.5, "Thank You For ", 0x000000);
	DrawString(310, 2100 - MoveString * 2.5, "Playing Game !!", 0x000000);
}