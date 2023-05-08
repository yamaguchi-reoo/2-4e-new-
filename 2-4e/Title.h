#pragma once
#include "AbstractScene.h"

class Title :
    public AbstractScene

{
private:
    int Select;         //選択数
    int TitleImage;     //背景画像
    int OldKey;		//前の入力キー
    int NowKey;		//今の入力キー
    int KeyFlg;		//入力キー情報

    int MenuFont; //メニュー用のフォント

    int TitleBGM;       //BGM
    int MenuSE;         //選択SE
    int StateSE;    //決定音SE
    int RankingSE;
    int HelpSE;
    int EndSE;
    int mori_img;
    int cursor_img;

public:
    //コンストラクタ
    Title();

    //デストラクタ
    ~Title();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


