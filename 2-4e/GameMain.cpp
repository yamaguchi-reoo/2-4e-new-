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
	GetPsAppleTime = 0;
	PlayerDispFlg = TRUE;
	TimerColor = GetColor(0,0,0);
	Soundflg = 0;

	//�I�u�W�F�N�g��
	player = new Player();
	apple = new Apple();
	score = new Score();

	//�摜�̓ǂݍ���
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//BGM�̓ǂݍ���
	if ((MainBGM = LoadSoundMem("Resource/sounds/BGM/seiya.wav")) == -1)
	{
		throw "Resource/sounds/BGM/seiya.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(90, MainBGM);

	//�T�E���h�Ǎ�
	if ((StartSE = LoadSoundMem("Resource/sounds/SE/Start.wav")) == -1) 
	{
		throw "Resource/sounds/SE/Start.wav";
	}
	if ((AppleSE = LoadSoundMem("Resource/sounds/SE/Apple.wav")) == -1) 
	{
		throw "Resource/sounds/SE/Apple.wav";
	}
	if ((PoisonAppleSE = LoadSoundMem("Resource/sounds/SE/ToxicApple.wav")) == -1) 
	{
		throw "Resource/sounds/SE/ToxicAplle.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(70, StartSE);
	ChangeVolumeSoundMem(100, AppleSE);
	ChangeVolumeSoundMem(100, PoisonAppleSE);


}

GameMain::~GameMain()
{
	//�I�u�W�F�N�g�̍폜
	delete player;
	delete apple;
	delete score;

	//�T�E���h�폜
	DeleteSoundMem(MainBGM);
	DeleteSoundMem(StartSE);
	DeleteSoundMem(AppleSE);
	DeleteSoundMem(PoisonAppleSE);


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
			if (apple->HitBox(player) == true && GetPsAppleTime == 0)
			{
				//�����擾������񂲂��łȂ�A
				if (apple->AppleTypeGet(i) == 3)
				{
					//�v���C���[�̓_�ŏ������J�n����
					GetPsAppleTime = 1;
					PlaySoundMem(PoisonAppleSE, DX_PLAYTYPE_BACK);

				}
				else
				{
					PlaySoundMem(AppleSE, DX_PLAYTYPE_BACK);
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
		if (GetPsAppleTime > 0)
		{
			if (++GetPsAppleTime % 20 == 0)
			{
				PlayerDispFlg = !PlayerDispFlg;
			}
			if (GetPsAppleTime >= 120)
			{
				GetPsAppleTime = 0;
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
		//�����Ń��U���g��ʂֈڍs�i�X�R�A��TotalScore�ɁA�ǂ̂�񂲂������擾�������̓����GetApple[]�ɓ����Ă���j
		Time = 600;	//���U���g�ڍs�������o����������Ă���
	}
	if (Time <= 600) {
		TimerColor = GetColor(255-Time/3,0,0);
	}

	//BGM
	if (CheckSoundMem(MainBGM) == 0)
	{
		PlaySoundMem(MainBGM, DX_PLAYTYPE_BACK);
	}

	//��ʐؑ֎�SE
	if (CheckSoundMem(StartSE) == 0)
	{
		if (Soundflg++ == 1)
		{
			PlaySoundMem(StartSE, DX_PLAYTYPE_BACK);
		}
	}
	return this;
	
}

void GameMain::Draw()const
{
	// �w�i�̕`��
	DrawGraph(0, 0, ForestImg, TRUE);

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
		DrawFormatString(1120+GetRand(10-Time/30), 200+GetRand(10-Time/30), TimerColor, "%2.2d", Time / 60 + 1);
	}
	else {
		DrawFormatString(1120, 200, TimerColor, "%.2d", Time / 60 + 1);
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

