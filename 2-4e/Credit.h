#pragma once
#include "AbstractScene.h"
class Credit :
    public AbstractScene
{
private:
    int CreditImage;   //�N���W�b�g�摜
    int CreditBGM;     //BGM
    int DecisionSE;

public:
    Credit();      //�R���X�g���N�^
    ~Credit();

    AbstractScene* Update() override;  //�X�V
    void Draw()const override;    //�摜�`��
};


