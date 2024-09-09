#include"DxLib.h"
#include"ConstantStrage.h"
#include"CheckDevice.h"
#include"ControlSound.h"
#include"Tutorial.h"

Tutorial::Tutorial()
{
	nowTutorialNum = 0;
	tutorialImgKeybord[FIRST_PAGE] = LoadGraph("../img/Tutorial_img.png");
	tutorialImgKeybord[SECOND_PAGE] = LoadGraph("../img/Tutorial_img2_Keybord.png");
	tutorialImgController[FIRST_PAGE] = LoadGraph("../img/Tutorial_img.png");
	tutorialImgController[SECOND_PAGE] = LoadGraph("../img/Tutorial_img2_Controller.png");
	pushButtonTimer = 0;
	changeTutorialNum = false;
}

Tutorial::~Tutorial()
{

}

//�`���[�g���A�������̃y�[�W�ɍs�����邽�߂̏���
void Tutorial::checkPushButton(CheckDevice checkDevice,ControlSound& sound)
{
	//���������Ă����
	if (CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1))
	{
		//�Q�[�W�𑝂₵������
		if (changeTutorialNum == false)
		{
			pushButtonTimer++;
		}
		//�}�b�N�X�𒴂����玟�̃y�[�W��
		if (pushButtonTimer > MAX_GAUGE)
		{
			sound.playSound(decisionSE);
			nowTutorialNum++;
			pushButtonTimer = 0;
			changeTutorialNum = true;
			//���������
			if (nowTutorialNum > SECOND_PAGE)
			{
				DeleteGraph(tutorialImgKeybord[FIRST_PAGE]);
				DeleteGraph(tutorialImgKeybord[SECOND_PAGE]);
				DeleteGraph(tutorialImgController[FIRST_PAGE]);
				DeleteGraph(tutorialImgController[SECOND_PAGE]);
			}
		}
	}
	//�����������Ȃ���
	else
	{
		//�^�C�}�[�����Z�b�g
		pushButtonTimer = 0;
		changeTutorialNum = false;
	}
}