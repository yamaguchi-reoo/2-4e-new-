#pragma once
#include "BoxCollider.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100
#define WALK_SPEED  4

enum class PLAYER_STATE {
	IDOL = 0,
	WALK_RIGHT,
	WALK_LEFT,

};

class Player :public BoxCollider
{
private:

	PLAYER_STATE PlayerState;	// �v���C���[�̌��݂̏�Ԃ𐧌�

	int Speed;			//�ړ����x
	int AccelerationRight;	//�����x�i�E�j
	int AccelerationLeft;	//�����x�i���j


private:

	int PlayerWalkImg[9];		//�v���C���[���s�摜�i�[�p
	int Cnt;		//�A�j���[�V�����؂�ւ��p
	int CntWait;	//�A�j���[�V�����؂�ւ��҂����ԑ���p
	int Vector;
	int FrontImg;

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void UpDate();

	//�`��
	void Draw() const;
};


