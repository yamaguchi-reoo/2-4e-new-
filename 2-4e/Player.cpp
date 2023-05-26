#include"Player.h"
#include"PadInput.h"
#include"math.h"
#include"define.h"

Player::Player()
{
	//初期化
	location.x = 100;
	location.y = 550;
	Speed = WALK_SPEED;

	erea.width = PLAYER_WIDTH;
	erea.height = PLAYER_HEIGHT;
	erea.rate = 0.0;

	AccelerationRight = 0;
	AccelerationLeft = 0;

	Cnt = 0;
	CntWait = 0;

	Vector = 1;
	
	PlayerState = PLAYER_STATE::IDOL;

	//プレイヤー画像読込
	if ((LoadDivGraph("Resource/Images/147431.png", 9, 5, 2, 102, 148, PlayerWalkImg)) == -1)
	{
		throw "Resource/Images/147431.png";
	}

	if ((FrontImg = LoadGraph("Resource/Images/front.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
}

Player::~Player()
{

}

void Player::UpDate()
{
	//左移動
	if (PAD_INPUT::GetLStick().ThumbX < -10000 || PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		PlayerState = PLAYER_STATE::WALK_LEFT;
		if (AccelerationLeft <= 30) //左移動時の勢い
		{
			AccelerationLeft++;
			Vector = 0;
		}
		if (AccelerationRight > 0)  //右に動いていた時の勢いを殺す処理
		{
			location.x += (AccelerationRight / 10);
			AccelerationRight--;
		}
		location.x = location.x - Speed - (AccelerationLeft / 10);
	}

	//右移動
	else if (PAD_INPUT::GetLStick().ThumbX > 10000 || PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
	{
		PlayerState = PLAYER_STATE::WALK_RIGHT;
		if (AccelerationRight <= 30)	//右移動時の勢い
		{
			AccelerationRight++;
			Vector = 1;
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
			PlayerState = PLAYER_STATE::WALK_RIGHT;
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

	//右の壁にぶつかった時止まる
	if (location.x > 895)
	{
		location.x = 895;
		PlayerState = PLAYER_STATE::IDOL;
		AccelerationRight = 0;
		AccelerationLeft = 0;
	}

	//左の壁にぶつかった時止まる
	if (location.x < 0)
	{
		location.x = 0;
		PlayerState = PLAYER_STATE::IDOL;
		AccelerationRight = 0;
		AccelerationLeft = 0;
	}

	//移動する際に画像のcntを増やす
	if (AccelerationLeft >= 5 || AccelerationRight >= 5) {
		if (++CntWait >= 6) {
			Cnt++;
			CntWait = 0;
			if (Cnt >= 9) {
				Cnt = 0;
			}
		}
	}
}

void Player::Draw() const
{
	switch (PlayerState)
	{
	case PLAYER_STATE::WALK_LEFT:
		DrawGraph(location.x, location.y, PlayerWalkImg[Cnt], TRUE);
		break;
	case PLAYER_STATE::WALK_RIGHT:
		DrawTurnGraph(location.x, location.y, PlayerWalkImg[Cnt], TRUE);
		break;
	case PLAYER_STATE::IDOL:
		DrawRotaGraph(location.x+50, location.y+50, 1.2, 0, FrontImg, TRUE);
		break;
	}
}
