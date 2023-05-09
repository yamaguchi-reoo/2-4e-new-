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
	//DrawGraph(0, 0, EndImage, TRUE);

	DrawString(370, 270, "Thank You For ", 0xf3704b);
	DrawString(340, 370, "Playing Game !!", 0xf3704b);
}