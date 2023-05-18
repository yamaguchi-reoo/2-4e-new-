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

	//�����L���O�̕��בւ�
	static void SortRanking();

	//�����L���O�f�[�^�̕ۑ�
	static void SaveRanking();

public:

	//�����L���O�f�[�^�̍X�V
	static void Insert(int score,char name[10]);

	//�����L���O�f�[�^�ǂݍ���
	static void ReadRanking();

	//�����L���O�̎擾�̎擾
	static RankingData GetData(int n) { return data[n]; }
};


