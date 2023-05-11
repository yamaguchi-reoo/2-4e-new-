#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE		 10			//��񂲃X�|�[�����
#define APPLE_SIZE		 85			//��񂲂̑傫��
#define APPLE_RED		 255,0,0	//�Ԃ�񂲂̐F���
#define APPLE_BLUE		 0,255,0	//��񂲂̐F���
#define APPLE_GOLD		 255,255,0  //����񂲂̐F���
#define APPLE_POISON	 255,0,255  //�ł�񂲂̐F���

class Apple :public BoxCollider
{
private:

	int a_Count;	//�����ɃX�|�[�����Ă����񂲂̐�

	int frame;	//�t���[��
	int Count;	//��x�ɃX�|�[�����������S�̌v��


	int gAppleImg[4];	//�摜�p�ϐ�
	int gGetApple[4];	//�J�E���g�p�ϐ�

	int CheckSpawn[MAX_APPLE];	//��񂲂��d�Ȃ�Ȃ����`�F�b�N����p

	struct GetAppleEffect {
		bool flg;		      //���o�t���O
		int type;		      //�擾��񂲎��
		int color;		      //�擾��񂲐F�f�[�^
		int pointeffect;      //���o�p
		int point;            //�_���\���p
		float x, y;			  //���W
	};
	struct AppleData {
		int flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float x, y;			//���W
		float rate;			//�傫���i�����蔻��p�j
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
		int time;			//��񂲂��o�����Ă���̌o�ߎ���
		int span;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
	};
public:
	//�����L���O�f�[�^�̕ϐ��錾
	struct AppleData		g_Apple[MAX_APPLE] = { FALSE };
	struct GetAppleEffect	e_Apple[MAX_APPLE] = { FALSE };
private:
	//img�ɉ��ŐF�f�[�^������Ă���
	struct AppleData	g_AppleRd = { TRUE,0,	    0,10000 ,0,  0.1, 1.0, 100,0, 90};
	struct AppleData	g_AppleBr = { TRUE,1,0x0000ff,10000 ,0,  0.1, 2.0, 200,0, 45};
	struct AppleData	g_AppleGr = { TRUE,2,0xffff00,10000 ,0,  0.1, 3.5, 500,0, 30};
	struct AppleData	g_ApplePs = { TRUE,3,0xff00ff,10000 ,0, -0.1, 0.5,-750,0,180};
	struct AppleData	g_AppleNl = {FALSE,4,	    0,10000 ,0,    0,   0,   0,0,  0};

public:
	//�R���X�g���N�^
	Apple();

	//�f�X�g���N�^
	~Apple();

	//�X�V
	void UpDate();

	//�`��
	void Draw() const;

	//�X�|�[������
	void Spawn();

	//�X�|�[�������񂲂̎�ނ̒��I
	int Rand();

	//�X�|�[������ʒu�̒��I
	int AppleSpawnPos();

	//��񂲂̍폜
	void AppleDelete(int i);

	//��񂲂̎擾
	int AppleGet(int i);

	//�擾������񂲂̎�ނ̔���
	int AppleTypeGet(int i);

	//BoxCollider�ɓn�����l�̐ݒ�
	void SetLocation(int i);
};




