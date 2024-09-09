#pragma once
class ControlFade
{
private:
	int fadeCount;			//シーン移動時の明るさ
	int flashingFadeCount;	//点滅時の明るさ
	bool fadeFlg;			//暗くなっているか
	bool flashFlg;			//点滅しているか
public:
	ControlFade();
	~ControlFade();
	void fadeOut();			//フェードアウト
	void fadeIn();			//フェードイン
	void flashingFade();	//点滅処理

	//ゲッター関数
	bool getFadeFlg() { return fadeFlg; }
	int getFadeCount() { return fadeCount; }
	int getFlashingFadeCount() { return flashingFadeCount; }

private:
	//定数
	const int FADE_SPEED = 5;		//フェードの速度
	const int MAX_FADE = 255;		//最大フェード値
	const int FLASH_FADE_SPEED = 10;//点滅スピード
	const int MAX_FLASH_FADE = 150; //点滅時の最大フェード値
};
