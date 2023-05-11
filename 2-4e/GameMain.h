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
    int TotalScore;         //���v�_
    bool PauseFlg;          //�ꎞ��~�������f
    int GetApple[10];
    int PauseFlash;         //�|�[�Y���̕����_�ŗp
    int Time;               //�������ԗp
    int TimerColor;         //�����F�ύX�p

    Player* player; //�v���C���[
    Apple* apple;   //�����S 
    FpsController* fps;
    Score* score;

    int ForestImg;
    int gAppleImg[2];
    int MainBGM;
    int StartSE;
    int AppleSE;
    int ToxicAppleSE;
    int SEflg;

    int GetTxAppleTime; //�Ń����S������Ă���̌o�ߎ���
    bool PlayerDispFlg; //�_�ŗp�t���O

public:
    
    static int getScore;
    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


