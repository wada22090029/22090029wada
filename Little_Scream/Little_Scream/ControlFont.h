#pragma once

class ControlFont
{
private:
	static const int FONT_KIND = 2;
	int fontHandle[FONT_KIND];

public:
	ControlFont();
	~ControlFont();

	//ゲッター関数
	int getFontHandle(const int i) { return fontHandle[i]; }
private:
	//定数
	const int MIN_FONT_SIZE = 15;	//最小フォントサイズ
	const int MAX_FONT_SIZE = 40;	//最大フォントサイズ
	const int FONT_THICK = 3;		//厚さ

};

