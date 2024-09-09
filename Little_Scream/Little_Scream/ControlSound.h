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

	void playSound(const int soundName);		//’ÊíÄ¶
	void playSoundLoop(const int soundName);	//ƒ‹[ƒvÄ¶
	void stopSound(const int soundName);		//Ä¶’â~
	void allSoundStop();						//‚·‚×‚Ä‚ÌÄ¶‚ğ’â~

};

