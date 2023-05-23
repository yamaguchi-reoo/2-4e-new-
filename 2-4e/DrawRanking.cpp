#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	//�w�i�摜�̓ǂݍ���
	if ((Image = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}

	//�t�H���g�̒ǉ�
	HeadLineFont = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);
	//�����L���O�f�[�^�̓ǂݍ���
	Ranking::ReadRanking();

	//BGM�̓ǂݍ���
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, RankingBGM);

	//SE�̓ǂݍ���
	if ((RankingSE = LoadSoundMem("Resource/sounds/SE/Shortbridge03-3.wav")) == -1)
	{
		throw "Resource/sounds/SEShortbridge03-3.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, RankingSE);

	//BGM�̍Đ�
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_BACK, TRUE);
	}
	//SE�̍Đ�
	if (CheckSoundMem(RankingSE) == 0)
	{
		PlaySoundMem(RankingSE, DX_PLAYTYPE_BACK, TRUE);
	}
}


DrawRanking::~DrawRanking()
{
	//BGM�̍폜
	DeleteSoundMem(RankingBGM);
	DeleteSoundMem(RankingSE);

	StopSoundMem(RankingBGM);
	//�t�H���g�̍폜
	DeleteFontToHandle(HeadLineFont);
	DeleteSoundMem(RankingBGM);
}

AbstractScene* DrawRanking::Update()
{
	//A�{�^���Ń^�C�g����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new Title();
	}
	return this;
}

void DrawRanking::Draw() const
{
	DrawGraph(0, 0, Image, TRUE);
	DrawStringToHandle(470, 75, "�����L���O", 0xffd800, HeadLineFont);

	int color = 0xffffff;
	for (int i = 0; i < RANK; i++)
	{
		//���ʂɉ����ĕ����F��ς���(1��:��(���F) 2��:��(��F) 3��:��(���F))
		switch (Ranking::GetData(i).no)
		{
		case 1:
			color = 0xffd700;
			break;
		case 2:
			color = 0xc0c0c0;
			break;
		case 3:
			color = 0x9a6229;
			break;
		case 4:
		case 5:
			color = 0x000000;
			break;
		default:
			break;
		}
		DrawFormatStringToHandle(270, 220 + (70 * i), color, HeadLineFont, "%d��", Ranking::GetData(i).no);
		DrawFormatStringToHandle(400, 220 + (70 * i), color, HeadLineFont, "%.10s", Ranking::GetData(i).name);
		DrawFormatStringToHandle(800, 220 + (70 * i), color, HeadLineFont, "%6dpt", Ranking::GetData(i).score);
	}
	DrawStringToHandle(425, 650, "A �Ń^�C�g��", 0xff0000, HeadLineFont);
}
