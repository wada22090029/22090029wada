#include"DxLib.h"
#include"SceneStrage.h"
#include"CheckDevice.h"
#include"ConstantStrage.h"
#include"ControlSound.h"
#include "Result.h"

Result::Result()
{
    select = 0;
    gameOverImg = LoadGraph("../img/game_over_img.png");
    gameClearImg = LoadGraph("../img/game_clear_img.png");
    pushFlg = false;
}

Result::~Result()
{

}

//�I��������
void Result::selectCommand(int& scene, CheckDevice checkDevice,ControlSound& sound)
{
    //�I�����ړ�
    if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S) || (checkDevice.getPadInput() & PAD_INPUT_UP) || (checkDevice.getPadInput() & PAD_INPUT_DOWN))
    {
        if (pushFlg == false)
        {
            select ^= 1;
            pushFlg = true;
            sound.playSound(selectSE);
        }
    }
    else
    {
        //�A�������h�~
        if (CheckHitKey(KEY_INPUT_SPACE) == false && (checkDevice.getPadInput() & PAD_INPUT_1) == false)
        {
            pushFlg = false;
        }
    }
    //����
    if ((CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1)) && pushFlg == false)
    {
        pushFlg = true;
        sound.playSound(decisionSE);
        //�V�[���ړ�
        if (select == retry)
        {
            scene = playScene;
        }
        else if (select == returnTitle)
        {
            scene = titleScene;
        }
    }
}