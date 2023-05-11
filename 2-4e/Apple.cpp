#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

//�R���X�g���N�^
Apple::Apple()
{
	//������
	flg = FALSE;
	type = -1;			//�^�C�v
	img = 0;			//�摜
	location.x = 0;		//x���W
	location.y = 0;		//y���W
	erea.rate = 0;		//�傫���i�����蔻��p�j
	speed = 0;			//�ړ����x
	point = 0;			//�X�R�A���Z�|�C���g
	time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

	//��񂲉摜�̓ǂݍ���
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple red.png")) == -1)
	{
		throw "Resource/Images/apple red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/BlueApple.png")) == -1)
	{
		throw "Resource/Images/BlueApple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/applegold.png")) == -1)
	{
		throw "Resource/Images/applegold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/applepoison.png")) == -1)
	{
		throw "Resource/Images/applepoison.png";
	}
}
//�f�X�g���N�^
Apple::~Apple()
{

}

//�X�V
void Apple::UpDate()
{
	//������񂲂��X�|�[���ςȂ�
	if (flg == TRUE)
	{
		//�e��񂲂̑��x�̐�����Y���W�����Z����
		location.y += speed;

		//��񂲂���ʓ��ɂ��鎞�Ԃ��v��
		time += 1;

		//Y��1000�ȏ�Ȃ�폜����
		if (location.y >= 1000)
		{
			AppleDelete();
		}
	}	
}
//�`��
void Apple::Draw() const
{
	if (flg == TRUE)
	{
		DrawGraph(location.x, location.y,img, TRUE);
		//�����蔻��\���p
		DrawBox(location.x - (APPLE_SIZE * erea.rate), location.y - (APPLE_SIZE * erea.rate), location.x + (APPLE_SIZE * erea.rate) + APPLE_SIZE, location.y + (APPLE_SIZE * erea.rate) + APPLE_SIZE, 0x000000, FALSE);
	}
}

//�X�|�[������
void Apple::Spawn()
{
	if (flg == FALSE)
	{
		//��񂲂̎�ނ𒊑I����
		switch (Rand())
		{
			case 0:
				flg = TRUE;
				type = 0;						//�^�C�v
				img = gAppleImg[0];				//�摜
				location.x = GetRand(6)*150;	//x���W
				location.y = 0;					//y���W
				erea.rate = 0.1;					//�傫���i�����蔻��p�j
				speed = 1;						//�ړ����x
				point = 100;						//�X�R�A���Z�|�C���g
				time = 0;						//��񂲂��o�����Ă���̌o�ߎ���
				span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����						//��x�ɃX�|�[����������񂲂��v������
				break;
			case 1:
				flg = TRUE;
				type = 1;						//�^�C�v
				img = gAppleImg[1];				//�摜
				location.x = GetRand(6) * 150;	//x���W
				location.y = 0;					//y���W
				erea.rate = 0.1;					//�傫���i�����蔻��p�j
				speed = 2;						//�ړ����x
				point = 200;						//�X�R�A���Z�|�C���g
				time = 0;						//��񂲂��o�����Ă���̌o�ߎ���
				span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
				break;
			case 2:
				flg = TRUE;
				type = 2;						//�^�C�v
				img = gAppleImg[2];				//�摜
				location.x = GetRand(6) * 150;	//x���W
				location.y = 0;					//y���W
				erea.rate = 0.1;					//�傫���i�����蔻��p�j
				speed = 3.5;						//�ړ����x
				point = 500;						//�X�R�A���Z�|�C���g
				time = 0;						//��񂲂��o�����Ă���̌o�ߎ���
				span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
				break;
			case 3:
				flg = TRUE;
				type = 3;						//�^�C�v
				img = gAppleImg[0];				//�摜
				location.x = GetRand(6) * 150;	//x���W
				location.y = 0;					//y���W
				erea.rate = -0.1;					//�傫���i�����蔻��p�j
				speed = 0.5;						//�ړ����x
				point = -750;						//�X�R�A���Z�|�C���g
				time = 0;						//��񂲂��o�����Ă���̌o�ߎ���
				span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
				break;
		}
	}
}
//�X�|�[�������񂲂̎�ނ̒��I
int Apple::Rand()
{
	int rand = GetRand(19);
	//rand��0�`11�Ȃ�ԐF�i�U�O���j
	if (rand >= 0 && rand <= 11)
	{
		return 0;
	}
	//rand��12�`16�Ȃ�F�i�Q�T���j
	else if (rand > 11 && rand <= 16)
	{
		return 1;
	}
	//rand��17�`18�Ȃ���F�i�P�O���j
	else if (rand > 16 && rand <= 18)
	{
		return 2;
	}
	//rand��19�Ȃ率�F�i�Łj�i�T���j
	else if (rand > 18)
	{
		return 3;
	}
}
//��񂲂̍폜
void Apple::AppleDelete() 
{
	//�擾���ꂽ��񂲂����Z�b�g
	flg = FALSE;
	type = 0;			//�^�C�v
	img = 0;			//�摜
	location.x = 0;
	location.y = 0;			//���W
	erea.rate = 0;			//�傫���i�����蔻��p�j
	speed = 0;			//�ړ����x
	point = 0;			//�X�R�A���Z�|�C���g
	time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
}
//��񂲂̎擾
int Apple::AppleGet()
{
	//�߂�l�i�擾���链�_���j����
	int t = type;
	
	//�擾���ꂽ��񂲂����Z�b�g
	flg = FALSE;
	type = 0;			//�^�C�v
	img = 0;			//�摜
	location.x = 0;
	location.y = 0;			//���W
	erea.rate = 0;			//�傫���i�����蔻��p�j
	speed = 0;		//�ړ����x
	point = 0;			//�X�R�A���Z�|�C���g
	time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

	return t;
}
