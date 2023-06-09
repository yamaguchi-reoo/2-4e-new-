#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Apple.h"
#include "FpsController.h"

class GameMain :
    public AbstractScene,Apple
{
private:	
    int frame;	    //フレーム

    float a_Count;	//同時にスポーンしているりんごの数
    int SpawnCount;	    //一度にスポーンしたリンゴの計測

    int gGetApple[4];	//どのりんごを何個取ったか集計用
    int gGetAppleType;	//どのりんごを取ったか格納用

    bool CheckSpawn[7];	//各レーンがりんごをスポーン可能か判断する用
    bool SpawnFlg;	    //スポーンできる場所があるかチェック用

    int SpawnPos;       //りんごスポーン用
    int SpawnApple;     //スポーンしていないりんごのオブジェクト探索用

    int TotalScore;         //合計点

    bool PauseFlg;          //一時停止中か判断
    int PauseFlashTime;        //ポーズ中の文字点滅用
    bool PauseFlashFlg;      //ポーズ中の文字点滅用

    int Time;               //制限時間
    int Timer;              //制限時間減少用
    int TimerColor;         //文字色変更用

    Player* player; //プレイヤー
    Apple* apple[MAX_APPLE];   //リンゴ 
    FpsController* fps;

    int ForestImg;      //背景画像
    int gAppleImg[4];	//画像用変数
    int MainBGM;        //BGM
    int StartSE;        //SE
    int AppleSE;        //りんご接触SE
    int PoisonAppleSE;  //毒りんご接触SE
    int MainFont1;      //フォント
    int MainFont2;      //フォント
    int MainFont3;      //フォント

    int GetPsAppleTime; //毒りんごを取ってからの経過時間
    bool GetPsAppleFlg; //毒りんご取得判断用フラグ
    bool PlayerDispFlg; //点滅用フラグ

public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //りんご取得処理
    void AppleGet(int i);

    //りんごスポーン処理
    void AppleSpawn();



};


