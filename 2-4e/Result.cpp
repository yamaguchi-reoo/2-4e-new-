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
Result::Result(int *GetApple,int Score)
{
	//������
	WaitTime = TIME_LIMIT;
	for (int i = 0; i < 4; i++)
	{
		R_GetApple[i] = GetApple[i];
	}
	R_Score = Score;
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
	//BGM�̓ǂݍ���
	if ((ResultBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, ResultBGM);
	//BGM�̍Đ�
	if (CheckSoundMem(ResultBGM) == 0)
	{
		PlaySoundMem(ResultBGM, DX_PLAYTYPE_BACK);
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

	//�T�E���h�폜
	DeleteSoundMem(ResultBGM);

	StopSoundMem(ResultBGM);

}
//--------------------------------
// �X�V
//--------------------------------
AbstractScene* Result::Update() {
	if (WaitTime-- < 0)
	{
		if (R_Score > Ranking::GetData(RANK - 1).score)
		{
			//���O���͏����ֈڍs
			return new InputRankingScene(R_Score);
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
	DrawFormatStringToHandle(270, 200, 0xff0000, ResultFont2, "�Ԃ�񂲁F%.2d", R_GetApple[0]);
	DrawFormatStringToHandle(270, 260, 0x0000ff, ResultFont2, "��񂲁F%.2d", R_GetApple[1]);
	DrawFormatStringToHandle(270, 320, 0xffff00, ResultFont2, "����񂲁F%.2d", R_GetApple[2]);
	DrawFormatStringToHandle(270, 380, 0xff00ff, ResultFont2, "�ł�񂲁F%.2d", R_GetApple[3]);
	DrawFormatStringToHandle(270, 440, 0xffffff, ResultFont2, "�X�R�A�F%.5d", R_Score);
	//SetFontSize(24);
}