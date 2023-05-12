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

		bool flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
		int time;			//��񂲂��o�����Ă���̌o�ߎ���
		int span;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

		//�_���擾�G�t�F�N�g�p
		bool e_flg;			//�G�t�F�N�g�\���t���O
		int e_type;			//
		int e_point;
		int e_time;
		int e_limit;
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
	int GetAppleLocationY();

	//��񂲂̓_���擾
	int GetApplePoint();

	//��񂲂��X�|�[�����Ă���̌o�ߎ��Ԏ擾
	int GetAppleTime();

	//�e��񂲂̃X�|�[���ҋ@���Ԏ擾
	int GetAppleSpan();

	//��񂲃��Z�b�g
	void AppleReset();
};




