#include"DxLib.h"
#include "math.h"
#include"Player.h"
#include"ControlGemObject.h"
#include"CheckClear.h"
#include"ConstantStrage.h"
#include "Compass.h"

Compass::Compass()
{
    minDistance = INITIALIZE_MIN_DISTANCE;
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            target[i][j] = false;
        }
    }
    objectDirection = 0;
    model = MV1LoadModel("../model/CompassModel/compass.mv1");
    pos = VGet(0, INITIALIZE_COMPAS_POSITION_Y, 0);
    MV1SetPosition(model, pos);
    MV1SetRotationXYZ(model, VGet(0.0f, 0.0f, 0.0f));
    MV1SetScale(model, COMPAS_MODEL_SIZE);

}

Compass::~Compass()
{

}

//�ڕW�Ƃ���I�u�W�F�N�g�܂ł̋����Ɗp�x�����߂�
void Compass::findObjectDistanceAndDirection(Player player, ControlGemObject ControlGemObject, CheckClear checkClear)
{
    VECTOR Vec;

    //��΂��W�ߏI����Ă��邩����
    if (checkClear.getClearFlg_1() == false)
    {
        for (int i = 0; i < STAGE_SIZE; i++) {
            for (int j = 0; j < STAGE_SIZE; j++) {
                //�ڕW�܂ł̋������o��
                Vec = VSub(ControlGemObject.getPosition(i, j), player.getPosition());
                //�������ł��߂��I�u�W�F�N�g�Ȃ炻�̍��W��ۑ�
                if (VSize(Vec) < VSize(minDistance) && ControlGemObject.getObtainedObject(i, j) == false)
                {
                    minDistance = Vec;
                }
            }
        }

        //�p�x���擾
        objectDirection = float(atan2(minDistance.x, minDistance.z));
        //���W�𔽉f
        MV1SetPosition(model, VGet(player.getPositionX() + sinf(objectDirection), INITIALIZE_COMPAS_POSITION_Y, player.getPositionZ() + cosf(objectDirection)));
        //�p�x�𔽉f
        MV1SetRotationXYZ(model, VGet(0.0f, objectDirection + DX_PI_F, 0.0f));

        minDistance = INITIALIZE_MIN_DISTANCE;
    }
    else
    {
        //�S�[���̕���������
        Vec = VSub(GOAL_POSITION, player.getPosition());
        //�p�x���擾
        objectDirection = float(atan2(Vec.x, Vec.z));
        //���W�𔽉f
        MV1SetPosition(model, VGet(player.getPositionX() + sinf(objectDirection), INITIALIZE_COMPAS_POSITION_Y, player.getPositionZ() + cosf(objectDirection)));
        //�p�x�𔽉f
        MV1SetRotationXYZ(model, VGet(0.0f, objectDirection + DX_PI_F, 0.0f));
    }

}