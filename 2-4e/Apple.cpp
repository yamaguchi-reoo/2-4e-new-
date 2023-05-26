#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Apple.h"
#include "define.h"
#include "GameMain.h"

Apple::Apple()
{
	//������
	Flg = FALSE;		//�t���O
	Type = -1;			//�^�C�v(0�͐Ԃ�񂲂Ȃ̂�-1�ɏ�����)
	Img = 0;			//�摜
	location.x = 0;		//x���W
	location.y = 0;		//y���W
	erea.rate = 0;		//�傫���i�����蔻��p�j
	Speed = 0;			//�ړ����x
	Point = 0;			//�X�R�A���Z�|�C���g
	Time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	Span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����

	eFlg = FALSE;				//�G�t�F�N�g�\���t���O
	eType = 0;					//��񂲎��
	eX = 0;					//���X���W�ۑ��p
	eY = 0;					//���Y���W�ۑ��p
	eColor = GetColor(0,0,0);	//�����F
	eSpeed = 0.0;				//�ړ����x
	ePoint = 0;				//�\�����链�_��
	eTime = 0;					//�G�t�F�N�g���J�n���Ă���̌o�ߎ���
	eLimit = 50;				//�G�t�F�N�g��\�����Ă�������

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

Apple::~Apple()
{

}

void Apple::UpDate()
{
	//������񂲂��X�|�[���ςȂ�
	if (Flg == TRUE)
	{
		//�e��񂲂̑��x�̐�����Y���W�����Z����
		location.y += Speed;

		//��񂲂���ʓ��ɂ��鎞�Ԃ��v��
		Time++;
	}	

	//�G�t�F�N�g�`�揈��
	if (eFlg == TRUE)
	{
		//��������ɓ�����
		eY -= eSpeed;
		//�������o�Ă��鎞�Ԃ��v��
		eTime++;
		//��莞�Ԍo������
		if (eTime > eLimit)
		{
			//�G�t�F�N�g������
			eFlg = FALSE;
			//�o�ߎ��ԃ��Z�b�g		
			eTime = 0;					
		}
	}
}
void Apple::Draw() const
{
	//��񂲂̕`��
	if (Flg == TRUE)
	{
		DrawGraph(location.x, location.y,Img, TRUE);
	}

	//�G�t�F�N�g�̕`��
	if (eFlg == TRUE)
	{
		SetFontSize(24);
		//�ԁA�A����񂲎擾�G�t�F�N�g�`��
		if (eType != 3)
		{
			DrawFormatString(eX, eY, eColor, "+%d", ePoint);
		}
		//�ł�񂲎擾�G�t�F�N�g�`��i�������k����j
		else
		{
			DrawFormatString(eX + GetRand(10)-5, eY + GetRand(10)-5 , eColor, "%d", ePoint);
		}
	}
}

void Apple::Spawn()
{
	int GetRand = Rand();			//��񂲎�ޒ��I

	//�ǂ̂�񂲂ł��ς��Ȃ����ڂ͂����ŏ�����
	Flg = TRUE;						//�t���O
	Type = GetRand;					//�^�C�v
	Img = gAppleImg[Type];			//�摜
	location.y = 0;					//y���W
	Time = 0;						//��񂲂��o�����Ă���̌o�ߎ���

	//��񂲂̎�ނɉ�����������
	switch (GetRand)
	{
	case 0:	
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		Speed = 1;						//�ړ����x
		Point = 100;					//�X�R�A���Z�|�C���g
		Span = 100;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����						//��x�ɃX�|�[����������񂲂��v������
		break;
	case 1:
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		Speed = 2;						//�ړ����x
		Point = 200;					//�X�R�A���Z�|�C���g
		Span = 50;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
	case 2:
		erea.rate = 0.1;				//�傫���i�����蔻��p�j
		Speed = 3.5;					//�ړ����x
		Point = 500;					//�X�R�A���Z�|�C���g
		Span = 25;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
	case 3:
		erea.rate = -0.1;				//�傫���i�����蔻��p�j
		Speed = 0.5;					//�ړ����x
		Point = -750;					//�X�R�A���Z�|�C���g
		Span = 200;						//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
		break;
	}
}

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

void Apple::SetLocation(int x)
{
	location.x = x;
}

int Apple::GetAppleFlg()
{
	return Flg;
}

int Apple::GetAppleType()
{
	return Type;
}

int Apple::GetAppleLocationX()
{
	return location.x;
}

int Apple::GetAppleLocationY()
{
	return location.y;
}

int Apple::GetApplePoint()
{
	return Point;
}

int Apple::GetAppleTime()
{
	return Time;
}

int Apple::GetAppleSpan()
{
	return Span;
}

void Apple::AppleReset()
{
	Flg = FALSE;		//�t���O
	Type = -1;			//�^�C�v
	Img = 0;			//�摜
	location.x = 0;		//X���W
	location.y = 0;		//Y���W
	erea.rate = 0;		//�傫���i�����蔻��p�j
	Speed = 0;			//�ړ����x
	Point = 0;			//�X�R�A���Z�|�C���g
	Time = 0;			//��񂲂��o�����Ă���̌o�ߎ���
	Span = 0;			//�e��񂲂����Ȃ��悤�ɂ��邽�߂̑҂�����
}

void Apple::EffectSet()
{
	eFlg = TRUE;				//�t���O�i�G�t�F�N�g�j
	eType = Type;				//�^�C�v�i�G�t�F�N�g�j
	eX = location.x;			//X���W�i�G�t�F�N�g�j				
	eY = location.y;			//Y���W�i�G�t�F�N�g�j		
	eColor = gAppleColor[Type];//�����F�i�G�t�F�N�g�j
	//�ł�񂲈ȊO�Ȃ��񂲂̃X�s�[�h�ɉ��������x�ŕ������i��
	if (Type != 3)				
	{ eSpeed = Speed; }
	//�ł�񂲂Ȃ瑼�̂�񂲂Ƌt�����֕������i��
	else 
	{ eSpeed = -1; }
	ePoint = Point;			//�|�C���g�i�G�t�F�N�g�j	
}