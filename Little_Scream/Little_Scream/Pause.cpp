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

//初期化
void Pause::initialize()
{
    select = continueGame;
    pushFlg = false;
    pushEscapeKeyFlg = false;
    resetFlg = false;
}

//選択肢処理
void Pause::selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound)
{
    //選択肢移動
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

    //連続押しを防止
    if (CheckHitKey(KEY_INPUT_SPACE) == false && CheckHitKey(KEY_INPUT_W) == false && CheckHitKey(KEY_INPUT_S) == false &&
        (checkDevice.getPadInput() & PAD_INPUT_UP) == false && (checkDevice.getPadInput() & PAD_INPUT_DOWN) == false && (checkDevice.getPadInput() & PAD_INPUT_1) == false && scene == pauseScene)
    {
        pushFlg = false;
    }
    
    //選択を決定
    if ((CheckHitKey(KEY_INPUT_SPACE) || (checkDevice.getPadInput() & PAD_INPUT_1)) && pushFlg == false)
    {
        pushFlg = true;
        sound.playSound(decisionSE);
        //シーン移動
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

//ポーズキーが押されたときの処理
void Pause::controlPauseKey(int& scene, CheckDevice checkDevice,ControlSound& sound)
{
    //ポーズキーが押されたらプレイ画面とポーズ画面を切り替える
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
    //連続押し防止
    if (CheckHitKey(KEY_INPUT_ESCAPE) == false && (checkDevice.getPadInput() & PAD_INPUT_8) == false)
    {
        pushEscapeKeyFlg = false;
    }
}