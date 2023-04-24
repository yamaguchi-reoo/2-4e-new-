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

	//�t�H���g�̒ǉ�
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�摜�̓ǂݍ���
	if ((EndImage = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}
}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
End::~End()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(HeadLineFont);
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
	DrawGraph(0, 0, EndImage, TRUE);

	DrawStringToHandle(370, 270, "Thank You For ", 0xf3704b, HeadLineFont);
	DrawStringToHandle(340, 370, "Playing Game !!", 0xf3704b, HeadLineFont);
}