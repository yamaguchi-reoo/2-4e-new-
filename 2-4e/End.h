#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //�I���܂ł̎���
    int MoveString; //�G���h���[���p
    int ForestImg; //�摜�p

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


