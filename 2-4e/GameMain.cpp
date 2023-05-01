#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"
#include "PadInput.h"

#define TIMER 180

GameMain::GameMain()
{
	//������
	TotalScore = 0;
	PauseFlg = FALSE;
	PauseFlash = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		GetApple[i] = 0;
	}

	//�I�u�W�F�N�g��
	player = new Player();
	apple = new Apple();
	fps = new FpsController();
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
	delete fps;
	delete score;

}

AbstractScene* GameMain::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
	}

	if (PauseFlg == FALSE) {
		//�����̍X�V
		player->UpDate();
		apple->UpDate();
		fps->All();
		for (int i = 0; i < MAX_APPLE; i++)
		{
			apple->SetLocation(i);
			if (apple->HitBox(player) == true)
			{
				TotalScore += apple->AppleGet(i);
				//���_�̉������O�ɂ���
				if (TotalScore < 0)
				{
					TotalScore = 0;
				}
			}
		}

	}

	if (PauseFlg == TRUE)
	{
		PauseFlash++;
		if (PauseFlash > 20)
		{
			PauseFlash = 0;
		}
	}
	return this;
	
}

void GameMain::Draw()const
{
	// �w�i�̕`��
	DrawGraph(0, 0, mori_img, TRUE);

	//�v���C���[�̕`��
	player->Draw();

	fps->Disp();

	//�X�R�A�̕`��
	score->Draw();
	//���̃X�R�A�`��	
	DrawFormatString(1070, 100, 0x000000, "%d",TotalScore);

	//�����S�̕`��
	apple->Draw();

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
	}
}

