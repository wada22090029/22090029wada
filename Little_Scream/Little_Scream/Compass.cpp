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

//目標とするオブジェクトまでの距離と角度を求める
void Compass::findObjectDistanceAndDirection(Player player, ControlGemObject ControlGemObject, CheckClear checkClear)
{
    VECTOR Vec;

    //宝石を集め終わっているか判定
    if (checkClear.getClearFlg_1() == false)
    {
        for (int i = 0; i < STAGE_SIZE; i++) {
            for (int j = 0; j < STAGE_SIZE; j++) {
                //目標までの距離を出す
                Vec = VSub(ControlGemObject.getPosition(i, j), player.getPosition());
                //距離が最も近いオブジェクトならその座標を保存
                if (VSize(Vec) < VSize(minDistance) && ControlGemObject.getObtainedObject(i, j) == false)
                {
                    minDistance = Vec;
                }
            }
        }

        //角度を取得
        objectDirection = float(atan2(minDistance.x, minDistance.z));
        //座標を反映
        MV1SetPosition(model, VGet(player.getPositionX() + sinf(objectDirection), INITIALIZE_COMPAS_POSITION_Y, player.getPositionZ() + cosf(objectDirection)));
        //角度を反映
        MV1SetRotationXYZ(model, VGet(0.0f, objectDirection + DX_PI_F, 0.0f));

        minDistance = INITIALIZE_MIN_DISTANCE;
    }
    else
    {
        //ゴールの方向を示す
        Vec = VSub(GOAL_POSITION, player.getPosition());
        //角度を取得
        objectDirection = float(atan2(Vec.x, Vec.z));
        //座標を反映
        MV1SetPosition(model, VGet(player.getPositionX() + sinf(objectDirection), INITIALIZE_COMPAS_POSITION_Y, player.getPositionZ() + cosf(objectDirection)));
        //角度を反映
        MV1SetRotationXYZ(model, VGet(0.0f, objectDirection + DX_PI_F, 0.0f));
    }

}