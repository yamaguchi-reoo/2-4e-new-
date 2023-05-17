#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"
#include"Result.h"


#define TIME_LIMIT 100;

// --------------------------------
// �R���X�g���N�^
//---------------------------------
Result::Result()
{
	//������
	WaitTime = TIME_LIMIT;
	ResultFont = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 50, 8, DX_FONTTYPE_ANTIALIASING);

	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}



}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
Result::~Result()
{

}
//--------------------------------
// �X�V
//--------------------------------
AbstractScene* Result::Update() {
	if (WaitTime-- < 0) {
		return new DrawRanking;
	}
	return this;
}


//--------------------------------
// �`��
//--------------------------------
void Result::Draw()const
{
	//�Q�[���I�����
	DrawGraph(0, 0, ForestImg, TRUE);

	// �X�R�A�̕`��
	DrawBox(256, 144, 1024, 576, 0xffffff, TRUE);
	SetFontSize(50);
	DrawFormatStringToHandle(270, 200, 0xff0000, ResultFont, "�Ԃ�񂲁F%.2d", GameMain::R_Apple[0]);
	DrawFormatStringToHandle(270, 260, 0x0000ff, ResultFont, "��񂲁F%.2d", GameMain::R_Apple[1]);
	DrawFormatStringToHandle(270, 320, 0xffff00, ResultFont, "����񂲁F%.2d", GameMain::R_Apple[2]);
	DrawFormatStringToHandle(270, 380, 0xff00ff, ResultFont, "�ł�񂲁F%.2d", GameMain::R_Apple[3]);
	DrawFormatStringToHandle(270, 440, 0x000000, ResultFont, "�X�R�A�F%.5d", GameMain::getScore);
	SetFontSize(24);
}