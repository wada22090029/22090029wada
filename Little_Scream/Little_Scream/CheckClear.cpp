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

//������
void CheckClear::initialize()
{
    clearFlg_1 = false;
    clearFlg_2 = false;
    remainingControlGemObject = 0;
}

//��΂����ׂďW�߂Ă��邩����
void CheckClear::checkClearConditions_1(ControlGemObject ControlGemObject)
{
    //�c��̕�΂��J�E���g���邽�߂ɏ�����
    remainingControlGemObject = 0;
    //�N���A�t���O���I���ɂ���
    clearFlg_1 = true;

    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            //�Ƃ�Ă��Ȃ���΂�����ꍇ
            if (ControlGemObject.getObtainedObject(i,j) == false)
            {
                //�c��̕�ΐ��̃J�E���g�𑝂₷
                remainingControlGemObject++;
                //�N���A�ł��Ă��Ȃ��̂Ńt���O���I�t�ɂ���
                clearFlg_1 = false;
            }
        }
    }
}

//�S�[���܂ł��ǂ蒅���Ă��邩����
void CheckClear::checkClearConditions_2(Player player,int& scene,Collision collision)
{
    //�S�[���͈̔͂ɓ����Ă��邩����
    if (collision.checkHitGoalArea(player) == true)
    {
        //�����Ă�����t���O���I���ɂ��ăV�[���؂�ւ�
        clearFlg_2 = true;
        scene = resultScene;
    }
}

//�S�[���̃��f������]
void CheckClear::rollingModel()
{
    //��ɉ�]�ʂ��v���X
    goalModelRotation++;
    //360�x�𒴂����珉����
    if (goalModelRotation > MAX_ANGLE)
    {
        goalModelRotation = 0;
    }
    //�ݒ�𔽉f
    MV1SetRotationXYZ(goalModel, VGet(0.0f, goalModelRotation * DX_PI_F / HALF_ANGLE, 0.0f));
}