#pragma once
#include "AbstractScene.h"
#include"InputRankingScene.h"
#include "Define.h"
#include "Ranking.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int ResultImg;  //���U���g�摜
    int ForestImg;  //�w�i�摜
    int WaitTime;   //���̃V�[���Ɉڂ�܂ł̎���
    int ResultBGM;
    int ResultFont1;//�t�H���g�p
    int ResultFont2;//�t�H���g�p

public:
    //�R���X�g���N�^
    Result();

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    ////�V�[���̕ύX����
    //AbstractScene* ChangeScene()override;
};
