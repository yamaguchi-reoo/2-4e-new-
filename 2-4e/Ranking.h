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
	//�R���X�g���N�^

	static RankingData data[RANK];

	RANKING() = default;

	//�����L���O�̕��בւ�
	static void SortRanking();

	//�����L���O�f�[�^�̕ۑ�
	static void SaveRanking();

	struct RANKING_DATA {
		std::string name;
	};

public:

	//�����L���O�f�[�^�̍X�V
	static void Insert(int score);

	//�����L���O�f�[�^�ǂݍ���
	static void ReadRanking();

	//�����L���O�̎擾�̎擾
	static RankingData GetData(int n) { return data[n]; }

	////�����L���O���O����
	//static void WriteRanking(std::string _name, long int _score);

};


