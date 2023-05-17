#pragma once
#include "AbstractScene.h"
#include "Define.h"
#include "Ranking.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int ResultImg;
    int ForestImg; //背景画像
    int WaitTime; //次のシーンに移るまでの時間
    int ResultFont1;
    int ResultFont2;
public:
    //コンストラクタ
    Result();

    //デストラクタ
    ~Result();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};
