#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"

//タイトルメニュー
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{
	//初期化
	Select = 0;

	MenuFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//タイトル画像の読み込み
	if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	// カーソル画像の読み込み
	if ((CursorImg = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//SEの読み込み
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //選択SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(100, MenuSE);

}

Title::~Title()
{
	//フォントの削除
	DeleteFontToHandle(MenuFont);

	//サウンドの削除
	DeleteSoundMem(MenuSE);
}

//更新
AbstractScene* Title::Update()
{
	//十字キー↑入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;

	}

	{
		//入力キー情報
		OldKey = NowKey;
		NowKey = PAD_INPUT::GetLStick().ThumbY;
		KeyFlg = NowKey & ~OldKey;

		//Lスティック上入力
		if (KeyFlg & NowKey / (-20923) < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select--;
			if (Select < 0)Select = 3;
		}

		//Lスティック下入力
		if (KeyFlg & NowKey / 20923 < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select++;
			if (Select > 3)Select = 0;
		}

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//ゲーム画面へ
		case TITLE_MENU::GAME_START:
			return new GameMain();
			break;
			//ランキング画面へ
		case TITLE_MENU::GAME_RANKING:
			return new DrawRanking();
			break;
			//エンド画面へ
		case TITLE_MENU::GAME_END:
			return new End();
			break;
		default:
			break;
		}
	}

	return this;
}

//画像描画
void Title::Draw()const
{
	// ステージの描画
	SetFontSize(64);                             //サイズを64に変更
	SetFontThickness(8);                         //太さを8に変更


	//タイトルの描画
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "りんごおとし", 0xffffff, MenuFont);

	//メニューの描画
	DrawStringToHandle(730, 240, "すたーと", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "らんきんぐ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "へるぷ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "えんど", 0xffffff, MenuFont);

	//カーソルの描画
	int select_y = 240 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}