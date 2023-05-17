#include"DxLib.h"
#include"Define.h"
#include"SceneManager.h"
#include"FpsController.h"
#include"Title.h"
#include"PadInput.h"
#include"GameMain.h"


#define FRAMERATE 60.0 //�t���[�����[�g

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("��񂲂��Ƃ�");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new Title());

	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}
	FpsController FPSC(FRAMERATE, 800);

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();
		sceneMng->Draw();
		FPSC.All();

		//�����I��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
		{
			break;
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	return 0;
}