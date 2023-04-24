#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	//�w�i�摜�̓ǂݍ���
	if ((Image = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}

	//�t�H���g�̒ǉ�
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	NomalFont = CreateFontToHandle("Nomal", 64, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	GuideFont = CreateFontToHandle("Guide", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�����L���O�f�[�^�̓ǂݍ���
	RANKING::ReadRanking();

	//BGM�ǂݍ���
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.mp3")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.mp3";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, RankingBGM);

	//����{�^����SE
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(200, DecisionSE);

	//BGM�̍Đ�
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

DrawRanking::~DrawRanking()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(HeadLineFont);
	DeleteFontToHandle(NomalFont);
	DeleteFontToHandle(GuideFont);

	//�T�E���h�̍폜
	DeleteSoundMem(DecisionSE);
	DeleteSoundMem(RankingBGM);
}

AbstractScene* DrawRanking::Update()
{


	//A�{�^���Ń^�C�g����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(RankingBGM);
		return new Title();
	}
	return this;
}

void DrawRanking::Draw() const
{
	DrawGraph(0, 0, Image, TRUE);
	DrawStringToHandle(440, 75, "�����L���O", 0xffd800, HeadLineFont);

	int color = 0xffffff;
	for (int i = 0; i < RANK; i++)
	{
		switch (RANKING::GetData(i).no)
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
		DrawFormatStringToHandle(490, 250 + (70 * i), color, NomalFont, "%d��", RANKING::GetData(i).no);
		DrawFormatStringToHandle(590, 250 + (70 * i), color, NomalFont, "%5dpt", RANKING::GetData(i).score);

	}
	DrawCircle(554, 666, 20, 0xffffff, TRUE);
	DrawStringToHandle(545, 650, "A �Ń^�C�g��", 0xff0000, GuideFont);

}