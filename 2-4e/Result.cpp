#pragma once
#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include "End.h"
#include "Result.h"
#include "Ranking.h"
#include "InputRankingScene.h"

#define TIME_LIMIT 200;

// --------------------------------
// �R���X�g���N�^
//---------------------------------
Result::Result()
{
	//������
	WaitTime = TIME_LIMIT;
	//�t�H���g�̒ǉ�
	ResultFont1 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 70, 8, DX_FONTTYPE_ANTIALIASING);
	ResultFont2 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 50, 8, DX_FONTTYPE_ANTIALIASING);

	Ranking::ReadRanking();

	//�摜�ǂݍ���
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((ResultImg = LoadGraph("Resource/Images/Result1.png")) == -1)
	{
		throw "Resource/Images/Result.png";
	}

}

//--------------------------------
// �f�X�g���N�^
//--------------------------------
Result::~Result()
{
	// �t�H���g�폜
	DeleteFontToHandle(ResultFont1);
	DeleteFontToHandle(ResultFont2);

}
//--------------------------------
// �X�V
//--------------------------------
AbstractScene* Result::Update() {
	if (WaitTime-- < 0)
	{
		if (GameMain::getScore > Ranking::GetData(RANK - 1).score)
		{
			//���O���͏����ֈڍs
			return new InputRankingScene(GameMain::getScore);
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
	DrawGraph(120, 160, ResultImg, TRUE);

	// �X�R�A�̕`��
	DrawStringToHandle(220,90,"�肴���",0xffffff,ResultFont1);
	DrawFormatStringToHandle(270, 200, 0xff0000, ResultFont2, "�Ԃ�񂲁F%.2d", GameMain::R_Apple[0]);
	DrawFormatStringToHandle(270, 260, 0x0000ff, ResultFont2, "��񂲁F%.2d", GameMain::R_Apple[1]);
	DrawFormatStringToHandle(270, 320, 0xffff00, ResultFont2, "����񂲁F%.2d", GameMain::R_Apple[2]);
	DrawFormatStringToHandle(270, 380, 0xff00ff, ResultFont2, "�ł�񂲁F%.2d", GameMain::R_Apple[3]);
	DrawFormatStringToHandle(270, 440, 0xffffff, ResultFont2, "�X�R�A�F%.5d", GameMain::getScore);
	//SetFontSize(24);
}