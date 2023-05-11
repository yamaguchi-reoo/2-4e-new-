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
    int a_Count;	//�����ɃX�|�[�����Ă����񂲂̐�
    int frame;	    //�t���[��
    int Count;	    //��x�ɃX�|�[�����������S�̌v��

    int gGetApple[4];	//�J�E���g�p�ϐ�
    int CheckSpawn[MAX_APPLE];	//��񂲂��d�Ȃ�Ȃ����`�F�b�N����p

    int TotalScore;         //���v�_
    bool PauseFlg;          //�ꎞ��~�������f
    int PauseFlash;         //�|�[�Y���̕����_�ŗp
    int Time;               //�������ԗp
    int TimerColor;         //�����F�ύX�p

    Player* player; //�v���C���[
    Apple* apple[10];   //�����S 
    FpsController* fps;
    Score* score;

    int ForestImg;
    int gAppleImg[2];
    int MainBGM;
    int StartSE;
    int AppleSE;
    int PoisonAppleSE;
    int SEflg;

    int GetPsAppleTime; //�Ń����S������Ă���̌o�ߎ���
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


