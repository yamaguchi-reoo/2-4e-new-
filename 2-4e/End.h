#pragma once
#include "AbstractScene.h"

class End :
    public AbstractScene
{
private:
    int WaitTime; //I—¹‚Ü‚Å‚ÌŠÔ

public:
    
    End();
    ~End();

    AbstractScene* Update() override;
    void Draw()const;
};


