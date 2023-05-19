#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime;   //終了までの時間
    int MoveString; //エンドロール用
    int ForestImg;  //画像用
    int EndBGM;     //BGM用
    int EndSE;      //SE用
    int EndFont1;
    int EndFont2;
    int EndFont3;


public:
    //コンストラクタ
    End();
    //デストラクタ
    ~End();
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw()const;

    ////シーンの変更処理
    //AbstractScene* ChangeScene()override;
};


