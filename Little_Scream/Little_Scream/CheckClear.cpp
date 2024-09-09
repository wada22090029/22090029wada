#include"DxLib.h"
#include"ConstantStrage.h"
#include"ControlGemObject.h"
#include"Player.h"
#include"Collision.h"
#include"SceneStrage.h"
#include "CheckClear.h"

CheckClear::CheckClear()
{
    clearFlg_1 = false;
    clearFlg_2 = false;
    remainingControlGemObject = 0;
    goalModel = MV1LoadModel("../model/GemModel/Crystal.mv1");
    MV1SetPosition(goalModel, GOAL_POSITION);
    MV1SetScale(goalModel, GOAL_MODEL_SIZE);
    goalModelRotation = 0;
}

CheckClear::~CheckClear()
{

}

//初期化
void CheckClear::initialize()
{
    clearFlg_1 = false;
    clearFlg_2 = false;
    remainingControlGemObject = 0;
}

//宝石をすべて集めているか判定
void CheckClear::checkClearConditions_1(ControlGemObject ControlGemObject)
{
    //残りの宝石をカウントするために初期化
    remainingControlGemObject = 0;
    //クリアフラグをオンにする
    clearFlg_1 = true;

    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            //とれていない宝石がある場合
            if (ControlGemObject.getObtainedObject(i,j) == false)
            {
                //残りの宝石数のカウントを増やす
                remainingControlGemObject++;
                //クリアできていないのでフラグをオフにする
                clearFlg_1 = false;
            }
        }
    }
}

//ゴールまでたどり着いているか判定
void CheckClear::checkClearConditions_2(Player player,int& scene,Collision collision)
{
    //ゴールの範囲に入っているか判定
    if (collision.checkHitGoalArea(player) == true)
    {
        //入っていたらフラグをオンにしてシーン切り替え
        clearFlg_2 = true;
        scene = resultScene;
    }
}

//ゴールのモデルを回転
void CheckClear::rollingModel()
{
    //常に回転量をプラス
    goalModelRotation++;
    //360度を超えたら初期化
    if (goalModelRotation > MAX_ANGLE)
    {
        goalModelRotation = 0;
    }
    //設定を反映
    MV1SetRotationXYZ(goalModel, VGet(0.0f, goalModelRotation * DX_PI_F / HALF_ANGLE, 0.0f));
}