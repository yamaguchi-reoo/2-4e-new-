#include "BoxCollider.h"
#include "Apple.h"

//BoxColliderとの当たり判定
int BoxCollider::HitBox(BoxCollider* bCollider)
{
	int ret = false; //返り値

		//自分の当たり判定の範囲
		float mx1 = location.x - (erea.width * erea.width_rate);
		float my1 = location.y - (erea.height * erea.height_rate);
		float mx2 = mx1 + erea.width;
		float my2 = my1 + erea.height;

		//相手の当たり判定の範囲
		float px1 = bCollider->GetLocation().x - (bCollider->GetErea().width * bCollider->GetErea().width_rate);
		float py1 = bCollider->GetLocation().y - (bCollider->GetErea().height * bCollider->GetErea().height_rate);
		float px2 = px1 + bCollider->GetErea().width;
		float py2 = py1 + bCollider->GetErea().height;

		if ((mx1 < px2) && (px1 < mx2) && (my1 < py2) && (py1 < my2)) //当たり判定
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