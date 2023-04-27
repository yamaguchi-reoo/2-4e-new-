#include "BoxCollider.h"
#include "Apple.h"

//BoxColliderとの当たり判定
int BoxCollider::HitBox(BoxCollider* bCollider)
{
	int ret = false; //返り値

		//りんごの当たり判定の範囲
		float ax1 = location.x - (APPLE_SIZE * erea.rate);
		float ay1 = location.y - (APPLE_SIZE * erea.rate);
		float ax2 = ax1 + APPLE_SIZE;
		float ay2 = ay1 + APPLE_SIZE;

		//プレイヤーの当たり判定の範囲
		float px1 = bCollider->GetLocation().x;
		float py1 = bCollider->GetLocation().y;
		float px2 = px1 + bCollider->GetErea().width;
		float py2 = py1 + bCollider->GetErea().height;

		if ((ax1 < px2) && (px1 < ax2) && (ay1 < py2) && (py1 < ay2)) //当たり判定
		{
			ret = true;
		}
	return ret;
}

//中心座標の取得
Location BoxCollider::GetLocation()const
{
	return location;
}

//半径の取得
Erea BoxCollider::GetErea()const
{
	return erea;
}

//中心座標の設定
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}

void BoxCollider::Draw() const
{
	
}