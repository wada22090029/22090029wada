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

//チュートリアルを次のページに行かせるための処理
void Tutorial::checkPushButton(CheckDevice checkDevice,ControlSound& sound)
{
	//長押ししている間
	if (CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1))
	{
		//ゲージを増やし続ける
		if (changeTutorialNum == false)
		{
			pushButtonTimer++;
		}
		//マックスを超えたら次のページへ
		if (pushButtonTimer > MAX_GAUGE)
		{
			sound.playSound(decisionSE);
			nowTutorialNum++;
			pushButtonTimer = 0;
			changeTutorialNum = true;
			//メモリ解放
			if (nowTutorialNum > SECOND_PAGE)
			{
				DeleteGraph(tutorialImgKeybord[FIRST_PAGE]);
				DeleteGraph(tutorialImgKeybord[SECOND_PAGE]);
				DeleteGraph(tutorialImgController[FIRST_PAGE]);
				DeleteGraph(tutorialImgController[SECOND_PAGE]);
			}
		}
	}
	//長押しをしないと
	else
	{
		//タイマーをリセット
		pushButtonTimer = 0;
		changeTutorialNum = false;
	}
}