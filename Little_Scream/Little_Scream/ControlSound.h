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

	void playSound(const int soundName);		//�ʏ�Đ�
	void playSoundLoop(const int soundName);	//���[�v�Đ�
	void stopSound(const int soundName);		//�Đ���~
	void allSoundStop();						//���ׂĂ̍Đ����~

};

