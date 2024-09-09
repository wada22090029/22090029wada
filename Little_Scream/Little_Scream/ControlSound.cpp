#include"DxLib.h"
#include"Enemy.h"
#include"Player.h"
#include"ConstantStrage.h"
#include "ControlSound.h"

ControlSound::ControlSound()
{
	//読み込み
	soundHandle[enemyDashSE] = LoadSoundMem("../sound/敵走行音.mp3");
	soundHandle[titleBGM] = LoadSoundMem("../sound/タイトルBGM.mp3");
	soundHandle[goalBGM] = LoadSoundMem("../sound/ゴールBGM.mp3");
	soundHandle[playerDashSE] = LoadSoundMem("../sound/プレイヤー走行音.mp3");
	soundHandle[selectSE] = LoadSoundMem("../sound/選択時.mp3");
	soundHandle[decisionSE] = LoadSoundMem("../sound/決定時.mp3");
	soundHandle[deadSE] = LoadSoundMem("../sound/死亡時.mp3");
	soundHandle[getObjectSE] = LoadSoundMem("../sound/取得時.mp3");
	soundHandle[itemUseSE] = LoadSoundMem("../sound/アイテム使用時.mp3");
}

ControlSound::~ControlSound()
{

}

//通常再生
void ControlSound::playSound(int soundName)
{
	PlaySoundMem(soundHandle[soundName], DX_PLAYTYPE_BACK);
}

//ループ再生
void ControlSound::playSoundLoop(int soundName)
{
	if (CheckSoundMem(soundHandle[soundName]) == FALSE)
	{
		PlaySoundMem(soundHandle[soundName], DX_PLAYTYPE_LOOP);
	}
}

//再生停止
void ControlSound::stopSound(int soundName)
{
	if (CheckSoundMem(soundHandle[soundName]) == TRUE)
	{
		StopSoundMem(soundHandle[soundName]);
	}
}

//すべての再生を停止
void ControlSound::allSoundStop()
{
	for (int i = 0; i < MAX_SOUND_KIND; i++)
	{
		StopSoundMem(soundHandle[i]);
	}
}