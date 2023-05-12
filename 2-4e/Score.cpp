#include"DxLib.h"
#include"Score.h"

Score::Score() 
{

	//ÇËÇÒÇ≤âÊëúÇÃì«Ç›çûÇ›
	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple red.png")) == -1)
	{
		throw "Resource/Images/apple red.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/BlueApple.png")) == -1)
	{
		throw "Resource/Images/BlueApple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/applegold.png")) == -1)
	{
		throw "Resource/Images/applegold.png";
	}
	if ((gAppleImg[3] = LoadGraph("Resource/Images/applepoison.png")) == -1)
	{
		throw "Resource/Images/applepoison.png";
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
	
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);

}

void Score::Draw(int x, int y) const
{
	DrawBox(x, y, 1280, 720, 0xffffff, TRUE);
}
