#include"DxLib.h"
#include"ConstantStrage.h"
#include "ControlFont.h"

ControlFont::ControlFont()
{
	//�t�H���g�Z�b�g
	fontHandle[MIN_FONT] =  CreateFontToHandle(NULL, MIN_FONT_SIZE, 3);
	fontHandle[MAX_FONT] = CreateFontToHandle(NULL, MAX_FONT_SIZE, 3);
}

ControlFont::~ControlFont()
{

}