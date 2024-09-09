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

//使用デバイスを調べる
void CheckDevice::CheckDeviceNum()
{
	XINPUT_STATE input;		//コントローラー右ステック保存用

	//キーボードが押されたらデバイスをキーボードに
	if (CheckHitKeyAll(DX_CHECKINPUT_KEY))
	{
		device = DEVICE_KEYBORD;
	}
	
	//コントローラーを設定変数
	padInput = GetJoypadInputState(DX_INPUT_PAD1);
	//コントローラーを使用したらデバイスをコントローラーに
	if ((padInput & PAD_INPUT_1) || (padInput & PAD_INPUT_2) || (padInput & PAD_INPUT_3) || (padInput & PAD_INPUT_4) || (padInput & PAD_INPUT_5) ||
		(padInput & PAD_INPUT_6) || (padInput & PAD_INPUT_7) || (padInput & PAD_INPUT_8) || (padInput & PAD_INPUT_9) || (padInput & PAD_INPUT_10) ||
		(padInput & PAD_INPUT_UP) || (padInput & PAD_INPUT_DOWN) || (padInput & PAD_INPUT_LEFT) || (padInput & PAD_INPUT_RIGHT))
	{
		device = DEVICE_CONTROLLER;
	}

	//右スティックを設定
	padInputR = GetJoypadXInputState(DX_INPUT_PAD1, &input);
	//右スティックを動かしたらデバイスをコントローラーにして移動量を保存
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