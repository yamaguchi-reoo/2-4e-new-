#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //終了までの時間
    int MoveString; //エンドロール用
    int ForestImg; //画像用

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


