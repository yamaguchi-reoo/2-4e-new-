#pragma once
#include"define.h"

//中心座標
struct Location
{
	float x;	//中心座標(x)
	float y;	//中心座標(y)
};

//範囲
struct Erea
{
	float height;	//高さ
	float width;	//幅
	float height_rate;	//高さの倍率
	float width_rate;	//幅の倍率 
};

class BoxCollider
{
protected:
	Location location;	//中心座標
	Erea erea; //範囲
public:

	//当たり判定
	int HitBox(BoxCollider* bCollider);

	//中心座標の取得
	Location GetLocation()const;
	//半径の取得
	Erea GetErea()const;

	//中心座標の設定
	void SetLocation(Location location);
};
