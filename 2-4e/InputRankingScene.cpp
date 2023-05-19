#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"


InputRankingScene::InputRankingScene(int _score)
{
	score = _score;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	
	NameFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 32, 8, DX_FONTTYPE_ANTIALIASING);

	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
}
InputRankingScene::~InputRankingScene()
{
	DeleteFontToHandle(NameFont1);
	DeleteFontToHandle(NameFont2);
	DeleteFontToHandle(NameFont3);
}

AbstractScene* InputRankingScene::Update()
{
	//カーソルを上移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {

		//カーソルがはみ出ないように調整する
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
	//カーソルを下移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {

		//カーソルがはみ出ないように調整する
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.y > 3 && cursorPoint.x > 9 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
	}
	//カーソルを右移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//カーソルがはみ出ないように調整する
		if (++cursorPoint.x > 9 && cursorPoint.y > 3 || cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	//カーソルを左移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {

		//カーソルがはみ出ないように調整する
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
	//Aボタンが押されて名前が9文字以上入力されていないなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < NAME_MAX-1) {

		//名前に現在のカーソル上の文字を追加する
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < 10) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		name += keyboard[cursorPoint.y][cursorPoint.x];
	}
	//Bボタンが押されて名前が1文字以上入力されているなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && name.size() > 0) {

		//名前を1文字消す
		name.erase(name.begin() + (name.size() - 1));
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			name.erase(name.begin() + (name.size() - 1));
	}
	//1文字以上入力されていてStartボタンが押されたなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START) && name.size() > 0) {

		//ランキングを更新する
		Ranking::Insert(score, const_cast<char*>(name.c_str()));

		//ランキングを描画する
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		Ranking::Insert(score);
		return new DrawRanking;
	}
	return this;
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, img, TRUE);

	DrawStringToHandle(120, 100, "名前入力", 0xffffff, NameFont1);

	DrawBox(470, 240, 820, 300, 0xffffff, TRUE);
	DrawFormatStringToHandle(480, 250, 0x000000, NameFont2, "%s", name.c_str());

	DrawBox(308 + 50 * cursorPoint.x, 350 + 50 * cursorPoint.y,
		358 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == cursorPoint.x && i == cursorPoint.y) {
				DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0x000000, NameFont2, "%c", keyboard[i][j]);
			}
			else
			{
				DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0xffffff, NameFont2, "%c", keyboard[i][j]);
			}
		
		}
	}

	DrawStringToHandle(435, 640, "STARTボタンで入力終了", 0xffffff, NameFont3);
}
