#pragma once
#include"ConstantStrage.h"

class ControlFps {
private:
	const int N = 40;	//���ς����T���v����
	const int fps = 40;	//�ݒ肵��FPS

public:
	int mStartTime;      //����J�n����
	int mCount;          //�J�E���^
	float mFps;          //fps
	ControlFps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool upDate();
	void wait();
};

