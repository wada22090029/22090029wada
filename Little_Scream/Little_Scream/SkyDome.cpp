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

//�X�J�C�h�[���̍��W���Z�b�g
void SkyDome::setPosition(Player player)
{
    //�v���C���[�̍��W�𒆐S�Ƃ���
    MV1SetPosition(model, player.getPosition());
}