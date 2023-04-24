#include"DxLib.h"
#include "FpsController.h"


void FpsController::Init(float RefreshRate, int UpdateTime) {
    frame_time = (int)(1000.0f / RefreshRate); //1�t���[���̎��Ԃ̌v�Z
    update_time = UpdateTime;
    wait_time = 0;
    last_time = now_time = 0;
    count = 0.0f;
    fps = 0.0f;
    last_update = 0;
}
//�҂����Ԃ̌v�Z
void FpsController::Wait() {
    now_time = GetNowCount();
    wait_time = frame_time - (now_time - last_time);
    if (wait_time > 0) { //�҂����Ԃ������
        WaitTimer(wait_time); //�w�莞�ԑ҂�
    }
    last_time = GetNowCount();
}

//FPS�l�̌v�Z
float FpsController::Get() {
    count += 1.0f;
    if (update_time < (last_time - last_update)) { //�A�b�v�f�[�g���ԂɂȂ��Ă����
        fps = count / (float)(last_time - last_update) * 1000.0f; //FPS�l�̌v�Z
        last_update = last_time;
        count = 0.0f;
    }
    return (fps);
}