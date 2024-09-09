#include"DxLib.h"
#include"math.h"
#include"Player.h"
#include "Light.h"

Light::Light()
{
    playerLightHandle = 0;
}

Light::~Light()
{

}

void Light::setPlayerLight(Player player)
{
    // プレイヤー前方を光らせる
    playerLightHandle = CreateSpotLightHandle(
        VGet(player.getPositionX(), player.getPositionY(), player.getPositionZ()),
        VGet(sinf(player.getRotateH()), tanf(-player.getRotateV()), cosf(player.getRotateH())),
        DX_PI_F / HALF,
        0.0f,
        LIGHT_RANGE,
        ATTAN_1,
        ATTAN_2,
        ATTAN_3);
}