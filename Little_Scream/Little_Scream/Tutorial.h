#pragma once
class CheckDevice;
class ControlSound;
class Tutorial
{
private:
	static const int TUTORIAL_KIND = 2;
	int nowTutorialNum;				//現在のチュートリアルのページ
	int tutorialImgKeybord[TUTORIAL_KIND];		//チュートリアル画像　キーボード用
	int tutorialImgController[TUTORIAL_KIND];	//チュートリアル画像　コントローラー用
	int pushButtonTimer;			//長押ししている時間を保存
	bool changeTutorialNum;			//次のページに行くか判別

public:
	Tutorial();
	~Tutorial();
	void checkPushButton(CheckDevice checkDevice, ControlSound& sound);		//チュートリアルを次のページに行かせるための処理

	//ゲッター関数
	int getTutorialImgKeybord(const int i) { return tutorialImgKeybord[i]; }
	int getTutorialImgController(const int i) { return tutorialImgController[i]; }
	int getNowTutorialNum() { return nowTutorialNum; }
	int getPushButtonTimer() { return pushButtonTimer; }

private:
	//定数
	const int MAX_GAUGE = 50;	//ボタン長押し時の最大ゲージ値
	const int FIRST_PAGE = 0;	//１枚目のページ
	const int SECOND_PAGE = 1;	//２枚目のページ

};

