#pragma once

static const int STAGE_SIZE = 21;  //�}�b�v�T�C�Y�c��

const float STAGE_CHIP_SIZE = 4.0f;  //�X�e�[�W�̃��f��1�^�C���T�C�Y

//�E�B���h�E�T�C�Y
const int WINDOW_SIZE_WIDTH = 1920;
const int WINDOW_SIZE_HEIGHT = 1080;

const int COLOR_BIT = 32;//�J���[�r�b�g

//�f�o�C�X����
const int DEVICE_CONTROLLER = 1;
const int DEVICE_KEYBORD = 0;

const int ALL_HELPFULL_ITEM_KIND = 4;//�������A�C�e���̎��
const float MAX_ANGLE = 360.0f;      //360�x
const float HALF_ANGLE = 180.0f;     //180�x
const float QUARTAR_ANGLE = 90.0f;   //90�x
const int HALF = 2;                  //2���̈�ɂ���
const VECTOR GOAL_POSITION = VGet(40.0f, 8.0f, -40.0f);     //�S�[���̍��W
const int TUTORIAL_KIND = 2;    //�`���[�g���A���̑��y�[�W��
const int MIN_FONT = 0;			//�������t�H���g �ԍ�
const int MAX_FONT = 1;			//�傫���t�H���g �ԍ�

//�^�C�g���őI�ׂ�R�}���h
enum TitleCommand {
    playGame,
    endGame
};

//���U���g�ƃ|�[�Y��ʂőI�ׂ�R�}���h
enum ResultAndPauseCommand {
    retry,
    returnTitle,
    continueGame = -1   //���̃R�}���h�̂݃|�[�Y�Ŏg�p
};

//�A�C�e���̖��O
enum ItemName {
    stunItem,
    dashItem,
    absorbItem,
    teleportItem,
    nothing
};

//���֘A�̃X�g���[�W
enum soundStrage {
	titleBGM,
	goalBGM,
	playerDashSE,
	enemyDashSE,
	selectSE,
	decisionSE,
	deadSE,
	getObjectSE,
	itemUseSE
};