#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"Help.h"
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

	MenuFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 64, 8, DX_FONTTYPE_ANTIALIASING);

	//タイトル画像の読み込み
	if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	// カーソル画像の読み込み
	if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//BGMの読み込み
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(70, TitleBGM);

	//SEの読み込み
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //選択SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(75, MenuSE);

	//BGMの再生
	if (CheckSoundMem(TitleBGM) == 0)
	{
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK);
	}

}

Title::~Title()
{
	//フォントの削除
	DeleteFontToHandle(MenuFont);

	//サウンドの削除
	DeleteSoundMem(TitleBGM);
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
			//ヘルプ画面
		case TITLE_MENU::GAME_HELP:
			return new Help();
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
	//SetFontThickness(8);                         //太さを8に変更

	//タイトルの描画
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "りんごおとし", 0xffffff, MenuFont);

	//メニューの描画
	DrawStringToHandle(730, 240, "すたーと", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "らんきんぐ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "へるぷ", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "えんど", 0xffffff, MenuFont);

	//カーソルの描画
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}