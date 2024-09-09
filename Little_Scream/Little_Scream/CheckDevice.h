#pragma once
class CheckDevice
{
private:
	int device;				//デバイスの種類
	int padInput;			//ゲームパッド入力
	int padInputR;			//ゲームパッド右スティック入力
	int padRightRotateX;	//ゲームパッド右スティックX軸傾き量
	int padRightRotateY;	//ゲームパッド右スティックY軸傾き量
public:
	CheckDevice();
	~CheckDevice();
	void CheckDeviceNum();		//使用デバイスを調べる

	//ゲッター関数
	int getDevice() { return device; }
	int getPadInput() { return padInput; }
	int getPadRightRotateX() { return padRightRotateX; }
	int getPadRightRotateY() { return padRightRotateY; }
};

