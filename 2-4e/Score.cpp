#include"DxLib.h"
#include"Score.h"

Score::Score()
{
	gTimeLimit = GetNowCount();
	time = 60000 - (GetNowCount() - gTimeLimit);

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
	delete[] gAppleImg;
}
void Score::UpDate()
{
	if (time >=0)
	{
		time--;
	}
	return;
}
void Score::Draw() const
{
	DrawBox(1000, 0, 1280, 720, 0xffffff, TRUE);
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);

	DrawFormatString(1140, 100, 0x000000, "%2d",time/1000);
}
