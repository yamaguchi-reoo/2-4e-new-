#pragma once
#include "AbstractScene.h"

class Title :
    public AbstractScene

{
private:
    int Select;         //�I��
    int OldKey;		//�O�̓��̓L�[
    int NowKey;		//���̓��̓L�[
    int KeyFlg;		//���̓L�[���

    int MenuFont; //���j���[�p�̃t�H���g

    int TitleBGM;     //BGM
    int MenuSE;       //�I��SE
    int TitleImg;     //�^�C�g���摜
    int CursorImg;    //�J�[�\���摜

public:
    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


