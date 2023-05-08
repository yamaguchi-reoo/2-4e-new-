#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"
#include "PadInput.h"

GameMain::GameMain()
{
	//������
	TotalScore = 0;
	PauseFlg = FALSE;
	PauseFlash = 0;
	Time = 3599;
	GetTxAppleTime = 0;
	PlayerDispFlg = TRUE;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		GetApple[i] = 0;
	}

	//�I�u�W�F�N�g��
	player = new Player();
	apple = new Apple();
	score = new Score();

	//�摜�̓ǂݍ���
	if ((mori_img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}

}

GameMain::~GameMain()
{
	//�I�u�W�F�N�g�̍폜
	delete player;
	delete apple;
	delete score;

}

AbstractScene* GameMain::Update()
{
	//�|�[�Y�t���O�؂�ւ�����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
	}
	//�|�[�Y���łȂ��Ȃ�
	if (PauseFlg == FALSE) {
		//�����̍X�V
		player->UpDate();
		apple->UpDate();

		for (int i = 0; i < MAX_APPLE; i++)
		{
			apple->SetLocation(i);
			if (apple->HitBox(player) == true && GetTxAppleTime == 0)
			{
				//�����擾������񂲂��łȂ�A
				if (apple->AppleTypeGet(i) == 3)
				{
					//�v���C���[�̓_�ŏ������J�n����
					GetTxAppleTime = 1;
				}
				TotalScore += apple->AppleGet(i);
				//���_�̉������O�ɂ���
				if (TotalScore < 0)
				{
					TotalScore = 0;
				}
			}
		}
		//�_�Œ��̏���
		if (GetTxAppleTime > 0)
		{
			if (++GetTxAppleTime % 20 == 0)
			{
				PlayerDispFlg = !PlayerDispFlg;
			}
			if (GetTxAppleTime >= 120)
			{
				GetTxAppleTime = 0;
			}
		}
		//�������Ԍ���
		Time--;
	}

	if (PauseFlg == TRUE)
	{
		PauseFlash++;
		if (PauseFlash > 20)
		{
			PauseFlash = 0;
		}
	}
	if (Time <= 0)
	{
		//�����Ń��U���g��ʂֈڍs�i�X�R�A��TotarScore�ɁA�ǂ̂�񂲂������擾�������̓����GetApple[]�ɓ����Ă���j
		Time = 600;	//���U���g�ڍs�������o����������Ă���
	}
	return this;
	
}

void GameMain::Draw()const
{
	// �w�i�̕`��
	DrawGraph(0, 0, mori_img, TRUE);

	//�v���C���[�̕`��
	if (PlayerDispFlg == TRUE) {
		player->Draw();
	}

	//�X�R�A�̕`��
	score->Draw();
	//���̃X�R�A�`��	
	SetFontSize(30);
	DrawString(1105, 450, "���_", 0x000000);
	DrawFormatString(1095, 500, 0x000000, "%.5d",TotalScore);
	SetFontSize(24);

	//��������
	SetFontSize(30);
	DrawString(1075, 150, "��������", 0x000000);
	SetFontSize(40);
	//5�b��؂�ƕ������h���
	if (Time <= 300) {
		DrawFormatString(1120+GetRand(10-Time/30), 200+GetRand(10-Time/30), 0x000000, "%2.2d", Time / 60 + 1);
	}
	else {
		DrawFormatString(1120, 200, 0x000000, "%.2d", Time / 60 + 1);
	}
	SetFontSize(24);

	//�����S�̕`��
	apple->Draw();

	//�ꎞ��~���̕`��
	if (PauseFlg == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1000, 780, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(30);
		if (PauseFlash <= 10) {
			DrawString(370, 370, "---�|�[�Y��---", 0x000000, TRUE);
		}
		else if (PauseFlash > 10) {
			DrawString(370, 370, "---�|�[�Y��---", 0xffffff, TRUE);
		}
		SetFontSize(20);
		DrawString(390, 420, "Start�{�^���ōĊJ", 0xffffff, TRUE);
		SetFontSize(24);
	}
}

