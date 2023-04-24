#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	//背景画像の読み込み
	if ((Image = LoadGraph("Resource/Images/End.png")) == -1)
	{
		throw "Resource/Images/End.png";
	}

	//フォントの追加
	HeadLineFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	NomalFont = CreateFontToHandle("Nomal", 64, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	GuideFont = CreateFontToHandle("Guide", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//ランキングデータの読み込み
	RANKING::ReadRanking();

	//BGM読み込み
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.mp3")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.mp3";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, RankingBGM);

	//決定ボタンのSE
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(200, DecisionSE);

	//BGMの再生
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

DrawRanking::~DrawRanking()
{
	//フォントの削除
	DeleteFontToHandle(HeadLineFont);
	DeleteFontToHandle(NomalFont);
	DeleteFontToHandle(GuideFont);

	//サウンドの削除
	DeleteSoundMem(DecisionSE);
	DeleteSoundMem(RankingBGM);
}

AbstractScene* DrawRanking::Update()
{


	//Aボタンでタイトルへ
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
	DrawStringToHandle(440, 75, "ランキング", 0xffd800, HeadLineFont);

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
		DrawFormatStringToHandle(490, 250 + (70 * i), color, NomalFont, "%d位", RANKING::GetData(i).no);
		DrawFormatStringToHandle(590, 250 + (70 * i), color, NomalFont, "%5dpt", RANKING::GetData(i).score);

	}
	DrawCircle(554, 666, 20, 0xffffff, TRUE);
	DrawStringToHandle(545, 650, "A でタイトル", 0xff0000, GuideFont);

}