#pragma once

class Score
{
private:
	int gScore;
	int gAppleImg[2];
	int gAppleCount;


public:
	Score();
	~Score();

	void UpDate();

	void Draw() const;
};
