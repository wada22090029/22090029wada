#pragma once

class Enemy;
class Player;

class ControlSound
{
private:
	static const int MAX_SOUND_KIND = 9;
	int soundHandle[MAX_SOUND_KIND];

public:
	ControlSound();
	~ControlSound();

	void playSound(const int soundName);		//通常再生
	void playSoundLoop(const int soundName);	//ループ再生
	void stopSound(const int soundName);		//再生停止
	void allSoundStop();						//すべての再生を停止

};

