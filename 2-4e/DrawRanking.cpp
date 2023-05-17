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
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	NomalFont = CreateFontToHandle("Nomal", 64, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	GuideFont = CreateFontToHandle("Guide", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�����L���O�f�[�^�̓ǂݍ���
	Ranking::ReadRanking();
}

DrawRanking::~DrawRanking()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(HeadLineFont);
	DeleteFontToHandle(NomalFont);
	DeleteFontToHandle(GuideFont);

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
	DrawStringToHandle(440, 75, "�����L���O", 0xffd800, HeadLineFont);

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
		DrawFormatStringToHandle(490, 250 + (70 * i), color, NomalFont, "%d��", Ranking::GetData(i).no);
		DrawFormatStringToHandle(590, 250 + (70 * i), color, NomalFont, "%5dpt", Ranking::GetData(i).score);

	}
	DrawCircle(554, 666, 20, 0xffffff, TRUE);
	DrawStringToHandle(545, 650, "A �Ń^�C�g��", 0xff0000, GuideFont);

}