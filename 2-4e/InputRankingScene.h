#pragma once
#include "AbstractScene.h"
#include "Ranking.h"
#include "DxLib.h"
#include "PadInput.h"
#include<string>
#include "Result.h"

class InputRankingScene : public AbstractScene
{
private:
	Ranking ranking;

	int img;	//背景画像用
	int score;	//スコア用
	//BGM.SE用
	int InputBGM;
	int SelectSE;	
	int DecisionSE;
	//フォント用変数
	int NameFont1;
	int NameFont2;
	int NameFont3;
	std::string name;	//名前入力用

	POINT cursorPoint;	//カーソルの座標用

	//入力可能文字格納
	const char keyboard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789"};
public:
	//コンストラクタ
	InputRankingScene(int score);
	//デストラクタ
	 ~InputRankingScene();
	//描画以外の更新を実行
	AbstractScene* Update()override;
	//描画に関することを実装
	void Draw()const override;
};

