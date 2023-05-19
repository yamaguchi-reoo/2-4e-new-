#pragma once
#include"DxLib.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 300;
// --------------------------------
// �R���X�g���N�^
//---------------------------------
End::End() {
	//������
	WaitTime = TIME_LIMIT;
	MoveString = 0;

	//�t�H���g�̒ǉ�
	EndFont1 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 70, 8, DX_FONTTYPE_ANTIALIASING);
	EndFont2 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 50, 8, DX_FONTTYPE_ANTIALIASING);
	EndFont3 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 90, 8, DX_FONTTYPE_ANTIALIASING);

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
	DeleteFontToHandle(EndFont1);
	DeleteFontToHandle(EndFont2);
	DeleteFontToHandle(EndFont3);
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
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void End::Draw()const {
	//�Q�[���I�����
	DrawGraph(0, 0, ForestImg, TRUE);
    //SetFontSize(70);							 //�傫��70�ɕύX
	//SetFontThickness(3);                         //������3�ɕύX
	//ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
	//ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_16X16);	 //�A���`�G�C���A�V���O �G�b�W�t��16x16
	DrawStringToHandle(500, 780 - MoveString * 2, "SE & BGM", 0x0000ff,EndFont1);

	//SetFontSize(50);							//�傫��50�ɕύX
	DrawStringToHandle(540, 880 - MoveString * 2, "OtoLogic", 0x000000, EndFont2);
	DrawStringToHandle(515, 940 - MoveString * 2, "�������ʉ�", 0x000000, EndFont2);
	DrawStringToHandle(470, 1000 - MoveString * 2, "�Ò��̉��y�H�[", 0x000000,EndFont2);

	//SetFontSize(70);							//�傫��70�ɕύX
	DrawStringToHandle(505, 1200 - MoveString * 2, "�摜�f��", 0xff0000, EndFont1);

	//SetFontSize(50);							//�傫��50�ɕύX
	DrawStringToHandle(510, 1300 - MoveString * 2, "�C���X�g��", 0x000000, EndFont2);

	//SetFontSize(90);							//�傫��90�ɕύX
	DrawStringToHandle(340, 2000 - MoveString * 2.5, "Thank You For ", 0x000000, EndFont3);
	DrawStringToHandle(310, 2100 - MoveString * 2.5, "Playing Game !!", 0x000000, EndFont3);
}