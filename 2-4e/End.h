#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int EndImage; //背景画像
    int WaitTime; //終了までの時間
    int HeadLineFont; //見出し用のフォント

public:
    //
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


