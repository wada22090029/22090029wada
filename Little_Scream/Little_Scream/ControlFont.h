#pragma once

class ControlFont
{
private:
	static const int FONT_KIND = 2;
	int fontHandle[FONT_KIND];

public:
	ControlFont();
	~ControlFont();

	//�Q�b�^�[�֐�
	int getFontHandle(const int i) { return fontHandle[i]; }
private:
	//�萔
	const int MIN_FONT_SIZE = 15;	//�ŏ��t�H���g�T�C�Y
	const int MAX_FONT_SIZE = 40;	//�ő�t�H���g�T�C�Y
	const int FONT_THICK = 3;		//����

};

