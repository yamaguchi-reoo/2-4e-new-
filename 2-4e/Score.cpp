#include"DxLib.h"
#include"Score.h"

Score::Score() 
{

	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
}
Score::~Score()
{
	
}
void Score::UpDate()

{
	return ;
}
void Score::Draw() const
{
	DrawBox(1000, 0, 1280, 720, 0xffffff, TRUE);
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);

}
