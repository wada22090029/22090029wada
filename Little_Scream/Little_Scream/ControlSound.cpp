#include"DxLib.h"
#include"Enemy.h"
#include"Player.h"
#include"ConstantStrage.h"
#include "ControlSound.h"

ControlSound::ControlSound()
{
	//�ǂݍ���
	soundHandle[enemyDashSE] = LoadSoundMem("../sound/�G���s��.mp3");
	soundHandle[titleBGM] = LoadSoundMem("../sound/�^�C�g��BGM.mp3");
	soundHandle[goalBGM] = LoadSoundMem("../sound/�S�[��BGM.mp3");
	soundHandle[playerDashSE] = LoadSoundMem("../sound/�v���C���[���s��.mp3");
	soundHandle[selectSE] = LoadSoundMem("../sound/�I����.mp3");
	soundHandle[decisionSE] = LoadSoundMem("../sound/���莞.mp3");
	soundHandle[deadSE] = LoadSoundMem("../sound/���S��.mp3");
	soundHandle[getObjectSE] = LoadSoundMem("../sound/�擾��.mp3");
	soundHandle[itemUseSE] = LoadSoundMem("../sound/�A�C�e���g�p��.mp3");
}

ControlSound::~ControlSound()
{

}

//�ʏ�Đ�
void ControlSound::playSound(int soundName)
{
	PlaySoundMem(soundHandle[soundName], DX_PLAYTYPE_BACK);
}

//���[�v�Đ�
void ControlSound::playSoundLoop(int soundName)
{
	if (CheckSoundMem(soundHandle[soundName]) == FALSE)
	{
		PlaySoundMem(soundHandle[soundName], DX_PLAYTYPE_LOOP);
	}
}

//�Đ���~
void ControlSound::stopSound(int soundName)
{
	if (CheckSoundMem(soundHandle[soundName]) == TRUE)
	{
		StopSoundMem(soundHandle[soundName]);
	}
}

//���ׂĂ̍Đ����~
void ControlSound::allSoundStop()
{
	for (int i = 0; i < MAX_SOUND_KIND; i++)
	{
		StopSoundMem(soundHandle[i]);
	}
}