#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //�I���܂ł̎���

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


