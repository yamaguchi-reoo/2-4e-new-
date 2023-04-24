#pragma once
#include "AbstractScene.h"
class Credit :
    public AbstractScene
{
private:
    int CreditImage;   //クレジット画像
    int CreditBGM;     //BGM
    int DecisionSE;

public:
    Credit();      //コンストラクタ
    ~Credit();

    AbstractScene* Update() override;  //更新
    void Draw()const override;    //画像描画
};


