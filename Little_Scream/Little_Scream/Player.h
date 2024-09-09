#pragma once

#include"ConstantStrage.h"

class HelpfulItems;
class CheckDevice;
class ControlSound;

class Player
{
private:
	VECTOR position;            //�v���C���[���W
    VECTOR keepPosition;        //�v���C���[�ړ��\�����W
    float vRotate;              //���_�@Y
    float hRotate;              //���_�@X
    int mouseX;                 //�}�E�X���W�@X
    int mouseY;                 //�}�E�X���W�@Y
    VECTOR moveVector;          //�v���C���[�ړ���
public:
	Player();
	~Player();
    void initialize();  //������
	void control(HelpfulItems helpfulItems, CheckDevice checkDevice,ControlSound& sound);//�v���C���[����

    VECTOR setPosition(VECTOR vector) { return position = vector; }             //���W�Z�b�g
    VECTOR setKeepPosition(VECTOR vector) { return keepPosition = vector; }     //�ړ��\�����Z�b�g  
    VECTOR resetMoveVector() { return moveVector = VGet(0, 0, 0); }             //�ړ��ʂ����Z�b�g
    //�}�E�X���������W�ɖ߂�
    void resetMousePosition() { 
        mouseX = 0, mouseY = 0;        
        SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
    }

    //�Q�b�^�[�֐�
	VECTOR getPosition() { return position; }
    VECTOR getKeepPosition() { return keepPosition; }
    VECTOR getMoveVector() { return moveVector; }
    float getPositionX() { return position.x; }
    float getPositionY() { return position.y; }
    float getPositionZ() { return position.z; }
    float getKeepPositionX() { return keepPosition.x; }
    float getKeepPositionY() { return keepPosition.y; }
    float getKeepPositionZ() { return keepPosition.z; }
    float getRotateV() { return vRotate; }
    float getRotateH() { return hRotate; }


private:

    //�萔
	const VECTOR INITIALIZE_POSITION = VGet(40.0f, 6.0f, -40.0f);     //�v���C���[�������W
    const float FRONT_AND_BACK_MOVE_SPEED = 0.3f;                    //�J�����O��ړ��X�s�[�h
    const float SIDE_MOVE_SPEED = 0.2f;                              //�J�������ړ��X�s�[�h
    const float ROTATE_SPEED = 0.0025f;                              //�J������]�X�s�[�h
    const int MAX_ROTATE_SPEED = 200;                                //�J�����ő��]���x
    const float MAX_ROTATE_UP = -0.7f;                               //�J�����c�U������ő�l
    const float MAX_ROTATE_DOWN = 1.5f;                              //�J�����c�U������ŏ��l
    const int WINDOW_SIZE_WIDTH_HALF = WINDOW_SIZE_WIDTH / 2;        // ��ʃT�C�Y���̔���
    const int WINDOW_SIZE_HEIGHT_HALF = WINDOW_SIZE_HEIGHT / 2;      // ��ʃT�C�Y�c�̔���
    const int CONTROLER_SPEED_X = 1000;                              //�R���g���[���[���_�ړ��X�s�[�h�␳�@X
    const int CONTROLER_SPEED_Y = 2000;                              //�R���g���[���[���_�ړ��X�s�[�h�␳  Y
};

