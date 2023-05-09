#pragma once
#include"DxLib.h"
#include"End.h"

#define TIME_LIMIT 180;
// --------------------------------
// �R���X�g���N�^
//---------------------------------
End::End() {
	//������
	WaitTime = TIME_LIMIT;

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
	return this;
}

//--------------------------------
// �`��
//--------------------------------
void End::Draw()const {
	//�Q�[���I�����
	DrawGraph(0, 0, ForestImg, TRUE);

	SetFontSize(50);
	DrawString(190, 100, "SE:BGM", 0x0000ff);
	DrawString(860, 100, "�摜�f��", 0xff0000);
	SetFontSize(30);
	DrawString(200, 160, "OtoLogic", 0x000000);
	DrawString(190, 195, "�������ʉ�", 0x000000);
	DrawString(160, 230, "�Ò��̉��y�H�[", 0x000000); 
	DrawString(880, 160, "�C���X�g��", 0x000000); 
	SetFontSize(90);
	DrawString(340, 430, "Thank You For ", 0x000000);
	DrawString(310, 530, "Playing Game !!", 0x000000);
}