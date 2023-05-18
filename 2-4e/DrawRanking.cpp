#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	//背景画像の読み込み
	if ((Image = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}

	//フォントの追加
	HeadLineFont = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 64, 8, DX_FONTTYPE_ANTIALIASING);
	//ランキングデータの読み込み
	Ranking::ReadRanking();

	//BGMの読み込み
	if ((RankingBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, RankingBGM);
	//SEの読み込み
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //選択SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(75, DecisionSE);


	//BGMの再生
	if (CheckSoundMem(RankingBGM) == 0)
	{
		PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}


DrawRanking::DrawRanking(int score)
{
}

DrawRanking::~DrawRanking()
{
	//フォントの削除
	DeleteFontToHandle(HeadLineFont);

}

AbstractScene* DrawRanking::Update()
{
	//Aボタンでタイトルへ
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new Title();
	}
	return this;
}

void DrawRanking::Draw() const
{
	DrawGraph(0, 0, Image, TRUE);
	DrawStringToHandle(470, 75, "ランキング", 0xffd800, HeadLineFont);

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
		DrawFormatStringToHandle(470, 220 + (70 * i), color, HeadLineFont, "%d位", Ranking::GetData(i).no);
		DrawFormatStringToHandle(570, 220 + (70 * i), color, HeadLineFont, "%6dpt", Ranking::GetData(i).score);
	}
	DrawStringToHandle(455, 650, "A でタイトル", 0xff0000, HeadLineFont);

}
