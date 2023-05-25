#pragma once
#include "AbstractScene.h"
#include "Ranking.h"
#include "DxLib.h"
#include "PadInput.h"
#include<string>
#include "Result.h"

class InputRankingScene : public AbstractScene
{
private:
	Ranking ranking;

	int img;	//�w�i�摜�p
	int score;	//�X�R�A�p
	//BGM.SE�p
	int InputBGM;
	int SelectSE;	
	int DecisionSE;
	//�t�H���g�p�ϐ�
	int NameFont1;
	int NameFont2;
	int NameFont3;
	std::string name;	//���O���͗p

	POINT cursorPoint;	//�J�[�\���̍��W�p

	//���͉\�����i�[
	const char keyboard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789"};
public:
	//�R���X�g���N�^
	InputRankingScene(int score);
	//�f�X�g���N�^
	 ~InputRankingScene();
	//�`��ȊO�̍X�V�����s
	AbstractScene* Update()override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const override;
};

