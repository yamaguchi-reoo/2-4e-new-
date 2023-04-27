#include "BoxCollider.h"
#include "Apple.h"

//BoxCollider�Ƃ̓����蔻��
int BoxCollider::HitBox(BoxCollider* bCollider)
{
	int ret = false; //�Ԃ�l

		//��񂲂̓����蔻��͈̔�
		float ax1 = location.x - (APPLE_SIZE * erea.rate);
		float ay1 = location.y - (APPLE_SIZE * erea.rate);
		float ax2 = ax1 + APPLE_SIZE;
		float ay2 = ay1 + APPLE_SIZE;

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

//���S���W�̎擾
Location BoxCollider::GetLocation()const
{
	return location;
}

//���a�̎擾
Erea BoxCollider::GetErea()const
{
	return erea;
}

//���S���W�̐ݒ�
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}

void BoxCollider::Draw() const
{
	
}