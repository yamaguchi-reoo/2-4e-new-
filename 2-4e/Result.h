#pragma once
#include "AbstractScene.h"
#include "Define.h"

#define WAIT_TIME 360
class Result :
    public AbstractScene
{
private:
    int ForestImg; //�w�i�摜
    int WaitTime; //���̃V�[���Ɉڂ�܂ł̎���
public:
    //�R���X�g���N�^
    Result();

    //�f�X�g���N�^
    ~Result();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
