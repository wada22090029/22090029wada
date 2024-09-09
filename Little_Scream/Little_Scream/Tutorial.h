#pragma once
class CheckDevice;
class ControlSound;
class Tutorial
{
private:
	static const int TUTORIAL_KIND = 2;
	int nowTutorialNum;				//���݂̃`���[�g���A���̃y�[�W
	int tutorialImgKeybord[TUTORIAL_KIND];		//�`���[�g���A���摜�@�L�[�{�[�h�p
	int tutorialImgController[TUTORIAL_KIND];	//�`���[�g���A���摜�@�R���g���[���[�p
	int pushButtonTimer;			//���������Ă��鎞�Ԃ�ۑ�
	bool changeTutorialNum;			//���̃y�[�W�ɍs��������

public:
	Tutorial();
	~Tutorial();
	void checkPushButton(CheckDevice checkDevice, ControlSound& sound);		//�`���[�g���A�������̃y�[�W�ɍs�����邽�߂̏���

	//�Q�b�^�[�֐�
	int getTutorialImgKeybord(const int i) { return tutorialImgKeybord[i]; }
	int getTutorialImgController(const int i) { return tutorialImgController[i]; }
	int getNowTutorialNum() { return nowTutorialNum; }
	int getPushButtonTimer() { return pushButtonTimer; }

private:
	//�萔
	const int MAX_GAUGE = 50;	//�{�^�����������̍ő�Q�[�W�l
	const int FIRST_PAGE = 0;	//�P���ڂ̃y�[�W
	const int SECOND_PAGE = 1;	//�Q���ڂ̃y�[�W

};

