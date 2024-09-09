#include"DxLib.h"
#include "ControlFade.h"

ControlFade::ControlFade()
{
    fadeCount = 0;
    flashingFadeCount = 0;
    fadeFlg = false;
    flashFlg = false;
}

ControlFade::~ControlFade()
{

}

//フェードイン
void ControlFade::fadeIn()
{
    fadeCount += FADE_SPEED;

    //フェード切り替え
    if (fadeCount == MAX_FADE)
    {
        fadeFlg = true;
    }
}

//フェードアウト
void ControlFade::fadeOut()
{
    fadeCount -= FADE_SPEED;

    //フェード切り替え
    if (fadeCount == 0)
    {
        fadeFlg = false;
    }
}

//点滅処理
void ControlFade::flashingFade()
{
    if (flashFlg == false)
    {
        //明るくする
        flashingFadeCount += FLASH_FADE_SPEED;
        if (flashingFadeCount == MAX_FLASH_FADE)
        {
            flashFlg = true;
        }
    }
    else
    {
        //暗くする
        flashingFadeCount -= FLASH_FADE_SPEED;
        if (flashingFadeCount == 0)
        {
            flashFlg = false;
        }
    }
}