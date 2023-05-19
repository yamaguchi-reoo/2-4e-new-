#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"


InputRankingScene::InputRankingScene(int _score)
{
	score = _score;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	for (int i = 0; i < 5; i++) {
		RankingData[i] = ranking.GetData(i);
	}
	
	NameFont1 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 32, 8, DX_FONTTYPE_ANTIALIASING);

	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//SE‚Ì“Ç‚Ýž‚Ý
	if ((SelectSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //‘I‘ðSE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/coin04.wav")) == -1) //‘I‘ðSE
	{
		throw "Resource/sounds/SE/coin04.wav";
	}
	//SE‚Ì‰¹—Ê•ÏX
	ChangeVolumeSoundMem(55, SelectSE);
	ChangeVolumeSoundMem(125, DecisionSE);
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, image, TRUE);
	//DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	
	DrawStringToHandle(470, 75, "–¼‘O“ü—Í", 0xffffff,NameFont1);

	DrawBox(420, 240, 860, 300, 0xffffff, TRUE);
	DrawFormatStringToHandle(420, 250, 0x000000, NameFont2, "%s", name.c_str());

	DrawBox(308 + 50 * cursorPoint.x, 350 + 50 * cursorPoint.y,
		358 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0xffffff, NameFont2, "%c", keyboard[i][j]);
		}
	}

	DrawStringToHandle(435, 640, "B BUTTON PUSH", 0x000000, NameFont3);
}

AbstractScene* InputRankingScene::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.y < 0) {
			if (cursorPoint.x > 9) {
				cursorPoint.y = 3;
			}
			else {
				cursorPoint.y = 4;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.y > 3 && cursorPoint.x > 9 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.x > 9 && cursorPoint.y > 3 || cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 9;
			}
			else {
				cursorPoint.x = 12;
			}
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < 10) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		name += keyboard[cursorPoint.y][cursorPoint.x];
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && name.size() > 0) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			name.erase(name.begin() + (name.size() - 1));
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START) && name.size() > 0) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		Ranking::Insert(score);
		return new DrawRanking;
	}
	return this;
}
