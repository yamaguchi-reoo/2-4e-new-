#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int Image = 0; //背景画像
	int HeadLineFont = 0; //見出し用のフォント
	int NomalFont = 0; //通常時用のフォント
	int GuideFont = 0; //ボタン指示用のフォント

	int RankingBGM = 0; //BGM
	int DecisionSE = 0; //選択SE
public:
	DrawRanking();
	//コンストラクタ
	DrawRanking(int score);

	//デストラクタ
	~DrawRanking();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;
};

