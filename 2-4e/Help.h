#pragma once
#include"AbstractScene.h"
class Help :
    public AbstractScene
{
private:
    int HelpImg;     //�w���v�摜
    int HelpBGM;      //�^�C�g���Ɠ���BGM
    int DecisionSE;    //ketteibotann

public:
    //�R���X�g���N�^
    Help();

    //�f�X�g���N�^
    ~Help();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw()const override;
};
