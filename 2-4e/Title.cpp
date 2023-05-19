#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"Help.h"
#include"End.h"

//�^�C�g�����j���[
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{
	//������
	Select = 0;

	MenuFont = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 64, 8, DX_FONTTYPE_ANTIALIASING);

	//�^�C�g���摜�̓ǂݍ���
	if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	// �J�[�\���摜�̓ǂݍ���
	if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	//BGM�̓ǂݍ���
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	{
		throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(70, TitleBGM);

	//SE�̓ǂݍ���
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //�I��SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(75, MenuSE);

	//BGM�̍Đ�
	if (CheckSoundMem(TitleBGM) == 0)
	{
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK);
	}

}

Title::~Title()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(MenuFont);

	//�T�E���h�̍폜
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
}

//�X�V
AbstractScene* Title::Update()
{
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 3;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 3)Select = 0;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:
			return new GameMain();
			break;
			//�����L���O��ʂ�
		case TITLE_MENU::GAME_RANKING:
			return new DrawRanking();
			break;
			//�w���v���
		case TITLE_MENU::GAME_HELP:
			return new Help();
			break;
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:
			return new End();
			break;
		default:
			break;
		}
	}
	return this;
}

//�摜�`��
void Title::Draw()const
{
	// �X�e�[�W�̕`��
	SetFontSize(64);                             //�T�C�Y��64�ɕύX
	//SetFontThickness(8);                         //������8�ɕύX

	//�^�C�g���̕`��
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "��񂲂��Ƃ�", 0xffffff, MenuFont);

	//���j���[�̕`��
	DrawStringToHandle(730, 240, "�����[��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "��񂫂�", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "�ւ��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "�����", 0xffffff, MenuFont);

	//�J�[�\���̕`��
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}