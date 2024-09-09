#include"DxLib.h"
#include"math.h"
#include"HelpfulItems.h"
#include"CheckDevice.h"
#include"ControlSound.h"
#include"ConstantStrage.h"
#include "Player.h"

Player::Player()
{
    vRotate = 0.0f;
    hRotate = 0.0f;
    mouseX = 0;
    mouseY = 0;
    SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
	position = INITIALIZE_POSITION;
    keepPosition = INITIALIZE_POSITION;
    moveVector = VGet(0, 0, 0);
}

Player::~Player()
{

}

//������
void Player::initialize()
{
    vRotate = 0.0f;
    hRotate = 0.0f;
    mouseX = 0;
    mouseY = 0;
    SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
    position = INITIALIZE_POSITION;
    keepPosition = INITIALIZE_POSITION;
    moveVector = VGet(0, 0, 0);
}

//�v���C���[����
void Player::control(HelpfulItems helpfulItems, CheckDevice checkDevice,ControlSound& sound)
{
    float itemAddSpeed = 1; //�A�C�e���ɂ�鑬�x�㏸�{��
    //�X�s�[�h�A�b�v�A�C�e���ő��x���㏸
    if (helpfulItems.getUsingItem(dashItem) == true)
    {
        itemAddSpeed = 1.5f;
    }
    //�e���|�[�g�A�C�e���Ń}�b�v������
    if (helpfulItems.getUsingItem(teleportItem) == true)
    {
        position = VGet(40.0f,6.0f,-40.0f);
    }
    //�x�N�g�������߂đ����Ă���
    if (CheckHitKey(KEY_INPUT_W) || (checkDevice.getPadInput() & PAD_INPUT_UP))
    {
        moveVector = VAdd(moveVector, VGet(sinf(hRotate) * FRONT_AND_BACK_MOVE_SPEED * itemAddSpeed, 0.0f, cosf(hRotate) * FRONT_AND_BACK_MOVE_SPEED * itemAddSpeed));
    }
    if (CheckHitKey(KEY_INPUT_A) || (checkDevice.getPadInput() & PAD_INPUT_LEFT))
    {
        moveVector = VAdd(moveVector, VGet(cosf(hRotate) * -SIDE_MOVE_SPEED * itemAddSpeed, 0.0f, sinf(hRotate) * SIDE_MOVE_SPEED * itemAddSpeed));
    }
    if (CheckHitKey(KEY_INPUT_S) || (checkDevice.getPadInput() & PAD_INPUT_DOWN))
    {
        moveVector = VAdd(moveVector, VGet(sinf(hRotate) * -FRONT_AND_BACK_MOVE_SPEED * itemAddSpeed, 0.0f, cosf(hRotate) * -FRONT_AND_BACK_MOVE_SPEED * itemAddSpeed));
    }
    if (CheckHitKey(KEY_INPUT_D) || (checkDevice.getPadInput() & PAD_INPUT_RIGHT))
    {
        moveVector = VAdd(moveVector, VGet(cosf(hRotate) * SIDE_MOVE_SPEED * itemAddSpeed, 0.0f, sinf(hRotate) * -SIDE_MOVE_SPEED * itemAddSpeed));
    }

    //�~�܂������v���C���[�̑������~�߂�
    if ((CheckHitKey(KEY_INPUT_W) == false && (checkDevice.getPadInput() & PAD_INPUT_UP) == false) &&
        (CheckHitKey(KEY_INPUT_A) == false && (checkDevice.getPadInput() & PAD_INPUT_LEFT) == false) &&
        (CheckHitKey(KEY_INPUT_S) == false && (checkDevice.getPadInput() & PAD_INPUT_DOWN) == false) &&
        (CheckHitKey(KEY_INPUT_D) == false && (checkDevice.getPadInput() & PAD_INPUT_RIGHT) == false))
    {
        sound.stopSound(playerDashSE);
    }
    //�����Ă���Ƃ��������o��
    else
    {
        sound.playSoundLoop(playerDashSE);
    }

    //�L�[�{�[�h�̎�
    if (checkDevice.getDevice() == 0)
    {
        //���݂̃}�E�X�̈ʒu�����߂�
        GetMousePoint(&mouseX, &mouseY);
        //1�t���[���O�Ƃ̋��������߂�
        int addMouseX = WINDOW_SIZE_WIDTH_HALF - mouseX;
        int addMouseY = WINDOW_SIZE_HEIGHT_HALF - mouseY;
        //��x�Ɉړ�����ő�ʂ�����@X
        //���
        if (addMouseX > MAX_ROTATE_SPEED)
        {
            hRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //����
        else if (addMouseX < -MAX_ROTATE_SPEED)
        {
            hRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //�ʏ�
        else
        {
            //�}�E�X�̋����̕��������_�ړ�
            hRotate -= addMouseX * ROTATE_SPEED;
        }
        //��x�Ɉړ�����ő�ʂ�����@Y
        //���
        if (addMouseY > MAX_ROTATE_SPEED)
        {
            vRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //����
        else if (addMouseY < -MAX_ROTATE_SPEED)
        {
            vRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //�ʏ�
        else
        {
            //�}�E�X�̋����̕��������_�ړ�
            vRotate -= addMouseY * ROTATE_SPEED;
        }

        //�}�E�X���������W�ɖ߂�
        SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
    }
    //�R���g���[���[�̎�
    else
    {
        //��x�Ɉړ�����ő�ʂ�����@X
        //���
        if (checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X > MAX_ROTATE_SPEED)
        {
            hRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //����
        else if (checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X < -MAX_ROTATE_SPEED)
        {
            hRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //�ʏ�
        else
        {
            //�E�X�e�B�b�N�ړ��ʂ̕��������_�ړ�
            hRotate += checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X * ROTATE_SPEED;
        }
        //��x�Ɉړ�����ő�ʂ�����@Y
        //���
        if (checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y > MAX_ROTATE_SPEED)
        {
            vRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //����
        else if (checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y < -MAX_ROTATE_SPEED)
        {
            vRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //�ʏ�
        else
        {
            //�E�X�e�B�b�N�ړ��ʂ̕��������_�ړ�
            vRotate -= checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y * ROTATE_SPEED;
        }
    }
    //�㉺�̂ݐU�������ő�l��ݒ�
    if (vRotate < MAX_ROTATE_UP)
    {
        vRotate = MAX_ROTATE_UP;
    }
    if (vRotate > MAX_ROTATE_DOWN)
    {
        vRotate = MAX_ROTATE_DOWN;
    }
}