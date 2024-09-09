#pragma once
class ControlFade
{
private:
	int fadeCount;			//�V�[���ړ����̖��邳
	int flashingFadeCount;	//�_�Ŏ��̖��邳
	bool fadeFlg;			//�Â��Ȃ��Ă��邩
	bool flashFlg;			//�_�ł��Ă��邩
public:
	ControlFade();
	~ControlFade();
	void fadeOut();			//�t�F�[�h�A�E�g
	void fadeIn();			//�t�F�[�h�C��
	void flashingFade();	//�_�ŏ���

	//�Q�b�^�[�֐�
	bool getFadeFlg() { return fadeFlg; }
	int getFadeCount() { return fadeCount; }
	int getFlashingFadeCount() { return flashingFadeCount; }

private:
	//�萔
	const int FADE_SPEED = 5;		//�t�F�[�h�̑��x
	const int MAX_FADE = 255;		//�ő�t�F�[�h�l
	const int FLASH_FADE_SPEED = 10;//�_�ŃX�s�[�h
	const int MAX_FLASH_FADE = 150; //�_�Ŏ��̍ő�t�F�[�h�l
};
