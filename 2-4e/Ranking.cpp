#include "Ranking.h"
#include "DxLib.h"

#define FILEPATH "Resource/Ranking/Ranking.txt"

RankingData Ranking::data[RANK];

void Ranking::Insert(int score,char name[10])
{
	ReadRanking();
	if (data[RANK - 1].score < score)
	{
		data[RANK - 1].score = score;
		//data[].nameを新しい名前に更新したい
		for (int i = 0; i < 10; i++)
		{
			data[RANK - 1].name[i] = name[i];
		}
		SortRanking();
		SaveRanking();
	}
}

void Ranking::SortRanking()
{
	RankingData work;	//並び替え用の変数

	// 選択法ソート
	for (int i = 0; i < RANK - 1; i++) {
		for (int j = i + 1; j < RANK; j++) {
			if (data[i].score <= data[j].score) {
				work = data[i];
				data[i] = data[j];
				data[j] = work;
			}
		}
	}

	// 順位付け
	for (int i = 0; i < RANK; i++) {
		data[i].no = 1;
	}

	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (int i = 0; i < RANK - 1; i++) {
		for (int j = i + 1; j < RANK; j++) {
			if (data[i].score > data[j].score) {
				data[j].no++;
			}
		}
	}
}
void Ranking::SaveRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, FILEPATH, "w") != NULL)
	{
		throw FILEPATH;
	}

	//ランキングデータを書き込む
	for (int i = 0; i < RANK; i++) {
		fprintf_s(fp, "%1d%10d%10s\n", data[i].no, data[i].score, data[i].name);
	}

	fclose(fp);
}


void Ranking::ReadRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, FILEPATH, "r") != NULL)
	{
		throw FILEPATH;
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANK; i++) {
		fscanf_s(fp, "%1d%10d%10s", &data[i].no, &data[i].score,data[i].name,10);
	}

	//ファイルクローズ
	fclose(fp);
}
