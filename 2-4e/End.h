#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //�I���܂ł̎���
    int MoveString; //�G���h���[���p
    int ForestImg; //�摜�p
    bool BackTitle; //�^�C�g���֖߂��d�l���������邩���f����

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


