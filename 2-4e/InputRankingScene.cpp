#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"

InputRankingScene::InputRankingScene(int _score)
{
	score = _score;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	
	//フォント追加
	NameFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 32, 8, DX_FONTTYPE_ANTIALIASING);

	//画像読込
	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//SE読込
	if ((SelectSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1)
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision01.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision01.wav";
	}
	//音量調整
	ChangeVolumeSoundMem(70, SelectSE);
	ChangeVolumeSoundMem(70, DecisionSE);
}

InputRankingScene::~InputRankingScene()
{
	DeleteFontToHandle(NameFont1);
	DeleteFontToHandle(NameFont2);
	DeleteFontToHandle(NameFont3);

	DeleteSoundMem(SelectSE);
	DeleteSoundMem(DecisionSE);


}

AbstractScene* InputRankingScene::Update()
{
	//カーソルを上移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {

		//カーソルがはみ出ないように調整する
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.y < 0) {
			if (cursorPoint.x == 10) {
				cursorPoint.y = 3;
			}
			else {
				cursorPoint.y = 4;
			}
			if (cursorPoint.x == 12) {
				cursorPoint.x = 11;
			}
		}
	}
	//カーソルを下移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {

		//カーソルがはみ出ないように調整する
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.y > 3 && cursorPoint.x == 10 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
		if (cursorPoint.y > 3 && cursorPoint.x == 12){
			cursorPoint.x = 11;
		}
	}
	//カーソルを右移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//カーソルがはみ出ないように調整する
		if (++cursorPoint.x == 10 && cursorPoint.y > 3)
		{
			cursorPoint.x = 11;
		}
		if (cursorPoint.x > 11 && cursorPoint.y == 4) {
			cursorPoint.x = 0;
		}
		if (cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	//カーソルを左移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {

		//カーソルがはみ出ないように調整する
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 11;
			}
			else {
				cursorPoint.x = 12;
			}
		}
		if (cursorPoint.x == 10 && cursorPoint.y == 4)
		{
			cursorPoint.x = 9;
		}
	}
	//Aボタンが押されて名前が9文字以上入力されていないなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < NAME_MAX - 1) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		if (cursorPoint.x != 11 || cursorPoint.y != 4)
		{
			name += keyboard[cursorPoint.y][cursorPoint.x];
		}
		else if (name.size() > 0)
		{
			//ランキングを更新する
			Ranking::Insert(score, const_cast<char*>(name.c_str()));

			//ランキングを描画する
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			return new DrawRanking;
		}
	}
	//Bボタンが押されて名前が1文字以上入力されているなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && name.size() > 0) {
		//名前を1文字消す
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		name.erase(name.begin() + (name.size() - 1));
	}
	//1文字以上入力されていてStartボタンが押されたなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)&& name.size() > 0) 
	{
		//ランキングを更新する
		Ranking::Insert(score, const_cast<char*>(name.c_str()));

		//ランキングを描画する
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new DrawRanking;
	}
	return this;
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, img, TRUE);

	DrawStringToHandle(120, 100, "名前入力", 0xffffff, NameFont1);

	DrawBox(470, 240, 820, 300, 0xffffff, TRUE);
	DrawFormatStringToHandle(480, 250, 0x000000, NameFont2, "%s", name.c_str());

	//確定のカーソルだけ大きくする
	if (cursorPoint.x == 11 && cursorPoint.y == 4)
	{
		DrawBox(308 + 50 * cursorPoint.x, 355 + 50 * cursorPoint.y,
			408 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);
		//”確定”の文字色を変える
		DrawStringToHandle(858, 555, "確定", 0x000000,NameFont2);
	}
	else
	{
		DrawBox(308 + 50 * cursorPoint.x, 350 + 50 * cursorPoint.y,
			358 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);
		//普通の文字色の”確定”を描画する
		DrawStringToHandle(858, 555, "確定", 0xffffff, NameFont2);
	}
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
	DrawStringToHandle(390, 640, "STARTボタン or 確定で入力終了", 0xffffff, NameFont3);
}
