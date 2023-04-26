#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE	 10	//�����S�X�|�[�����
#define APPLE_SIZE	100//�����S�̑傫��

class Apple :public BoxCollider
{
private:

	int a_Count;	//�����ɃX�|�[�����Ă����񂲂̐�
	int AppleScore;	//���_��

	int frame;	//�t���[��
	int Count;	//��x�ɃX�|�[�����������S�̌v��

	int gAppleImg[4];

	int CheckSpawn[10];	//��񂲂��d�Ȃ�Ȃ����`�F�b�N����

	struct AppleData {
		int flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float x, y;			//���W
		float rate;			//�傫���i�����蔻��p�j
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
		int span;			//�摜�����Ȃ����p
	};
public:
	//�����L���O�f�[�^�̕ϐ��錾
	struct AppleData	g_Apple[MAX_APPLE] = { FALSE };
private:
	//img�ɉ��ŐF�f�[�^������Ă���
	struct AppleData	g_AppleRd = { TRUE,0,		0,0 ,0, 1.1, 1.0, 100,0};
	struct AppleData	g_AppleBr = { TRUE,1,0x0000ff,0	,0, 1.1, 2.0, 200,0 };
	struct AppleData	g_AppleGr = { TRUE,2,0xffff00,0 ,0, 1.1, 3.5, 500,0 };
	struct AppleData	g_AppleTx = { TRUE,3,0xff00ff,0 ,0, 0.9, 0.5,-750,0 };
	struct AppleData	g_AppleNl = { FALSE,4,	    0,0 ,0, 0  , 0  , 0 };

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

	//��񂲍폜
	void AppleDelete(int i);

	//��񂲓���
	int AppleGet(int i);

	//BoxCollider�Ŏg���p�̔��Ɋi�[����
	void SetLocation(int i);
};




