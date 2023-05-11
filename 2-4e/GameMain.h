#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Apple.h"
#include "FpsController.h"
#include "Score.h"

class GameMain :
    public AbstractScene
{
private:
    int TotalScore;         //合計点
    bool PauseFlg;          //一時停止中か判断
    int GetApple[10];
    int PauseFlash;         //ポーズ中の文字点滅用
    int Time;               //制限時間用
    int TimerColor;         //文字色変更用

    Player* player; //プレイヤー
    Apple* apple;   //リンゴ 
    FpsController* fps;
    Score* score;

    int ForestImg;
    int gAppleImg[2];
    int MainBGM;
    int StartSE;
    int AppleSE;
    int ToxicAppleSE;
    int SEflg;

    int GetTxAppleTime; //毒リンゴを取ってからの経過時間
    bool PlayerDispFlg; //点滅用フラグ

public:
    
    static int getScore;
    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


