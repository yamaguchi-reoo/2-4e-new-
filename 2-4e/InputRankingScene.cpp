#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include <DxLib.h>

InputRankingScene::InputRankingScene(int _score)
{
	Score = _score;
	XOnce = TRUE;
	YOnce = TRUE;
	CursorPoint = { 0, 0 };
	ranking.ReadRanking();

	//フォント追加
	NameFont1 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 32, 8, DX_FONTTYPE_ANTIALIASING);


	//画像読込
	if ((Img = LoadGraph("Resource/Images/mori.png")) == -1)
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
	ChangeVolumeSoundMem(140, SelectSE);
	ChangeVolumeSoundMem(140, DecisionSE);
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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().ThumbY > 10000 && YOnce == TRUE)) {

		//連続入力しないようにする
		YOnce = FALSE;

		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//カーソルがはみ出ないように調整する
		if (--CursorPoint.y < 0) {
			if (CursorPoint.x == 10) {
				CursorPoint.y = 3;
			}
			else {
				CursorPoint.y = 4;
			}
			if (CursorPoint.x == 12) {
				CursorPoint.x = 11;
			}
		}
	}

	//カーソルを下移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().ThumbY < -10000 && YOnce == TRUE)) {

		//連続入力しないようにする
		YOnce = FALSE;

		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//カーソルがはみ出ないように調整する
		if (++CursorPoint.y > 3 && CursorPoint.x == 10 || CursorPoint.y > 4) {
			CursorPoint.y = 0;
		}
		if (CursorPoint.y > 3 && CursorPoint.x == 12){
			CursorPoint.x = 11;
		}
	
	}

	//カーソルを右移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)|| (PAD_INPUT::GetLStick().ThumbX > 10000 && XOnce == TRUE)) {

		//連続入力しないようにする
		XOnce = FALSE;

		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//カーソルがはみ出ないように調整する
		if (++CursorPoint.x == 10 && CursorPoint.y > 3)
		{
			CursorPoint.x = 11;
		}
		if (CursorPoint.x > 11 && CursorPoint.y == 4) {
			CursorPoint.x = 0;
		}
		if (CursorPoint.x > 12) {
			CursorPoint.x = 0;
		}
	}

	//カーソルを左移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)|| (PAD_INPUT::GetLStick().ThumbX < -10000 && XOnce == TRUE)) {

		//連続入力しないようにする
		XOnce = FALSE;

		//カーソルがはみ出ないように調整する
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--CursorPoint.x < 0) {
			if (CursorPoint.y > 3) {
				CursorPoint.x = 11;
			}
			else {
				CursorPoint.x = 12;
			}
		}
		if (CursorPoint.x == 10 && CursorPoint.y == 4)
		{
			CursorPoint.x = 9;
		}
	}

	//Aボタンが押されたら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);

		//確定ボタンが押された時
		if (CursorPoint.x == 11 && CursorPoint.y == 4)
		{
			//名前が1文字でも入力されていたら
			if (Name.size() > 0)
			{
				//ランキングを更新する
				Ranking::Insert(Score, const_cast<char*>(Name.c_str()));

				//ランキングを描画する
				PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
				return new DrawRanking;
			}
		}
		//名前が9文字以上入力されていないなら
		else if(Name.size() < NAME_MAX - 1)
		{
			//名前を入力する
			Name += KeyBoard[CursorPoint.y][CursorPoint.x];
		}
	}

	//Bボタンが押されて名前が1文字以上入力されているなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && Name.size() > 0) {
		//名前を1文字消す
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		Name.erase(Name.begin() + (Name.size() - 1));
	}

	//1文字以上入力されていてStartボタンが押されたなら
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)&& Name.size() > 0) 
	{
		//ランキングを更新する
		Ranking::Insert(Score, const_cast<char*>(Name.c_str()));

		//ランキングを描画する
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new DrawRanking;
	}

	//LスティックのX座標が元の位置に戻ったらフラグをリセットする
	if (PAD_INPUT::GetLStick().ThumbX < 10000 && PAD_INPUT::GetLStick().ThumbX > -10000 && XOnce == FALSE) {
		XOnce = TRUE;
	}	
	//LスティックのY座標が元の位置に戻ったらフラグをリセットする
	if (PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000 && YOnce == FALSE) {
		YOnce = TRUE;
	}
	return this;
}

void InputRankingScene::Draw() const {

	DrawGraph(0, 0, Img, TRUE);

	DrawStringToHandle(120, 100, "名前入力", 0xffffff, NameFont1);

	DrawBox(470, 240, 820, 300, 0xffffff, TRUE);
	DrawFormatStringToHandle(480, 250, 0x000000, NameFont2, "%s", Name.c_str());

	//確定のカーソルだけ大きくする
	if (CursorPoint.x == 11 && CursorPoint.y == 4)
	{
		DrawBox(308 + 50 * CursorPoint.x, 355 + 50 * CursorPoint.y,
			408 + 50 * CursorPoint.x, 407 + 50 * CursorPoint.y, 0x808080, TRUE);
		//”確定”の文字色を変える
		DrawStringToHandle(858, 555, "確定", 0x000000,NameFont2);
	}
	else
	{
		DrawBox(308 + 50 * CursorPoint.x, 353 + 50 * CursorPoint.y,
			358 + 50 * CursorPoint.x, 405 + 50 * CursorPoint.y, 0x808080, TRUE);
		//普通の文字色の”確定”を描画する
		DrawStringToHandle(858, 555, "確定", 0xffffff, NameFont2);
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == CursorPoint.x && i == CursorPoint.y) {
				//I、i、Lの文字の空白を調整する
				if (i == 0 && j == 8 && KeyBoard[0][8] || i == 2 && j == 8 && KeyBoard[2][8] || i == 2 && j == 11 && KeyBoard[2][11]) {
					DrawFormatStringToHandle(j * 50 + 328, i * 50 + 355, 0x000000, NameFont2, "%c", KeyBoard[i][j]);
				}
				//gの文字高さを調整する
				else if (i == 2 && j == 6 && KeyBoard[0][8]) {
					DrawFormatStringToHandle(j * 50 + 318, i * 50 + 345, 0x000000, NameFont2, "%c", KeyBoard[i][j]);
				}
				else
				{
					DrawFormatStringToHandle(j * 50 + 318, i * 50 + 358, 0x000000, NameFont2, "%c", KeyBoard[i][j]);
				}
			}
			else
			{
				//I、i、Lの文字の空白を調整する
				if (i == 0 && j == 8 && KeyBoard[0][8]||i == 2 && j == 8 && KeyBoard[2][8]||i == 2 && j == 11 && KeyBoard[2][11]) {
					DrawFormatStringToHandle(j * 50 + 328, i * 50 + 355, 0xffffff, NameFont2, "%c", KeyBoard[i][j]);
				}
				//gの文字高さを調整する
				else if (i == 2 && j == 6 && KeyBoard[0][8]) {
					DrawFormatStringToHandle(j * 50 + 318, i * 50 + 348, 0xffffff, NameFont2, "%c", KeyBoard[i][j]);
				}
				else
				{
					DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0xffffff, NameFont2, "%c", KeyBoard[i][j]);
				}
				
			}
		
		}
	}
	DrawStringToHandle(390, 640, "STARTボタン or 確定で入力終了", 0xffffff, NameFont3);
}
