#include"DxLib.h"
#include"SceneStrage.h"
#include"CheckDevice.h"
#include"ConstantStrage.h"
#include"ControlSound.h"
#include"Pause.h"

Pause::Pause()
{
    select = continueGame;
    pushFlg = false;
    pushEscapeKeyFlg = false;
    resetFlg = false;
    pauseTextImg = LoadGraph("../img/Pause_Text.png");
}

Pause::~Pause()
{

}

//������
void Pause::initialize()
{
    select = continueGame;
    pushFlg = false;
    pushEscapeKeyFlg = false;
    resetFlg = false;
}

//�I��������
void Pause::selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound)
{
    //�I�����ړ�
    if (CheckHitKey(KEY_INPUT_W) || (checkDevice.getPadInput() & PAD_INPUT_UP))
    {
        if (pushFlg == false)
        {
            sound.playSound(selectSE);
            if (select == continueGame)
            {
                select = returnTitle;
            }
            else
            {
                select -= 1;
            }
            pushFlg = true;
        }
    }
    if (CheckHitKey(KEY_INPUT_S) || (checkDevice.getPadInput() & PAD_INPUT_DOWN))
    {
        if (pushFlg == false)
        {
            sound.playSound(selectSE);
            if (select == returnTitle)
            {
                select = continueGame;
            }
            else
            {
                select += 1;
            }
            pushFlg = true;
        }
    }

    //�A��������h�~
    if (CheckHitKey(KEY_INPUT_SPACE) == false && CheckHitKey(KEY_INPUT_W) == false && CheckHitKey(KEY_INPUT_S) == false &&
        (checkDevice.getPadInput() & PAD_INPUT_UP) == false && (checkDevice.getPadInput() & PAD_INPUT_DOWN) == false && (checkDevice.getPadInput() & PAD_INPUT_1) == false && scene == pauseScene)
    {
        pushFlg = false;
    }
    
    //�I��������
    if ((CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1)) && pushFlg == false)
    {
        pushFlg = true;
        sound.playSound(decisionSE);
        //�V�[���ړ�
        if (select == continueGame)
        {
            scene = playScene;
        }
        else if (select == retry)
        {
            resetFlg = true;
            scene = playScene;
        }
        else if (select == returnTitle)
        {
            scene = titleScene;
        }
    }
}

//�|�[�Y�L�[�������ꂽ�Ƃ��̏���
void Pause::controlPauseKey(int& scene, CheckDevice checkDevice,ControlSound& sound)
{
    //�|�[�Y�L�[�������ꂽ��v���C��ʂƃ|�[�Y��ʂ�؂�ւ���
    if ((CheckHitKey(KEY_INPUT_ESCAPE) || (checkDevice.getPadInput() & PAD_INPUT_8)) && pushEscapeKeyFlg == false)
    {
        sound.allSoundStop();
        pushEscapeKeyFlg = true;
        if (scene == playScene)
        {
            scene = pauseScene;
        }
        else if (scene == pauseScene)
        {
            select = continueGame;
            scene = playScene;
        }
    }
    //�A�������h�~
    if (CheckHitKey(KEY_INPUT_ESCAPE) == false && (checkDevice.getPadInput() & PAD_INPUT_8) == false)
    {
        pushEscapeKeyFlg = false;
    }
}