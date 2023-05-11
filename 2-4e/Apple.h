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
	int gAppleImg[4];	//�摜�p�ϐ�

		int flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
		int time;			//��񂲂��o�����Ă���̌o�ߎ���
		int span;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
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

	//��񂲂̍폜
	void AppleDelete();

	//��񂲂̎擾
	int AppleGet();
};




