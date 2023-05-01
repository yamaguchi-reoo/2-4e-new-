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
    int TotalScore;  //���v�_
    bool PauseFlg;   //�ꎞ��~�������f
    int GetApple[10];
    int PauseFlash; //�|�[�Y���̕����_�ŗp

    Player* player; //�v���C���[
    Apple* apple;   //�����S 
    FpsController* fps;
    Score* score;

    int mori_img;
    int gAppleImg[2];

public:
    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


