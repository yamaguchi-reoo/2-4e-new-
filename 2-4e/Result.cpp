#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include "End.h"
#include "Result.h"
#include "Ranking.h"


#define TIME_LIMIT 200;

// --------------------------------
// �R���X�g���N�^
//---------------------------------
Result::Result()
{
	//������
	WaitTime = TIME_LIMIT;
	Ranking::ReadRanking();
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
	if (WaitTime-- < 0)
	{
		if (GameMain::getScore > Ranking::GetData(4).score)
		{
			//���O���͏����ֈڍs
			return new Title;
		}
		else
		{
			//�����L���O�`�揈���ֈڍs
			return new DrawRanking;
		}
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
	DrawFormatString(270, 200, 0x000000, "�Ԃ�񂲁F%.2d", GameMain::R_Apple[0]);
	DrawFormatString(270, 260, 0x000000, "��񂲁F%.2d", GameMain::R_Apple[1]);
	DrawFormatString(270, 320, 0x000000, "����񂲁F%.2d", GameMain::R_Apple[2]);
	DrawFormatString(270, 380, 0x000000, "�ł�񂲁F%.2d", GameMain::R_Apple[3]);
	DrawFormatString(270, 440, 0x000000, "�X�R�A�F%.5d", GameMain::getScore);
	SetFontSize(24);
}