#pragma once
#include"ConstantStrage.h"

class ControlFps {
private:
	const int N = 40;	//平均を取るサンプル数
	const int fps = 40;	//設定したFPS

public:
	int mStartTime;      //測定開始時刻
	int mCount;          //カウンタ
	float mFps;          //fps
	ControlFps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool upDate();
	void wait();
};

