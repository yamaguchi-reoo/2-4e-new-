#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	//�w�i�摜�̓ǂݍ���
	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}

	//�t�H���g�̒ǉ�
	RankingFont = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);
	NomalFont = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);
	GuideFont = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);
	//�����L���O�f�[�^�̓ǂݍ���
	RANKING::ReadRanking();

	//BGM�̓ǂݍ���
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, RankingBGM);
	//SE�̓ǂݍ���
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //�I��SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(75, DecisionSE);


	//BGM�̍Đ�
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

DrawRanking::~DrawRanking()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(RankingFont);

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
	DrawGraph(0, 0, ForestImg, TRUE);
	DrawStringToHandle(470, 75, "�����L���O", 0xffd800, RankingFont);

	int color = 0xffffff;
	for (int i = 0; i < RANK; i++)
	{
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
		DrawFormatStringToHandle(470, 220 + (70 * i), color, RankingFont, "%d��", RANKING::GetData(i).no);
		DrawFormatStringToHandle(570, 220 + (70 * i), color, RankingFont, "%5dpt", RANKING::GetData(i).score);

	}
	//DrawCircle(554, 666, 20, 0xffffff, TRUE);
	DrawStringToHandle(455, 650, "A �Ń^�C�g��", 0xff0000, RankingFont);

}