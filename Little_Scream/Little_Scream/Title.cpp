#include"DxLib.h"
#include"SceneStrage.h"
#include"ConstantStrage.h"
#include"CheckDevice.h"
#include"ControlSound.h"
#include"Title.h"

Title::Title()
{
    select = 0;
    pushFlg = false;
    titleImg = LoadGraph("../img/Title_img.png");
    menuTextImg = LoadGraph("../img/MenuText.png");
}

Title::~Title()
{

}

//�I��������
void Title::selectCommand(int& scene, CheckDevice checkDevice,ControlSound& sound)
{
    //�I���ړ�
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
    //���莞
    if ((CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1)) && pushFlg == false)
    {
        pushFlg = true;
        sound.playSound(decisionSE);
        //�V�[���ړ�
        if (select == playGame)
        {
            scene = playScene;
        }
        else if (select == endGame)
        {
            scene = endScene;
        }
    }
}