#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int EndImage; //�w�i�摜
    int WaitTime; //�I���܂ł̎���
    int HeadLineFont; //���o���p�̃t�H���g

public:
    //
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


