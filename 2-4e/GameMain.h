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
    int frame;	    //�t���[��
    float Fps;

    float a_Count;	//�����ɃX�|�[�����Ă����񂲂̐�
    int SpawnCount;	    //��x�ɃX�|�[�����������S�̌v��

    int gGetApple[4];	//�ǂ̂�񂲂�����������W�v�p
    int gGetAppleType;	//�ǂ̂�񂲂���������i�[�p

    bool CheckSpawn[7];	//�e���[������񂲂��X�|�[���\�����f����p
    bool SpawnFlg;	    //�X�|�[���ł���ꏊ�����邩�`�F�b�N�p

    int SpawnPos;       //��񂲃X�|�[���p
    int SpawnApple;     //�X�|�[�����Ă��Ȃ���񂲂̃I�u�W�F�N�g�T���p

    int TotalScore;         //���v�_

    bool PauseFlg;          //�ꎞ��~�������f
    int PauseFlashTime;        //�|�[�Y���̕����_�ŗp
    bool PauseFlashFlg;      //�|�[�Y���̕����_�ŗp

    int Time;               //�������ԗp
    int TimerColor;         //�����F�ύX�p

    Player* player; //�v���C���[
    Apple* apple[MAX_APPLE];   //�����S 
    FpsController* fps;

    int ForestImg;      //�w�i�摜
    int gAppleImg[4];	//�摜�p�ϐ�
    int MainBGM;        //BGM
    int StartSE;        //SE
    int AppleSE;        //��񂲐ڐGSE
    int PoisonAppleSE;  //�ł�񂲐ڐGSE
    int MainFont1;      //�t�H���g
    int MainFont2;      //�t�H���g
    int MainFont3;      //�t�H���g

    int GetPsAppleTime; //�ł�񂲂�����Ă���̌o�ߎ���
    bool GetPsAppleFlg; //�ł�񂲎擾���f�p�t���O
    bool PlayerDispFlg; //�_�ŗp�t���O

public:
    static int R_Apple[4];
    static int getScore;
    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //��񂲎擾����
    void AppleGet(int i);

    //��񂲃X�|�[������
    void AppleSpawn();



};


