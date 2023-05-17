#pragma once
#include<string>


#define RANK 5

typedef struct 
{
	int no;
	int score;
}RankingData;

class RANKING
{	

public:
	//コンストラクタ

	static RankingData data[RANK];

	RANKING() = default;

	//ランキングの並べ替え
	static void SortRanking();

	//ランキングデータの保存
	static void SaveRanking();

	struct RANKING_DATA {
		std::string name;
	};

public:

	//ランキングデータの更新
	static void Insert(int score);

	//ランキングデータ読み込み
	static void ReadRanking();

	//ランキングの取得の取得
	static RankingData GetData(int n) { return data[n]; }

	////ランキング名前入力
	//static void WriteRanking(std::string _name, long int _score);

};


