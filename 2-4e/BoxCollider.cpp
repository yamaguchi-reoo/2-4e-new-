#include "BoxCollider.h"
#include "Apple.h"

int BoxCollider::HitBox(BoxCollider* bCollider)
{
	int ret = false; //�Ԃ�l

		//��񂲂̓����蔻��͈̔�
		float ax1 = location.x - (APPLE_SIZE * erea.rate);
		float ay1 = location.y - (APPLE_SIZE * erea.rate);
		float ax2 = location.x + APPLE_SIZE + (APPLE_SIZE * erea.rate);
		float ay2 = location.y + APPLE_SIZE + (APPLE_SIZE * erea.rate);

		//�v���C���[�̓����蔻��͈̔�
		float px1 = bCollider->GetLocation().x;
		float py1 = bCollider->GetLocation().y;
		float px2 = px1 + bCollider->GetErea().width;
		float py2 = py1 + bCollider->GetErea().height;

		if ((ax1 < px2) && (px1 < ax2) && (ay1 < py2) && (py1 < ay2)) //�����蔻��
		{
			ret = true;
		}
	return ret;
}

Location BoxCollider::GetLocation()const
{
	return location;
}

Erea BoxCollider::GetErea()const
{
	return erea;
}

void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}