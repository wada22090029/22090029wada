#include"DxLib.h"
#include"Player.h"
#include "SkyDome.h"

SkyDome::SkyDome()
{
    model = MV1LoadModel("../model/SkydomeModel/Dome_QQ101.x");
}

SkyDome::~SkyDome()
{

}

//スカイドームの座標をセット
void SkyDome::setPosition(Player player)
{
    //プレイヤーの座標を中心とする
    MV1SetPosition(model, player.getPosition());
}