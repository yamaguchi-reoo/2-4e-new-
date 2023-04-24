#pragma once
#include "AbstractScene.h"

class DrawRanking :
	public AbstractScene
{
private:
	int Image; //�w�i�摜
	int HeadLineFont; //���o���p�̃t�H���g
	int NomalFont; //�ʏ펞�p�̃t�H���g
	int GuideFont; //�{�^���w���p�̃t�H���g

	int RankingBGM; //BGM
	int DecisionSE; //�I��SE
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

