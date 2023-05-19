#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int Image; //背景画像
	int HeadLineFont; //見出し用のフォント
	int NomalFont; //通常時用のフォント
	int GuideFont; //ボタン指示用のフォント

	int RankingBGM; //BGM
	int DecisionSE; //選択SE
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

