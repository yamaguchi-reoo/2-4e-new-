#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int ForestImg; //背景画像
	int RankingFont; //見出し用のフォント
	int NomalFont; //通常時用のフォント
	int GuideFont; //ボタン指示用のフォント

	int RankingBGM; //BGM
	int DecisionSE;
public:
	//コンストラクタ
	DrawRanking();

	//デストラクタ
	~DrawRanking();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;
};

