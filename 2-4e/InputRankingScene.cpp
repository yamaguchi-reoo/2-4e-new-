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

	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, image, TRUE);
		SetFontSize(80);
		DrawString(120, 100, "INPUT RANKING", 0x000000);

		SetFontSize(48);
	DrawBox(420, 240, 860, 300, 0x000000, TRUE);
	DrawFormatString(420, 250, 0xFFFFFF, "%s", name.c_str());

	DrawBox(318 + 50 * cursorPoint.x, 360 + 50 * cursorPoint.y,
		368 + 50 * cursorPoint.x, 405 + 50 * cursorPoint.y, 0x808080, TRUE);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			DrawFormatString(j * 50 + 318, i * 50 + 355, 0x000000, "%c", keyboard[i][j]);
		}
	}

	SetFontSize(32);
	DrawString(435, 640, "B BUTTON PUSH", 0x000000);
}

AbstractScene* InputRankingScene::Update()
{
	if (PAD_INPUT::OnButton(PAD_INPUT_UP)) {
		if (--cursorPoint.y < 0) {
			if (cursorPoint.x > 10) {
				cursorPoint.y = 3;
			}
			else {
				cursorPoint.y = 4;
			}
		}
	}
	if (PAD_INPUT::OnButton(PAD_INPUT_DOWN)) {
		if (++cursorPoint.y > 3 && cursorPoint.x > 10 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
	}
	if (PAD_INPUT::OnButton(PAD_INPUT_RIGHT)) {
	
		if (++cursorPoint.x > 10 && cursorPoint.y > 3 || cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	if (PAD_INPUT::OnButton(PAD_INPUT_LEFT)) {
		
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 10;
			}
			else {
				cursorPoint.x = 12;
			}
		}
	}

	if (PAD_INPUT::OnButton(PAD_INPUT_A) && name.size() < 5) {
		if (keyboard[cursorPoint.y][cursorPoint.x] == '<' && name.size() > 0) {
			name.erase(name.begin() + (name.size() - 1));
		}
		else {
			name += keyboard[cursorPoint.y][cursorPoint.x];
		}
	}
	return this;
}

//void RANKING::WriteRanking(std::string _name, long int _score)
//{
//}

//ÉVÅ[ÉìÇÃïœçXèàóù
AbstractScene* InputRankingScene::ChangeScene()
{
	if (PAD_INPUT::OnButton(PAD_INPUT_A)) {
		return new DrawRanking(score);
	}

	return this;
}
