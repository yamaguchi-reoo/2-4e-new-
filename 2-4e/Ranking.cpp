#include "Ranking.h"
#include "DxLib.h"

#define FILEPATH "Resource/Ranking/Ranking.txt"

RankingData Ranking::data[RANK];

void Ranking::Insert(int score)
{
	ReadRanking();
	if (data[RANK - 1].score < score)
	{
		data[RANK - 1].score = score;
		SortRanking();
		SaveRanking();
	}
}

void Ranking::SortRanking()
{
	RankingData work;	//���ёւ��悤�̕ϐ�

	// �I��@�\�[�g
	for (int i = 0; i < RANK - 1; i++) {
		for (int j = i + 1; j < RANK; j++) {
			if (data[i].score <= data[j].score) {
				work = data[i];
				data[i] = data[j];
				data[j] = work;
			}
		}
	}

	// ���ʕt��
	for (int i = 0; i < RANK; i++) {
		data[i].no = 1;
	}

	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
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

	//�t�@�C���I�[�v��
	if (fopen_s(&fp, FILEPATH, "w") != NULL)
	{
		throw FILEPATH;
	}

	//�����L���O�f�[�^����������
	for (int i = 0; i < RANK; i++) {
		fprintf_s(fp, "%1d %10d\n", data[i].no, data[i].score);
	}

	fclose(fp);
}


void Ranking::ReadRanking(void) {
	FILE* fp = NULL;

	//�t�@�C���I�[�v��
	if (fopen_s(&fp, FILEPATH, "r") != NULL)
	{
		throw FILEPATH;
	}

	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANK; i++) {
		fscanf_s(fp, "%1d %10d", &data[i].no, &data[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}