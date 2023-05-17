#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int Image = 0; //�w�i�摜
	int HeadLineFont = 0; //���o���p�̃t�H���g
	int NomalFont = 0; //�ʏ펞�p�̃t�H���g
	int GuideFont = 0; //�{�^���w���p�̃t�H���g

	int RankingBGM = 0; //BGM
	int DecisionSE = 0; //�I��SE
public:
	DrawRanking();
	//�R���X�g���N�^
	DrawRanking(int score);

	//�f�X�g���N�^
	~DrawRanking();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;
};

