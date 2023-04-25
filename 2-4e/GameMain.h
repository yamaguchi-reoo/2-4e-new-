#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Apple.h"
#include "FpsController.h"
#include"Score.h"

class GameMain :
    public AbstractScene
{
private:
    int TotalScore;
    int GetApple[10];

    Player* player; //プレイヤー
    Apple* apple;   //リンゴ 
    FpsController* fps;
    Score* score;

    int mori_img;
    int gAppleImg[2];

public:
    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


