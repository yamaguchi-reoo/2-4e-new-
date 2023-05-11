#include"Player.h"
#include"PadInput.h"
#include"math.h"
#include"define.h"

Player::Player()
{

	//ここでプレイヤー画像とSE読込

	//初期化
	location.x = 100;
	location.y = 550;

	erea.width = PLAYER_WIDTH;
	erea.height = PLAYER_HEIGHT;
	erea.rate = 0.0;

	AccelerationRight = 0;
	AccelerationLeft = 0;

	cnt = 0;
	cnt_wait = 0;
	

	PlayerState = PLAYER_STATE::IDOL;

	if ((LoadDivGraph("Resource/Images/147431.png", 9, 5, 2, 102, 148, gh)) == -1)
	{
		throw "Resource/Images/147431.png";
	}

	
}

Player::~Player()
{

}

void Player::UpDate()
{
	//移動
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		PlayerState = PLAYER_STATE::WALK_LEFT;
		Speed = WALK_SPEED;
		if (AccelerationLeft <= 30) //左移動時の勢い
		{
			AccelerationLeft++;
		}
		if (AccelerationRight > 0)  //右に動いていた時の勢いを殺す処理
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
		if (AccelerationRight <= 30)	//右移動時の勢い
		{
			AccelerationRight++;
		}
		if (AccelerationLeft > 0)		//左に動いていた時の勢いを殺す処理
		{
			location.x -= (AccelerationLeft / 10);
			AccelerationLeft--;

		}
		location.x = location.x + Speed + (AccelerationRight / 10);
	}
	//加速度に応じて慣性が働く
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
	//壁にぶつかる
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

	//移動する際に画像のcntを増やす
	if (AccelerationLeft >= 5) {
		if (++cnt_wait >= 6) {
			cnt++;
			cnt_wait = 0;
			if (cnt >= 9) {
				cnt = 0;
			}
		}
	}
	else if (AccelerationRight >= 5) {
		{
			if (++cnt_wait >= 6) {
				cnt++;
				cnt_wait = 0;
				if (cnt >= 9) {
					cnt = 0;
				}
			}
		}

	}
}

void Player::Draw() const
{
	//DrawTurnGraph(location.x, location.y, gh[cnt], TRUE);

	if (AccelerationLeft) {
		DrawGraph(location.x, location.y, gh[cnt], TRUE);
	}
	else if(AccelerationRight) {
		DrawTurnGraph(location.x, location.y, gh[cnt], TRUE);
	}
	else {
		DrawTurnGraph(location.x, location.y, gh[cnt], TRUE);
	}
}
