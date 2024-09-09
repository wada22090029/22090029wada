#include"DxLib.h"
#include"ConstantStrage.h"
#include "CheckDevice.h"

CheckDevice::CheckDevice()
{
	device = 0;
	padInput = 0;
	padInputR = 0;
	padRightRotateX = 0;
	padRightRotateY = 0;
}

CheckDevice::~CheckDevice()
{

}

//�g�p�f�o�C�X�𒲂ׂ�
void CheckDevice::CheckDeviceNum()
{
	XINPUT_STATE input;		//�R���g���[���[�E�X�e�b�N�ۑ��p

	//�L�[�{�[�h�������ꂽ��f�o�C�X���L�[�{�[�h��
	if (CheckHitKeyAll(DX_CHECKINPUT_KEY))
	{
		device = DEVICE_KEYBORD;
	}
	
	//�R���g���[���[��ݒ�ϐ�
	padInput = GetJoypadInputState(DX_INPUT_PAD1);
	//�R���g���[���[���g�p������f�o�C�X���R���g���[���[��
	if ((padInput & PAD_INPUT_1) || (padInput & PAD_INPUT_2) || (padInput & PAD_INPUT_3) || (padInput & PAD_INPUT_4) || (padInput & PAD_INPUT_5) ||
		(padInput & PAD_INPUT_6) || (padInput & PAD_INPUT_7) || (padInput & PAD_INPUT_8) || (padInput & PAD_INPUT_9) || (padInput & PAD_INPUT_10) ||
		(padInput & PAD_INPUT_UP) || (padInput & PAD_INPUT_DOWN) || (padInput & PAD_INPUT_LEFT) || (padInput & PAD_INPUT_RIGHT))
	{
		device = DEVICE_CONTROLLER;
	}

	//�E�X�e�B�b�N��ݒ�
	padInputR = GetJoypadXInputState(DX_INPUT_PAD1, &input);
	//�E�X�e�B�b�N�𓮂�������f�o�C�X���R���g���[���[�ɂ��Ĉړ��ʂ�ۑ�
	if (input.ThumbRX != 0 || input.ThumbRY != 0)
	{
		device = DEVICE_CONTROLLER;
		padRightRotateX = input.ThumbRX;
		padRightRotateY = input.ThumbRY;
	}
	else
	{
		padRightRotateX = 0;
		padRightRotateY = 0;
	}

}