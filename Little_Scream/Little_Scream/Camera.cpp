#include"DxLib.h"
#include"math.h"
#include"Player.h"
#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::mainCamera(Player player)
{
    //カメラ配置
    SetCameraPositionAndAngle(player.getPosition(), player.getRotateV(), player.getRotateH(), 0.0f);
}
