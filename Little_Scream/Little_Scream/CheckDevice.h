#pragma once
class CheckDevice
{
private:
	int device;				//�f�o�C�X�̎��
	int padInput;			//�Q�[���p�b�h����
	int padInputR;			//�Q�[���p�b�h�E�X�e�B�b�N����
	int padRightRotateX;	//�Q�[���p�b�h�E�X�e�B�b�NX���X����
	int padRightRotateY;	//�Q�[���p�b�h�E�X�e�B�b�NY���X����
public:
	CheckDevice();
	~CheckDevice();
	void CheckDeviceNum();		//�g�p�f�o�C�X�𒲂ׂ�

	//�Q�b�^�[�֐�
	int getDevice() { return device; }
	int getPadInput() { return padInput; }
	int getPadRightRotateX() { return padRightRotateX; }
	int getPadRightRotateY() { return padRightRotateY; }
};

