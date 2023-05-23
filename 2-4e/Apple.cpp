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
	flg = FALSE;		//�t���O
	type = -1;			//�^�C�v(0�͐Ԃ�񂲂Ȃ̂�-1�ɏ�����)
	img = 0;			//�摜
	location.x = 0;		//x���W
	location.y = 0;		//y���W
	erea.rate = 0;		//�傫���i�����蔻��p�j
	speed = 0;			//�ړ����x
	point = 0;			//�X�R�A���Z�|�C���g
	time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

	e_flg = FALSE;				//�G�t�F�N�g�\���t���O
	e_type = 0;					//��񂲎��
	e_x = 0;					//���X���W�ۑ��p
	e_y = 0;					//���Y���W�ۑ��p
	e_color = GetColor(0,0,0);	//�����F
	e_speed = 0.0;				//�ړ����x
	e_point = 0;				//�\�����链�_��
	e_time = 0;					//�G�t�F�N�g���J�n���Ă���̌o�ߎ���
	e_limit = 50;				//�G�t�F�N�g��\�����Ă�������

	//��񂲉摜�̓ǂݍ���
	if ((gAppleImg[0] = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/Apple_Red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/Apple_Blue.png")) == -1)
	{
		throw "Resource/Images/Apple_Blue.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/Apple_Gold.png")) == -1)
	{
		throw "Resource/Images/Apple_Gold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/Apple_Poison.png")) == -1)
	{
		throw "Resource/Images/Apple_Poison.png";
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
		time++;
	}	

	//�G�t�F�N�g�`�揈��
	if (e_flg == TRUE)
	{
		//��������ɓ�����
		e_y -= e_speed;
		//�������o�Ă��鎞�Ԃ��v��
		e_time++;
		//��莞�Ԍo������
		if (e_time > e_limit)
		{
			//�G�t�F�N�g������
			e_flg = FALSE;
			//�o�ߎ��ԃ��Z�b�g		
			e_time = 0;					
		}
	}
}
//�`��
void Apple::Draw() const
{
	//��񂲂̕`��
	if (flg == TRUE)
	{
		DrawGraph(location.x, location.y,img, TRUE);
	}

	//�G�t�F�N�g�̕`��
	if (e_flg == TRUE)
	{
		SetFontSize(24);
		//�ԁA�A����񂲎擾�G�t�F�N�g�`��
		if (e_type != 3)
		{
			DrawFormatString(e_x, e_y, e_color, "+%d", e_point);
		}
		//�ł�񂲎擾�G�t�F�N�g�`��i�������k����j
		else
		{
			DrawFormatString(e_x + GetRand(10)-5, e_y + GetRand(10)-5 , e_color, "%d", e_point);
		}
	}
}

//�X�|�[������
void Apple::Spawn()
{
	int GetRand = Rand();			//��񂲎�ޒ��I

	//�ǂ̂�񂲂ł��ς��Ȃ����ڂ͂����ŏ�����
	flg = TRUE;						//�t���O
	type = GetRand;					//�^�C�v
	img = gAppleImg[type];			//�摜
	location.y = 0;					//y���W
	time = 0;						//��񂲂��o�����Ă���̌o�ߎ���

	//��񂲂̎�ނɉ�����������
	switch (GetRand)
	{
	case 0:	
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		speed = 1;						//�ړ����x
		point = 100;					//�X�R�A���Z�|�C���g
		span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����						//��x�ɃX�|�[����������񂲂��v������
		break;
	case 1:
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		speed = 2;						//�ړ����x
		point = 200;					//�X�R�A���Z�|�C���g
		span = 50;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
	case 2:
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		speed = 3.5;					//�ړ����x
		point = 500;					//�X�R�A���Z�|�C���g
		span = 25;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
	case 3:
		erea.rate = -0.1;				//�傫���i�����蔻��p�j
		speed = 0.5;					//�ړ����x
		point = -750;					//�X�R�A���Z�|�C���g
		span = 200;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
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
	else if (rand >= 12 && rand <= 16)
	{
		return 1;
	}
	//rand��17�`18�Ȃ���F�i�P�O���j
	else if (rand >= 17 && rand <= 18)
	{
		return 2;
	}
	//rand��19�Ȃ率�F�i�Łj�i�T���j
	else if (rand == 19)
	{
		return 3;
	}
}

//��񂲂�X���W�ݒ�
void Apple::SetLocation(int x)
{
	location.x = x;
}

//��񂲂����݃X�|�[�������擾
int Apple::GetAppleFlg()
{
	return flg;
}

//��񂲂̎�ގ擾
int Apple::GetAppleType()
{
	return type;
}

//��񂲂�X���W�擾
int Apple::GetAppleLocationX()
{
	return location.x;
}

//��񂲂�Y���W�擾
int Apple::GetAppleLocationY()
{
	return location.y;
}

//��񂲂̓_���擾
int Apple::GetApplePoint()
{
	return point;
}

//��񂲂��X�|�[�����Ă���̌o�ߎ��Ԏ擾
int Apple::GetAppleTime()
{
	return time;
}

//�e��񂲂̃X�|�[���ҋ@���Ԏ擾
int Apple::GetAppleSpan()
{
	return span;
}

//��񂲃��Z�b�g
void Apple::AppleReset()
{
	flg = FALSE;		//�t���O
	type = -1;			//�^�C�v
	img = 0;			//�摜
	location.x = 0;		//X���W
	location.y = 0;		//Y���W
	erea.rate = 0;		//�傫���i�����蔻��p�j
	speed = 0;			//�ړ����x
	point = 0;			//�X�R�A���Z�|�C���g
	time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
}

//�G�t�F�N�g�J�n�p�ݒ�
void Apple::EffectSet()
{
	e_flg = TRUE;				//�t���O�i�G�t�F�N�g�j
	e_type = type;				//�^�C�v�i�G�t�F�N�g�j
	e_x = location.x;			//X���W�i�G�t�F�N�g�j				
	e_y = location.y;			//Y���W�i�G�t�F�N�g�j		
	e_color = gAppleColor[type];//�����F�i�G�t�F�N�g�j
	//�ł�񂲈ȊO�Ȃ��񂲂̃X�s�[�h�ɉ��������x�ŕ������i��
	if (type != 3)				
	{ e_speed = speed; }
	//�ł�񂲂Ȃ瑼�̂�񂲂Ƌt�����֕������i��
	else 
	{ e_speed = -1; }
	e_point = point;			//�|�C���g�i�G�t�F�N�g�j	
}