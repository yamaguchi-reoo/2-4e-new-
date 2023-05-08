#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Credit.h"
#include"End.h"

//�^�C�g�����j���[
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_CREDIT,
	GAME_END
};

Title::Title()
{
	//������
	Select = 0;

	MenuFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�^�C�g���摜�̓ǂݍ���
	if ((mori_img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	// �J�[�\���摜�̓ǂݍ���
	if ((cursor_img = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}


	//BGM�̓ǂݍ���
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, TitleBGM);

	//SE�̓ǂݍ���
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select01.wav")) == -1) //�I��SE
	{
		throw "Resource/sounds/SE/select01.wav";
	}
	if ((StartSE = LoadSoundMem("Resource/sounds/SE/Start.wav")) == -1) //����{�^��
	{
		throw "Resource/sounds/SE/Start.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(100, MenuSE);
	ChangeVolumeSoundMem(200, StartSE);

	//�^�C�g��BGM���X�^�[�g
	//if (CheckSoundMem(TitleBGM) == 0) {
		//PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK, TRUE);
	//}
}

Title::~Title()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(MenuFont);

	//�T�E���h�̍폜
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
	DeleteSoundMem(StartSE);
	DeleteSoundMem(RankingSE);
	DeleteSoundMem(HelpSE);
	DeleteSoundMem(EndSE);
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

	{
		//���̓L�[���
		OldKey = NowKey;
		NowKey = PAD_INPUT::GetLStick().ThumbY;
		KeyFlg = NowKey & ~OldKey;

		//L�X�e�B�b�N�����
		if (KeyFlg & NowKey / (-20923) < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select--;
			if (Select < 0)Select = 3;
		}

		//L�X�e�B�b�N������
		if (KeyFlg & NowKey / 20923 < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select++;
			if (Select > 3)Select = 0;
		}

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		switch (static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:
			//StopSoundMem(TitleBGM);
			return new GameMain();
			break;
			//�����L���O��ʂ�
		case TITLE_MENU::GAME_RANKING:
			//StopSoundMem(TitleBGM);
			return new DrawRanking();
			break;
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:
			//StopSoundMem(TitleBGM);
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
	DrawGraph(0, 0, mori_img, FALSE);

	// �X�e�[�W�̕`��
	SetFontSize(64);                             //�T�C�Y��64�ɕύX
	SetFontThickness(8);                         //������8�ɕύX

	//���j���[�̕`��
	DrawStringToHandle(730, 240, "�����[��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 320, "��񂫂�", 0xffffff, MenuFont);
	DrawStringToHandle(730, 400, "�ւ��", 0xffffff, MenuFont);
	DrawStringToHandle(730, 480, "�����", 0xffffff, MenuFont);

	//�J�[�\���̕`��
	int select_y = 280 + Select * 80;
	DrawGraph(700, select_y, cursor_img, TRUE);
}