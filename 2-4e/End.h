#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //終了までの時間
    int MoveString; //エンドロール用
    int ForestImg; //画像用
    bool BackTitle; //タイトルへ戻れる仕様を実装するか判断する

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


