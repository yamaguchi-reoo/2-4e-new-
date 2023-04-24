#pragma once
#include "BoxCollider.h"

#define MAX_APPLE	 10	//�����S�X�|�[�����
#define APPLE_SIZE	100//�����S�̑傫��

class Apple :public BoxCollider
{
private:

	int a_Count;	//�����ɃX�|�[�����Ă����񂲂̐�

	int frame;	//�t���[��
	int Count;	//��x�ɃX�|�[�����������S�̌v��

	int CheckSpawn[10];	//��񂲂��d�Ȃ�Ȃ����`�F�b�N����

	struct AppleData {
		int flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float x, y;			//���W
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
		int span;			//�摜�����Ȃ����p
	};

	//�����L���O�f�[�^�̕ϐ��錾
	struct AppleData	g_Apple[MAX_APPLE] = { FALSE };

	//img�ɉ��ŐF�f�[�^������Ă���
	struct AppleData	g_AppleRd = { TRUE,0,0xff0000,0	 ,0, 1.0,  100,0 };
	struct AppleData	g_AppleBr = { TRUE,0,0x0000ff,0	 ,0, 2.0,  200,0 };
	struct AppleData	g_AppleGr = { TRUE,0,0xffff00,0  ,0, 3.5,  500,0 };
	struct AppleData	g_AppleTx = { TRUE,1,0xff00ff,0  ,0, 0.5, -750,0 };
	struct AppleData	g_AppleNl = { FALSE,0,0,0,0,0,0,0 };

public:
	//�R���X�g���N�^
	Apple();

	//�f�X�g���N�^
	~Apple();

	//�X�V
	void UpDate();

	//�`��
	void Draw() const;

	//��񂲂̃X�|�[��
	void Spawn();

	//��񂲂̃X�|�[���m���p
	int Rand();

	//��񂲂��X�|�[���\�����f
	int AppleSpawn();
};




