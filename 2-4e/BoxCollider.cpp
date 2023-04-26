#include "BoxCollider.h"
#include "Apple.h"

//BoxCollider�Ƃ̓����蔻��
int BoxCollider::HitBox(BoxCollider* bCollider)
{
	int ret = false; //�Ԃ�l

		//�����̓����蔻��͈̔�
		float mx1 = location.x - (APPLE_SIZE * erea.rate);
		float my1 = location.y - (APPLE_SIZE * erea.rate);
		float mx2 = mx1 + APPLE_SIZE;
		float my2 = my1 + APPLE_SIZE;

		//����̓����蔻��͈̔�
		float px1 = bCollider->GetLocation().x - (bCollider->GetErea().width * bCollider->GetErea().rate);
		float py1 = bCollider->GetLocation().y - (bCollider->GetErea().height * bCollider->GetErea().rate);
		float px2 = px1 + bCollider->GetErea().width;
		float py2 = py1 + bCollider->GetErea().height;

		if ((mx1 < px2) && (px1 < mx2) && (my1 < py2) && (py1 < my2)) //�����蔻��
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