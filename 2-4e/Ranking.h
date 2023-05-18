#pragma once

#define RANK 5

struct RankingData
{
	int no;
	int score;
};

class Ranking
{
private:
	static RankingData data[RANK];
private:
	//�R���X�g���N�^
	Ranking() = default;

	static RankingData data[RANK];

	Ranking() = default;

	//�����L���O�̕��בւ�
	static void SortRanking();

	//�����L���O�f�[�^�̕ۑ�
	static void SaveRanking();
public:

	//�����L���O�f�[�^�̍X�V
	static void Insert(int score);

	//�����L���O�f�[�^�ǂݍ���
	static void ReadRanking();

	//�����L���O�̎擾�̎擾
	static RankingData GetData(int n) { return data[n]; }
};


