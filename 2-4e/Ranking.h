#pragma once
#define RANK 5

struct RankingData
{
	int no;
	char name[10];
	int score;
};

class Ranking
{
private:

	static RankingData data[RANK];

	//ランキングの並べ替え
	static void SortRanking();

	//ランキングデータの保存
	static void SaveRanking();

public:

	//ランキングデータの更新
	static void Insert(int score,char name[10]);

	//ランキングデータ読み込み
	static void ReadRanking();

	//ランキングの取得の取得
	static RankingData GetData(int n) { return data[n]; }
};


