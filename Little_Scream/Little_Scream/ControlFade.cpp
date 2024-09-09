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

//�t�F�[�h�C��
void ControlFade::fadeIn()
{
    fadeCount += FADE_SPEED;

    //�t�F�[�h�؂�ւ�
    if (fadeCount == MAX_FADE)
    {
        fadeFlg = true;
    }
}

//�t�F�[�h�A�E�g
void ControlFade::fadeOut()
{
    fadeCount -= FADE_SPEED;

    //�t�F�[�h�؂�ւ�
    if (fadeCount == 0)
    {
        fadeFlg = false;
    }
}

//�_�ŏ���
void ControlFade::flashingFade()
{
    if (flashFlg == false)
    {
        //���邭����
        flashingFadeCount += FLASH_FADE_SPEED;
        if (flashingFadeCount == MAX_FLASH_FADE)
        {
            flashFlg = true;
        }
    }
    else
    {
        //�Â�����
        flashingFadeCount -= FLASH_FADE_SPEED;
        if (flashingFadeCount == 0)
        {
            flashFlg = false;
        }
    }
}