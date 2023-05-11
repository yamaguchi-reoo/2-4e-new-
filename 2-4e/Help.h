#pragma once
#include"AbstractScene.h"
class Help :
    public AbstractScene
{
private:
    int HelpImg;     //ヘルプ画像
    int HelpBGM;      //タイトルと同じBGM
    int HelpSE;    //ketteibotann
    int SEflg;

public:
    //コンストラクタ
    Help();

    //デストラクタ
    ~Help();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw()const override;
};
