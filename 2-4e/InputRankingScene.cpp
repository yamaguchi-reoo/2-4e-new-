#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"


InputRankingScene::InputRankingScene(int _score)
{
	score = _score;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	
	NameFont1 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 32, 8, DX_FONTTYPE_ANTIALIASING);

	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, image, TRUE);
	//DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	
	DrawStringToHandle(120, 100, "–¼‘O“ü—Í", 0x000000,NameFont1);

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
		if (++cursorPoint.y > 3 && cursorPoint.x > 9 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
	
		if (++cursorPoint.x > 9 && cursorPoint.y > 3 || cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 9;
			}
			else {
				cursorPoint.x = 12;
			}
		}
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < 9) {
		name += keyboard[cursorPoint.y][cursorPoint.x];
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && name.size() > 0) {
			name.erase(name.begin() + (name.size() - 1));
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START) && name.size() > 0) {
		//‚±‚±‚Å–¼‘O‚ğcharŒ^‚É‚µ‚Äscore‚Æˆê‚Éƒ‰ƒ“ƒLƒ“ƒOXV‰æ–Ê‚É‘—‚è‚½‚¢
		Ranking::Insert(score, const_cast<char*>(name.c_str()));
		return new DrawRanking;
	}
	return this;
}
