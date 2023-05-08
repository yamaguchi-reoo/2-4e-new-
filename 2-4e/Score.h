#pragma once

class Score
{
private:
	int gScore;
	int gAppleImg[2];

public:
	Score();
	~Score();

	void UpDate();

	void Draw() const;
};
