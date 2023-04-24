#pragma once
#include "BoxCollider.h"

#define PLAYER_SIZE 100
#define WALK_SPEED  5

enum class PLAYER_STATE {
	IDOL = 0,
	WALK_RIGTH,
	WALK_LEFT,

};

class Player :public BoxCollider
{
private:

	PLAYER_STATE PlayerState;	// �v���C���[�̌��݂̏�Ԃ𐧌�

	float Speed;
	int AccelerationRight;	//�����x�i�E�j
	int AccelerationLeft;	//�����x�i���j

private:


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


