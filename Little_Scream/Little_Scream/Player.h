#pragma once

#include"ConstantStrage.h"

class HelpfulItems;
class CheckDevice;
class ControlSound;

class Player
{
private:
	VECTOR position;            //プレイヤー座標
    VECTOR keepPosition;        //プレイヤー移動予定先座標
    float vRotate;              //視点　Y
    float hRotate;              //視点　X
    int mouseX;                 //マウス座標　X
    int mouseY;                 //マウス座標　Y
    VECTOR moveVector;          //プレイヤー移動量
public:
	Player();
	~Player();
    void initialize();  //初期化
	void control(HelpfulItems helpfulItems, CheckDevice checkDevice,ControlSound& sound);//プレイヤー操作

    VECTOR setPosition(VECTOR vector) { return position = vector; }             //座標セット
    VECTOR setKeepPosition(VECTOR vector) { return keepPosition = vector; }     //移動予定先をセット  
    VECTOR resetMoveVector() { return moveVector = VGet(0, 0, 0); }             //移動量をリセット
    //マウスを初期座標に戻す
    void resetMousePosition() { 
        mouseX = 0, mouseY = 0;        
        SetMousePoint(WINDOW_SIZE_WIDTH_HALF, WINDOW_SIZE_HEIGHT_HALF);
    }

    //ゲッター関数
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

    //定数
	const VECTOR INITIALIZE_POSITION = VGet(40.0f, 6.0f, -40.0f);     //プレイヤー初期座標
    const float FRONT_AND_BACK_MOVE_SPEED = 0.3f;                    //カメラ前後移動スピード
    const float SIDE_MOVE_SPEED = 0.2f;                              //カメラ横移動スピード
    const float ROTATE_SPEED = 0.0025f;                              //カメラ回転スピード
    const int MAX_ROTATE_SPEED = 200;                                //カメラ最大回転速度
    const float MAX_ROTATE_UP = -0.7f;                               //カメラ縦振り向き最大値
    const float MAX_ROTATE_DOWN = 1.5f;                              //カメラ縦振り向き最小値
    const int WINDOW_SIZE_WIDTH_HALF = WINDOW_SIZE_WIDTH / 2;        // 画面サイズ横の半分
    const int WINDOW_SIZE_HEIGHT_HALF = WINDOW_SIZE_HEIGHT / 2;      // 画面サイズ縦の半分
    const int CONTROLER_SPEED_X = 1000;                              //コントローラー視点移動スピード補正　X
    const int CONTROLER_SPEED_Y = 2000;                              //コントローラー視点移動スピード補正  Y
};

