#pragma once
#include "BoxCollider.h"
#include "Score.h"

#define MAX_APPLE		 10			//��񂲃X�|�[�����
#define APPLE_SIZE		 85			//��񂲂̑傫��
#define APPLE_DISTANCE	150			//��񂲓��m�̊Ԋu


class Apple :public BoxCollider
{
private:
	int gAppleImg[4];	//�摜�p�ϐ�
	int gAppleColor[4]={0xff0000,0x00ff00,0xffff00,0xdd00dd};	//��񂲐F�f�[�^�i�[�p�ϐ�

	bool Flg;			//�g�p�t���O
	int Type;			//�^�C�v
	int Img;			//�摜
	float Speed;		//�ړ����x
	int Point;			//�X�R�A���Z�|�C���g
	int Time;			//��񂲂��o�����Ă���̌o�ߎ���
	int Span;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

	//�_���擾�G�t�F�N�g�p
	bool eFlg;			//�G�t�F�N�g�\���t���O
	int eType;			//��񂲎��
	int eX;			//��񂲍��W
	float eY;			//��񂲎��
	int eColor;		//�����F
	float eSpeed;		//�ړ����x
	int ePoint;		//���_��
	int eTime;			//�G�t�F�N�g���J�n���Ă���̎���
	int eLimit;		//�G�t�F�N�g��\�����Ă�������

public:

	//�R���X�g���N�^
	Apple();

	//�f�X�g���N�^
	~Apple();

	//�`��ȊO�̍X�V�����s
	void UpDate();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;

	//�X�|�[������
	void Spawn();

	//�X�|�[�������񂲂̎�ޒ��I
	int Rand();

	//�X�|�[�������񂲂�X���W�ݒ�
	void SetLocation(int x);

	//��񂲂����݃X�|�[�������擾
	int GetAppleFlg();

	//��񂲂̎�ގ擾
	int GetAppleType();

	//��񂲂�X���W�擾
	int GetAppleLocationX();

	//��񂲂�Y���W�擾
	float GetAppleLocationY();

	//��񂲂̓_���擾
	int GetApplePoint();

	//��񂲂��X�|�[�����Ă���̌o�ߎ��Ԏ擾
	int GetAppleTime();

	//�e��񂲂̃X�|�[���ҋ@���Ԏ擾
	int GetAppleSpan();

	//��񂲃��Z�b�g
	void AppleReset();

	//�G�t�F�N�g�J�n�p�ݒ�
	void EffectSet();
};




