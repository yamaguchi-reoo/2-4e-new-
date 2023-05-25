#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"

InputRankingScene::InputRankingScene(int _score)
{
	score = _score;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	
	//�t�H���g�ǉ�
	NameFont1 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 80, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont2 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 48, 8, DX_FONTTYPE_ANTIALIASING);
	NameFont3 = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 32, 8, DX_FONTTYPE_ANTIALIASING);

	//�摜�Ǎ�
	if ((img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	//SE�Ǎ�
	if ((SelectSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1)
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision01.wav")) == -1)
	{
		throw "Resource/sounds/SE/Decision01.wav";
	}
	//���ʒ���
	ChangeVolumeSoundMem(70, SelectSE);
	ChangeVolumeSoundMem(70, DecisionSE);
}

InputRankingScene::~InputRankingScene()
{
	DeleteFontToHandle(NameFont1);
	DeleteFontToHandle(NameFont2);
	DeleteFontToHandle(NameFont3);

	DeleteSoundMem(SelectSE);
	DeleteSoundMem(DecisionSE);


}

AbstractScene* InputRankingScene::Update()
{
	//�J�[�\������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.y < 0) {
			if (cursorPoint.x == 10) {
				cursorPoint.y = 3;
			}
			else {
				cursorPoint.y = 4;
			}
			if (cursorPoint.x == 12) {
				cursorPoint.x = 11;
			}
		}
	}
	//�J�[�\�������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.y > 3 && cursorPoint.x == 10 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
		if (cursorPoint.y > 3 && cursorPoint.x == 12){
			cursorPoint.x = 11;
		}
	}
	//�J�[�\�����E�ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		if (++cursorPoint.x == 10 && cursorPoint.y > 3)
		{
			cursorPoint.x = 11;
		}
		if (cursorPoint.x > 11 && cursorPoint.y == 4) {
			cursorPoint.x = 0;
		}
		if (cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	//�J�[�\�������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 11;
			}
			else {
				cursorPoint.x = 12;
			}
		}
		if (cursorPoint.x == 10 && cursorPoint.y == 4)
		{
			cursorPoint.x = 9;
		}
	}
	//A�{�^����������Ė��O��9�����ȏ���͂���Ă��Ȃ��Ȃ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && name.size() < NAME_MAX - 1) {
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		if (cursorPoint.x != 11 || cursorPoint.y != 4)
		{
			name += keyboard[cursorPoint.y][cursorPoint.x];
		}
		else if (name.size() > 0)
		{
			//�����L���O���X�V����
			Ranking::Insert(score, const_cast<char*>(name.c_str()));

			//�����L���O��`�悷��
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			return new DrawRanking;
		}
	}
	//B�{�^����������Ė��O��1�����ȏ���͂���Ă���Ȃ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && name.size() > 0) {
		//���O��1��������
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		name.erase(name.begin() + (name.size() - 1));
	}
	//1�����ȏ���͂���Ă���Start�{�^���������ꂽ�Ȃ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)&& name.size() > 0) 
	{
		//�����L���O���X�V����
		Ranking::Insert(score, const_cast<char*>(name.c_str()));

		//�����L���O��`�悷��
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new DrawRanking;
	}
	return this;
}

void InputRankingScene::Draw() const {
	DrawGraph(0, 0, img, TRUE);

	DrawStringToHandle(120, 100, "���O����", 0xffffff, NameFont1);

	DrawBox(470, 240, 820, 300, 0xffffff, TRUE);
	DrawFormatStringToHandle(480, 250, 0x000000, NameFont2, "%s", name.c_str());

	//�m��̃J�[�\�������傫������
	if (cursorPoint.x == 11 && cursorPoint.y == 4)
	{
		DrawBox(308 + 50 * cursorPoint.x, 355 + 50 * cursorPoint.y,
			408 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);
		//�h�m��h�̕����F��ς���
		DrawStringToHandle(858, 555, "�m��", 0x000000,NameFont2);
	}
	else
	{
		DrawBox(308 + 50 * cursorPoint.x, 350 + 50 * cursorPoint.y,
			358 + 50 * cursorPoint.x, 407 + 50 * cursorPoint.y, 0x808080, TRUE);
		//���ʂ̕����F�́h�m��h��`�悷��
		DrawStringToHandle(858, 555, "�m��", 0xffffff, NameFont2);
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == cursorPoint.x && i == cursorPoint.y) {
				DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0x000000, NameFont2, "%c", keyboard[i][j]);
			}
			else
			{
				DrawFormatStringToHandle(j * 50 + 318, i * 50 + 355, 0xffffff, NameFont2, "%c", keyboard[i][j]);
			}
		
		}
	}
	DrawStringToHandle(390, 640, "START�{�^�� or �m��œ��͏I��", 0xffffff, NameFont3);
}
