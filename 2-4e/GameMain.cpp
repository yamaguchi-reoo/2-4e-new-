#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"

#define TIMER 180

GameMain::GameMain()
{
	//������
	TotalScore = 0;

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
	DrawFormatString(100, 100, 0x000000, "%d",TotalScore);

	//�����S�̕`��
	apple->Draw();
}

