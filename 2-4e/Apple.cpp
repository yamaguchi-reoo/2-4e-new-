#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

//�R���X�g���N�^
Apple::Apple()
{
	//������
	a_Count = 0;		
	frame = 0;	

	for (int i = 0; i < 10; i++) {
		CheckSpawn[i] = 0;
		e_Apple[i].point = 0;
		e_Apple[i].pointeffect = 0;
	}
	for (int i = 0; i < 4; i++) {
		gGetApple[i] = 0;
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
}
//�f�X�g���N�^
Apple::~Apple()
{

}

//�X�V
void Apple::UpDate()
{
	//���ʂɑ��ݏo�����񂲂̌����J��Ԃ�
	for (int i = 0; i < MAX_APPLE; i++)
	{
		//������񂲂��X�|�[���ςȂ�
		if (g_Apple[i].flg == TRUE)
		{
			//�e��񂲂̑��x�̐�����Y���W�����Z����
			g_Apple[i].y += g_Apple[i].speed;

			//��񂲂���ʓ��ɂ��鎞�Ԃ��v��
			g_Apple[i].time += 1;

			//Y��1000�ȏ�Ȃ�폜����
			if (g_Apple[i].y >= 1000)
			{
				AppleDelete(i);
			}
		}
		//�_���擾���o�p
		if (e_Apple[i].effectflg == TRUE)
		{
			if (--e_Apple[i].y <= e_Apple[i].pointeffect)
			{
				e_Apple[i].effectflg == FALSE;
			}

		}
	}	
	//25�t���[�����ɂ�񂲂̃X�|�[������
	if (++frame >= 25)
	{
		Spawn();
		frame = 0;
	}
}
//�`��
void Apple::Draw() const
{
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			//��񂲂̉摜���A�b�v���ꂽ��DrawGraph�̕��ɕύX
				DrawGraph(g_Apple[i].x, g_Apple[i].y, g_Apple[i].img, TRUE);
				DrawBox(g_Apple[i].x - (APPLE_SIZE * 0.1), g_Apple[i].y - (APPLE_SIZE * 0.1), 
					(g_Apple[i].x - (APPLE_SIZE * 0.1)) + APPLE_SIZE, (g_Apple[i].y - (APPLE_SIZE * 0.1)) + APPLE_SIZE, 0x000000, FALSE);
		}
		//�_���擾���o
		if (e_Apple[i].effectflg == TRUE)
		{
			DrawFormatString(e_Apple[i].x, e_Apple[i].y, 0x000000, "+%d", e_Apple[i].point);
		}
	}

	//�擾������񂲂̌��\��
	for (int i = 0; i < 3; i++) {
		DrawFormatString(1067+i*60, 320, 0x000000, "%.2d", gGetApple[i]);
	}
}

//�X�|�[������
void Apple::Spawn()
{
	Count = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count < ceil(MAX_APPLE - a_Count) / 2)
		{

			//�����_���ȃX�|�[���ł���G���A���擾����
			int Spawn = AppleSpawnPos();

			//�ǂ��ɂ��X�|�[���ł��Ȃ��ꍇ�ȊO�͂�񂲂̃X�|�[�������ւ͂���
			if (Spawn != -1) {

				//��񂲂̎�ނ𒊑I����
				switch (Rand())
				{
				case 0:
					g_Apple[i] = g_AppleRd;			//�w�肳�ꂽ�F�̂�񂲂̏����i�[����
					g_Apple[i].img = gAppleImg[0];	//img�ɉ摜���i�[����
					g_Apple[i].x = Spawn;			//�X�|�[������ꏊ�̒��I
					Count++;						//��x�ɃX�|�[����������񂲂��v������
					break;
				case 1:
					g_Apple[i] = g_AppleBr;
					g_Apple[i].img = gAppleImg[1];
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 2:
					g_Apple[i] = g_AppleGr;
					g_Apple[i].img = gAppleImg[2];
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 3:
					g_Apple[i] = g_AppleTx;
					g_Apple[i].img = gAppleImg[3];
					g_Apple[i].x = Spawn;
					Count++;
					break;
				default:	//�z�肵�Ă��Ȃ����l������Ɣ��F��
					g_Apple[i] = g_AppleRd;
					g_Apple[i].img = 0xffffff;
					g_Apple[i].x = Spawn;
					break;
				}
			}
		}
	}
	a_Count += Count;	//���ŏo���������S�̌������v�ɑ���
}
//�X�|�[�������񂲂̎�ނ̒��I
int Apple::Rand()
{
	int rand = GetRand(19);
	//rand��0�`11�Ȃ�ԐF�i�U�O���j
	if (rand >= 0 && rand <= 11)
	{
		return 0;
	}
	//rand��12�`16�Ȃ�F�i�Q�T���j
	else if (rand > 11 && rand <= 16)
	{
		return 1;
	}
	//rand��17�`18�Ȃ���F�i�P�O���j
	else if (rand > 16 && rand <= 18)
	{
		return 2;
	}
	//rand��19�Ȃ率�F�i�Łj�i�T���j
	else if (rand > 18)
	{
		return 3;
	}
	//rand��0�`19�ȊO�̐��l�Ȃ甒�F�i�z��O�j
	else
	{
		return -1;
	}
}
//�X�|�[������ʒu�̒��I
int Apple::AppleSpawnPos()
{
	int SpawnPos;				// �X�|�[���G���A
	int SpawnFlg = 1;			// �X�|�[���o���邩���f����
	int Check[7] = {};		// �ǂ����X�|�[���o���Ȃ����`�F�b�N����
	int Count = 0;				// �v���p		

	while (1) {

		do {
			SpawnPos = GetRand(6);
		} while (Check[SpawnPos] == 1);

		for (int i = 0; i < MAX_APPLE; i++)
		{
			//�X�|�[�����悤�Ƃ��Ă��郌�[���ɂ�����񂲂����違�X�|�[�����Ă����莞�Ԍo���Ă��Ȃ����
			if (g_Apple[i].x == SpawnPos * 150 && g_Apple[i].time <= g_Apple[i].span)
			{
				//�X�|�[���o���Ȃ��̂Ń`�F�b�N�������
				Check[SpawnPos] = 1;
			}
		}
		//�X�|�[�����悤�Ƃ��Ă��郌�[�����󂢂Ă���΂����ɃX�|�[��������
		if (Check[SpawnPos] == 0)
		{
			return SpawnPos * 150;
		}

		//�ǂ̃��[�����X�|�[���ł��Ȃ������ׂ�
		for (int i = 0; i < 7; i++)
		{
			if (Check[i] == 1)
			{
				Count++;
			}
		}
		//�S���̃��[���ŃX�|�[���s�Ȃ�
		if (Count >= 7)
		{
			return -1;	//�X�|�[�����s
		}
	}
}
//��񂲂̍폜
void Apple::AppleDelete(int i) {
	g_Apple[i] = g_AppleNl;
	a_Count--;
}
//��񂲂̎擾
int Apple::AppleGet(int i)
{
	//�߂�l�i�擾���链�_���j����
	int p = g_Apple[i].point;
	//�擾������񂲂̎�ނ𔻕�
	gGetApple[g_Apple[i].type]++;
	//�擾���o�J�n
	e_Apple[i].effectflg = TRUE;
	e_Apple[i].point = g_Apple[i].point;
	e_Apple[i].pointeffect = g_Apple[i].y - 50;
	e_Apple[i].x = g_Apple[i].x;
	e_Apple[i].y = g_Apple[i].y;

	if (g_Apple[i].type == 3) {
		//�Ń����S���擾�����Ƃ��̏���
	
	}
	else
	{
		//�Ń����S�ȊO�̂�񂲂���������̏���
	}
	//�擾���ꂽ��񂲂����Z�b�g
	g_Apple[i] = g_AppleNl;
	//��ɑ��݂��Ă����񂲂̌�������
	a_Count--;
	return p;
}
//�擾������񂲂̎�ނ̔���
int Apple::AppleTypeGet(int i)
{
	return g_Apple[i].type;
}
//BoxCollider�ɓn�����l�̐ݒ�
void Apple::SetLocation(int i)
{
	//BoxCollider�ɓn���l�̐ݒ�
	location.x = g_Apple[i].x;
	location.y = g_Apple[i].y;
	erea.rate = g_Apple[i].rate;
}