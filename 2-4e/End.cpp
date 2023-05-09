#pragma once
#include"DxLib.h"
#include"End.h"

#define TIME_LIMIT 900;
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

}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
End::~End()
{

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

	for (int i = 0; i < 1280; i++)
	{
		if (i % 128==0)DrawLine(i, 0, i, 780, 0x000000, TRUE);
	}
	SetFontSize(70);
	DrawString(500, 780 - MoveString * 2, "SE & BGM", 0x0000ff);
	SetFontSize(50);
	DrawString(540, 880 - MoveString * 2, "OtoLogic", 0x000000);
	DrawString(515, 940 - MoveString * 2, "�������ʉ�", 0x000000);
	DrawString(470, 1000 - MoveString * 2, "�Ò��̉��y�H�[", 0x000000);

	SetFontSize(70);
	DrawString(505, 1200 - MoveString * 2, "�摜�f��", 0xff0000);
	SetFontSize(50);
	DrawString(510, 1300 - MoveString * 2, "�C���X�g��", 0x000000);

	SetFontSize(90);
	DrawString(340, 2000 - MoveString * 2.5, "Thank You For ", 0x000000);
	DrawString(310, 2100 - MoveString * 2.5, "Playing Game !!", 0x000000);
}