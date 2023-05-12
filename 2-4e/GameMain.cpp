#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"
#include "Score.h"
#include "PadInput.h"

int GameMain::getScore = 0;
GameMain::GameMain()
{
	
	//������
	frame = 0;
	for (int i = 0; i < 4; i++) {
		gGetApple[i] = 0;
	}
	for (int i = 0; i < 7; i++) {
		CheckSpawn[i] = FALSE;
	}
	gGetAppleType = 0;
	TotalScore = 0;
	PauseFlg = FALSE;
	PauseFlash = 0;
	Time = 3599;
	GetPsAppleTime = 0;
	PlayerDispFlg = TRUE;
	TimerColor = GetColor(0,0,0);
	SEflg = 0;

	//�I�u�W�F�N�g��
	player = new Player();
	for (int i = 0; i < MAX_APPLE; i++) {
		apple[i] = new Apple();
	}
	score = new Score();

	//�摜�̓ǂݍ���
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//��񂲉摜�̓ǂݍ���
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple red.png")) == -1)
	{
		throw "Resource/Images/apple red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/BlueApple.png")) == -1)
	{
		throw "Resource/Images/BlueApple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/applegold.png")) == -1)
	{
		throw "Resource/Images/applegold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/applepoison.png")) == -1)
	{
		throw "Resource/Images/applepoison.png";
	}

	//BGM�̓ǂݍ���
	if ((MainBGM = LoadSoundMem("Resource/sounds/BGM/seiya.wav")) == -1)
	{
		throw "Resource/sounds/BGM/seiya.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(90, MainBGM);

	//SE�̓Ǎ�
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

	//BGM
	//if (CheckSoundMem(MainBGM) == 0)
	//{
		//PlaySoundMem(MainBGM, DX_PLAYTYPE_BACK);
	//}

}

GameMain::~GameMain()
{
	//�I�u�W�F�N�g�̍폜
	delete player;
	for (int i = 0; i < MAX_APPLE; i++) {
		delete apple[i];
	}
	delete score;
	

	//�T�E���h�폜
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
		StopSoundMem(MainBGM);
	}
	//�|�[�Y���łȂ��Ȃ�
	if (PauseFlg == FALSE) {
		//�����̍X�V
		player->UpDate();
		for (int i = 0; i < 10; i++) {
			apple[i]->UpDate();
		}
		//BGM
		if (CheckSoundMem(MainBGM) == 0)
		{
			PlaySoundMem(MainBGM, DX_PLAYTYPE_LOOP,FALSE);
		}

		//��񂲂̉�ʏ�����J��Ԃ�
		for (int i = 0; i < MAX_APPLE; i++)
		{
			//��񂲂��X�|�[�����Ă����莞�ԗ����Ă����
			if (apple[i]->GetAppleTime() == 100)
			{
				//�X�|�[���\��
				CheckSpawn[apple[i]->GetAppleLocationX()/150] = FALSE;
			}
			//��񂲂ƃv���C���[���ڐG���āA�v���C���[���_�ŏ�ԂłȂ��Ȃ��񂲎擾������
			if (apple[i]->HitBox(player) == true && GetPsAppleTime == 0)
			{
				//�������񂲂̎�ނ��擾���đΉ�����l�����Z����
				gGetAppleType = apple[i]->GetAppleType();
				gGetApple[gGetAppleType]++;
				//�������񂲂̓��_���擾
				TotalScore += apple[i]->GetApplePoint();
				//��񂲃��Z�b�g
				apple[i]->AppleReset();
				//�����擾������񂲂��łȂ�A
				if (gGetAppleType == 3)
				{
					//�v���C���[�̓_�ŏ������J�n����
					GetPsAppleTime = 1;
					PlaySoundMem(PoisonAppleSE, DX_PLAYTYPE_BACK);
				}
				else
				{
					PlaySoundMem(AppleSE, DX_PLAYTYPE_BACK);
				}
				//���_�̉������O�ɂ���
				if (TotalScore < 0)
				{
					TotalScore = 0;
				}
			}
			//��񂲂�Y��1000�ȏ�Ȃ�폜�i���Z�b�g�j
			if (apple[i]->GetAppleLocationY() >= 1000)
			{
				//��񂲂����Z�b�g
				apple[i]->AppleReset();
			}

		}
		//25�t���[�����ɂ�񂲐�������
		if (++frame >= 25)
		{
			//�X�|�[���ł���ꏊ�����邩�`�F�b�N
			SpawnFlg = FALSE;
			for (int i = 0; i < 7; i++)
			{
				if (CheckSpawn[i] == FALSE)
				{
					SpawnFlg = TRUE;
				}
			}
			//��ł��X�|�[���ł���ꏊ������Ȃ�
			if (SpawnFlg == TRUE)
			{
				SpawnApple = -1;
				//�X�|�[���ł����񂲂����邩�`�F�b�N
				for (int i = 0; i < MAX_APPLE; i++)
				{
					//�X�|�[���ł����񂲂�����������
					if (apple[i]->GetAppleFlg() == FALSE)
					{
						//�i�[����for�𔲂���
						SpawnApple = i;
						break;
					}
				}
				//�X�|�[���o�����񂲂������
				if (SpawnApple != -1) {
					//�X�|�[���ł���ꏊ��������܂�Rand���J��Ԃ�
					do {
						SpawnPos = GetRand(6);
					} while (CheckSpawn[SpawnPos] == TRUE);
					//��񂲐���
					apple[SpawnApple]->Spawn();
					//��񂲂̍��W����
					apple[SpawnApple]->SetLocation(SpawnPos * 150);
					//��񂲐����σ`�F�b�N�������
					CheckSpawn[SpawnPos] = TRUE;
					//25�t���[�������Ȃ���
					frame = 0;
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

	//�ꎞ��~��
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
		return new Result();//�����Ń��U���g��ʂֈڍs�i�X�R�A��TotalScore�ɁA�ǂ̂�񂲂������擾�������̓����GetApple[]�ɓ����Ă���j
		
	}
	if (Time <= 600) {
		TimerColor = GetColor(255-Time/3,0,0);
	}

	//��ʐؑ֎�SE
	if (CheckSoundMem(StartSE) == 0)
	{
		if (SEflg++ == 1)
		{
			PlaySoundMem(StartSE, DX_PLAYTYPE_BACK);
		}
	}
	GameMain::getScore = TotalScore;
	return this;
	
}

void GameMain::Draw()const
{
	// �w�i�̕`��
	DrawGraph(0, 0, ForestImg, TRUE);
	// �X�R�A�̕`��
	DrawBox(1000, 0, 1280, 720, 0xffffff, TRUE);
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);
	for (int i = 0; i < 3; i++) {
		DrawFormatString(1067 + i * 60, 320, 0x000000, "%.2d", gGetApple[i]);
	}
	SetFontSize(30);
	DrawString(1105, 450, "���_", 0x000000);
	DrawFormatString(1095, 500, 0x000000, "%.5d", TotalScore);
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

	//�v���C���[�̕`��
	if (PlayerDispFlg == TRUE) {
		player->Draw();
	}

	//�����S�̕`��
	for (int i = 0; i < 10; i++) {
		apple[i]->Draw();
	}

	for (int i = 0; i < 7; i++) {
		DrawFormatString(0 + i * 150, 320, 0x000000, "%.2d", CheckSpawn[i]);
	}
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


