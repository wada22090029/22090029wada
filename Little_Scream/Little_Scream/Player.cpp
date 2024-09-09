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

//初期化
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

//プレイヤー操作
void Player::control(HelpfulItems helpfulItems, CheckDevice checkDevice,ControlSound& sound)
{
    float itemAddSpeed = 1; //アイテムによる速度上昇倍率
    //スピードアップアイテムで速度が上昇
    if (helpfulItems.getUsingItem(dashItem) == true)
    {
        itemAddSpeed = 1.5f;
    }
    //テレポートアイテムでマップ中央へ
    if (helpfulItems.getUsingItem(teleportItem) == true)
    {
        position = VGet(40.0f,6.0f,-40.0f);
    }
    //ベクトルを求めて足していく
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

    //止まった時プレイヤーの足音を止める
    if ((CheckHitKey(KEY_INPUT_W) == false && (checkDevice.getPadInput() & PAD_INPUT_UP) == false) &&
        (CheckHitKey(KEY_INPUT_A) == false && (checkDevice.getPadInput() & PAD_INPUT_LEFT) == false) &&
        (CheckHitKey(KEY_INPUT_S) == false && (checkDevice.getPadInput() & PAD_INPUT_DOWN) == false) &&
        (CheckHitKey(KEY_INPUT_D) == false && (checkDevice.getPadInput() & PAD_INPUT_RIGHT) == false))
    {
        sound.stopSound(playerDashSE);
    }
    //動いているとき足音を出す
    else
    {
        sound.playSoundLoop(playerDashSE);
    }

    //キーボードの時
    if (checkDevice.getDevice() == 0)
    {
        //現在のマウスの位置を求める
        GetMousePoint(&mouseX, &mouseY);
        //1フレーム前との距離を求める
        int addMouseX = WINDOW_SIZE_WIDTH_HALF - mouseX;
        int addMouseY = WINDOW_SIZE_HEIGHT_HALF - mouseY;
        //一度に移動する最大量をつける　X
        //上限
        if (addMouseX > MAX_ROTATE_SPEED)
        {
            hRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //下限
        else if (addMouseX < -MAX_ROTATE_SPEED)
        {
            hRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //通常
        else
        {
            //マウスの距離の分だけ視点移動
            hRotate -= addMouseX * ROTATE_SPEED;
        }
        //一度に移動する最大量をつける　Y
        //上限
        if (addMouseY > MAX_ROTATE_SPEED)
        {
            vRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //下限
        else if (addMouseY < -MAX_ROTATE_SPEED)
        {
            vRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //通常
        else
        {
            //マウスの距離の分だけ視点移動
            vRotate -= addMouseY * ROTATE_SPEED;
        }

        //マウスを初期座標に戻す
        SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
    }
    //コントローラーの時
    else
    {
        //一度に移動する最大量をつける　X
        //上限
        if (checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X > MAX_ROTATE_SPEED)
        {
            hRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //下限
        else if (checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X < -MAX_ROTATE_SPEED)
        {
            hRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //通常
        else
        {
            //右スティック移動量の分だけ視点移動
            hRotate += checkDevice.getPadRightRotateX() / CONTROLER_SPEED_X * ROTATE_SPEED;
        }
        //一度に移動する最大量をつける　Y
        //上限
        if (checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y > MAX_ROTATE_SPEED)
        {
            vRotate -= MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //下限
        else if (checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y < -MAX_ROTATE_SPEED)
        {
            vRotate -= -MAX_ROTATE_SPEED * ROTATE_SPEED;
        }
        //通常
        else
        {
            //右スティック移動量の分だけ視点移動
            vRotate -= checkDevice.getPadRightRotateY() / CONTROLER_SPEED_Y * ROTATE_SPEED;
        }
    }
    //上下のみ振り向ける最大値を設定
    if (vRotate < MAX_ROTATE_UP)
    {
        vRotate = MAX_ROTATE_UP;
    }
    if (vRotate > MAX_ROTATE_DOWN)
    {
        vRotate = MAX_ROTATE_DOWN;
    }
}