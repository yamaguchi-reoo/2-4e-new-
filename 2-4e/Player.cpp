#include"Player.h"
#include"PadInput.h"
#include"math.h"
#include"define.h"

Player::Player()
{

	//�����Ńv���C���[�摜��SE�Ǎ�

	//������
	location.x = 100;
	location.y = 550;

	erea.width = PLAYER_WIDTH;
	erea.height = PLAYER_HEIGHT;
	erea.rate = 0.0;

	AccelerationRight = 0;
	AccelerationLeft = 0;

	PlayerState = PLAYER_STATE::IDOL;

	LoadDivGraph("imgaes/147431.png", 10, 2, 5, 50,50,image);

}

Player::~Player()
{

}

void Player::UpDate()
{
	//�ړ�
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		PlayerState = PLAYER_STATE::WALK_LEFT;
		Speed = WALK_SPEED;
		if (AccelerationLeft <= 30) //���ړ����̐���
		{
			AccelerationLeft++;
		}
		if (AccelerationRight > 0)  //�E�ɓ����Ă������̐������E������
		{
			location.x += (AccelerationRight / 10);
			AccelerationRight--;
		}
		location.x = location.x - Speed - (AccelerationLeft / 10);
	}

	else if (PAD_INPUT::GetLStick().ThumbX > 10000)
	{
		PlayerState = PLAYER_STATE::WALK_RIGTH;
		Speed = WALK_SPEED;
		if (AccelerationRight <= 30)	//�E�ړ����̐���
		{
			AccelerationRight++;
		}
		if (AccelerationLeft > 0)		//���ɓ����Ă������̐������E������
		{
			location.x -= (AccelerationLeft / 10);
			AccelerationLeft--;

		}
		location.x = location.x + Speed + (AccelerationRight / 10);
	}
	//�����x�ɉ����Ċ���������
	else
	{
		if (AccelerationRight > 0)
		{
			location.x += (AccelerationRight / 5);
			AccelerationRight -= 1;
			PlayerState = PLAYER_STATE::WALK_RIGTH;
		}
		else if (AccelerationLeft > 0)
		{
			location.x -= (AccelerationLeft / 5);
			AccelerationLeft -= 1;
			PlayerState = PLAYER_STATE::WALK_LEFT;
		}
		else
		{
			PlayerState = PLAYER_STATE::IDOL;
		}
	}
	//�ǂɂԂ���
	if (location.x > 950)
	{
		location.x = 950;
		PlayerState = PLAYER_STATE::IDOL;
		AccelerationRight = 0;
		AccelerationLeft = 0;
	}

	if (location.x < 0)
	{
		location.x = 0;
		PlayerState = PLAYER_STATE::IDOL;
		AccelerationRight = 0;
		AccelerationLeft = 0;
	}
}

void Player::Draw() const
{
	DrawBox(location.x, location.y, location.x + PLAYER_WIDTH, location.y + PLAYER_HEIGHT, 0x00ff00, TRUE);
	DrawFormatString(location.x, location.y,0x000000,"%d",PlayerState);
}
