#pragma once
#include "AbstractScene.h"
#include "Define.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int Image; //背景画像
    int TotalScore; //合計スコア
    int WaitTime; //次のシーンに移るまでの時間

    int HeadLineFont; //見出し用のフォント
    int NomalFont; //通常時用のフォント
    int GuideFont; //ボタン指示用のフォント

    int DecisionSE; //SE
    int RankingBGM; //BGM
public:
    //コンストラクタ
    Result(int total_score, int* score);

    //デストラクタ
    ~Result();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


