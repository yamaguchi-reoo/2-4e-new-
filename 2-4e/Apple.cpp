#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"

Apple::Apple()
{
	images[1] = LoadGraph("Images/Apple.red.png");
	colorimage[1] = LoadGraph("Images/apple.gold");
	colorimage[2] = LoadGraph("Images/apple.poson");
	a_Count = 0;
	frame = 0;
	CheckSpawn[10] = { 0 };
}
Apple::~Apple()
{

}
void Apple::UpDate()
{
	Count = 0;
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			g_Apple[i].y += g_Apple[i].speed;
			g_Apple[i].span += 1;
			Count++;
		}
		if (g_Apple[i].y >= 500)
		{
			g_Apple[i] = g_AppleNl;
			a_Count--;
		}
	}
	if (++frame >= 25)
	{
		Spawn();
		frame = 0;
	}
}
void Apple::Draw() const
{
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			DrawCircle(g_Apple[i].x + APPLE_SIZE / 2, g_Apple[i].y + APPLE_SIZE / 2, APPLE_SIZE / 2, g_Apple[i].img, TRUE);
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x + APPLE_SIZE, g_Apple[i].y + APPLE_SIZE, 0x000000, FALSE);
		}
	}
}

void Apple::Spawn()
{
	Count = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count < ceil(MAX_APPLE - a_Count) / 2)
		{

			//�����_���ȃX�|�[���ł���G���A���擾����
			int Spawn = AppleSpawn();

			//�ǂ��ɂ��X�|�[���ł��Ȃ��ꍇ�ȊO�͂�񂲂̃X�|�[�������ւ͂���
			if (Spawn != -1) {

				//��񂲂̎�ނ𒊑I����
				switch (Rand())
				{
				case 0:
					g_Apple[i] = g_AppleRd;
					g_Apple[i].x = Spawn;
					Count++;	//��x�ɃX�|�[����������񂲂��v������
					break;
				case 1:
					g_Apple[i] = g_AppleBr;
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 2:
					g_Apple[i] = g_AppleGr;
					g_Apple[i].x = Spawn;
					Count++;
					break;
				case 3:
					g_Apple[i] = g_AppleTx;
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
	else if (rand == 19)
	{
		return 3;
	}
	//rand��0�`19�ȊO�̐��l�Ȃ甒�F�i�z��O�j
	else
	{
		return -1;
	}
}

int Apple::AppleSpawn()
{
	int SpawnPos;				// �X�|�[���G���A
	int SpawnFlg = 1;			// �X�|�[���o���邩���f����
	int Check[7] = { 0 };		// �ǂ����X�|�[���o���Ȃ����`�F�b�N����
	int Count = 0;				// �v���p		

	while (1) {

		do {
			SpawnPos = GetRand(6) * 150;
		} while (Check[SpawnPos / 150] == 1);

		for (int i = 0; i < MAX_APPLE; i++)
		{
			//�X�|�[�����悤�Ƃ��Ă��郌�[���ɂ�����񂲂����違�X�|�[�����Ă����莞�Ԍo���Ă��Ȃ����
			if (g_Apple[i].x == SpawnPos && g_Apple[i].span <= 90)
			{
				//�X�|�[���o���Ȃ��̂Ń`�F�b�N�������
				Check[SpawnPos / 150] = 1;
			}
		}
		//�X�|�[�����悤�Ƃ��Ă��郌�[�����󂢂Ă���΂����ɃX�|�[��������
		if (Check[SpawnPos / 150] == 0)
		{
			return SpawnPos;
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