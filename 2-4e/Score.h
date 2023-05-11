#pragma once

class Score
{
private:
	int gScore;
	int gAppleImg[4];

public:
	Score();
	~Score();

	void UpDate();

	void Draw() const;
};
