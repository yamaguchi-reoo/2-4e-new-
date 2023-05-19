#pragma once
#include "AbstractScene.h"
#include "Ranking.h"
#include "DxLib.h"
#include "PadInput.h"
#include<string>

class InputRankingScene : public AbstractScene
{
private:
	Ranking ranking;
	RankingData RankingData[5];

	int image;
	int score;
	int MenuSE;
	int NameFont1;
	int NameFont2;
	int NameFont3;
	std::string name;

	int img;

	POINT cursorPoint;
	const char keyboard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789" };


public:
	InputRankingScene(int _score);

public:
	void Draw()const override;
	AbstractScene* Update()override;
	AbstractScene* ChangeScene();
};

