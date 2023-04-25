#pragma once
#include"define.h"

//���S���W
struct Location
{
	float x;	//���S���W(x)
	float y;	//���S���W(y)
};

//�͈�
struct Erea
{
	float height;	//����
	float width;	//��
	float height_rate;	//�����̔{��
	float width_rate;	//���̔{�� 
};

class BoxCollider
{
protected:
	Location location;	//���S���W
	Erea erea; //�͈�
public:

	//�����蔻��
	int HitBox(BoxCollider* bCollider);

	//���S���W�̎擾
	Location GetLocation()const;
	//���a�̎擾
	Erea GetErea()const;

	//���S���W�̐ݒ�
	void SetLocation(Location location);
};
