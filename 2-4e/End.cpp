#pragma once
#include"DxLib.h"
#include"PadInput.h"
#include"End.h"

#define TIME_LIMIT 300
#define MOVE_SPEED 7

End::End() {
	//‰Šú‰»
	WaitTime = TIME_LIMIT;
	MoveString = 0;

	//ƒtƒHƒ“ƒg‚Ì’Ç‰Á
	EndFont1 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 70, 8, DX_FONTTYPE_ANTIALIASING);
	EndFont2 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 50, 8, DX_FONTTYPE_ANTIALIASING);
	EndFont3 = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 90, 8, DX_FONTTYPE_ANTIALIASING);

	if ((ForestImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//BGM‚Ì“Ç‚İ‚İ
	if ((EndBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM‚Ì‰¹—Ê•ÏX
	ChangeVolumeSoundMem(70, EndBGM);

	//SE‚Ì“Ç‚İ‚İ
	if ((EndSE = LoadSoundMem("Resource/sounds/SE/Shortbridge03-2.wav")) == -1)
	{
		throw "Resource/sounds/SE/End.wav";
	}
	//SE‚Ì‰¹—Ê•ÏX
	ChangeVolumeSoundMem(70, EndSE);

	//BGM‚ÌÄ¶
	if (CheckSoundMem(EndBGM) == 0)
	{
		PlaySoundMem(EndBGM, DX_PLAYTYPE_BACK);
	}
	//‰æ–ÊØ‘ÖSE
	if (CheckSoundMem(EndSE) == 0)
	{
		PlaySoundMem(EndSE, DX_PLAYTYPE_BACK);
	}

}

End::~End()
{
	DeleteFontToHandle(EndFont1);
	DeleteFontToHandle(EndFont2);
	DeleteFontToHandle(EndFont3);
	//ƒTƒEƒ“ƒh‚Ìíœ
	DeleteSoundMem(EndBGM);
	DeleteSoundMem(EndSE);
}

AbstractScene* End::Update() {
	if (WaitTime-- < 0) {
		return nullptr;
	}
	if (++MoveString >= 200) { 
		MoveString = 200; 
	}
	return this;
}

void End::Draw()const {
	//ƒQ[ƒ€I—¹‰æ–Ê
	DrawGraph(0, 0, ForestImg, TRUE);
	DrawStringToHandle(500, 680 - MoveString * MOVE_SPEED, "SE & BGM", 0x0000ff,EndFont1);

	DrawStringToHandle(540, 780 - MoveString * MOVE_SPEED, "OtoLogic", 0x000000, EndFont2);
	DrawStringToHandle(515, 840 - MoveString * MOVE_SPEED, "–³—¿Œø‰Ê‰¹", 0x000000, EndFont2);
	DrawStringToHandle(470, 900 - MoveString * MOVE_SPEED, "ŠÃ’ƒ‚Ì‰¹ŠyH–[", 0x000000,EndFont2);

	DrawStringToHandle(505, 1050 - MoveString * MOVE_SPEED, "‰æ‘œ‘fŞ", 0xff0000, EndFont1);

	DrawStringToHandle(510, 1150 - MoveString * MOVE_SPEED, "ƒCƒ‰ƒXƒg‰®", 0x000000, EndFont2);
	DrawStringToHandle(545, 1210 - MoveString * MOVE_SPEED, "illustAC", 0x000000, EndFont2);
	DrawStringToHandle(560, 1270 - MoveString * MOVE_SPEED, "illust8", 0x000000, EndFont2);
	DrawStringToHandle(545, 1330 - MoveString * MOVE_SPEED, "SVG Silh", 0x000000, EndFont2);

	DrawStringToHandle(340, 2000 - MoveString * (MOVE_SPEED+1.5), "Thank You For ", 0x000000, EndFont3);
	DrawStringToHandle(310, 2100 - MoveString * (MOVE_SPEED+1.5), "Playing Game !!", 0x000000, EndFont3);
}