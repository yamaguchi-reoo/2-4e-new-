#pragma once
#include "AbstractScene.h"
#include"InputRankingScene.h"
#include "Define.h"
#include "Ranking.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int ResultImg;  //リザルト画像
    int ForestImg;  //背景画像
    int WaitTime;   //次のシーンに移るまでの時間
    int ResultBGM;
    int ResultFont1;//フォント用
    int ResultFont2;//フォント用

public:
    //コンストラクタ
    Result();

    //デストラクタ
    ~Result();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    ////シーンの変更処理
    //AbstractScene* ChangeScene()override;
};
