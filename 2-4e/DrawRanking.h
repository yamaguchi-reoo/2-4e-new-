#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int ForestImg; //�w�i�摜
	int RankingFont; //���o���p�̃t�H���g
	int NomalFont; //�ʏ펞�p�̃t�H���g
	int GuideFont; //�{�^���w���p�̃t�H���g

	int RankingBGM; //BGM
	int DecisionSE;
public:
	//�R���X�g���N�^
	DrawRanking();

	//�f�X�g���N�^
	~DrawRanking();

	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};

