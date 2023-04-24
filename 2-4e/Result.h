#pragma once
#include "AbstractScene.h"
#include "Define.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int Image; //�w�i�摜
    int TotalScore; //���v�X�R�A
    int WaitTime; //���̃V�[���Ɉڂ�܂ł̎���

    int HeadLineFont; //���o���p�̃t�H���g
    int NomalFont; //�ʏ펞�p�̃t�H���g
    int GuideFont; //�{�^���w���p�̃t�H���g

    int DecisionSE; //SE
    int RankingBGM; //BGM
public:
    //�R���X�g���N�^
    Result(int total_score, int* score);

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


