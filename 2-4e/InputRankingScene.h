#pragma once
#include "AbstractScene.h"
#include "Ranking.h"
#include "DxLib.h"
#include "PadInput.h"
#include<string>

class InputRankingScene : public AbstractScene
{
private:
	Ranking ranking;

	int Img;	//�w�i�摜�i�[�p
	int Score;	//�X�R�A�i�[�p
	bool XOnce;	//L�X�e�B�b�N���͏d���h�~�p�i���j
	bool YOnce;	//L�X�e�B�b�N���͏d���h�~�p�i�c�j

	//SE�p
	int SelectSE;	
	int DecisionSE;

	//�t�H���g�p
	int NameFont1;
	int NameFont2;
	int NameFont3;
	std::string Name;	//���O���͗p

	POINT CursorPoint;	//�J�[�\���̍��W�p

	//���͉\�����i�[
	const char KeyBoard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789"};

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

