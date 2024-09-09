#include"DxLib.h"
#include"ConstantStrage.h"
#include"Stage.h"
#include "Player.h"
#include "ControlGemObject.h"

ControlGemObject::ControlGemObject()
{
    VECTOR pos;
    objectModelOriginal = MV1LoadModel("../model/GemModel/gem.mv1");

    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            pos.x = 0;
            pos.y = 0;
            pos.z = 0;
            objectPosition[i][j] = pos;
            obtainedObject[i][j] = false;
            objectModel[i][j] = MV1DuplicateModel(objectModelOriginal);
            MV1SetScale(objectModel[i][j], GEM_OBJECT_SCALE);
        }
    }
    objectModelRotation = 0;
}
ControlGemObject::~ControlGemObject()
{

}

//‰Šú‰»
void ControlGemObject::initialize(Stage stage)
{
    VECTOR pos;
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            pos.x = STAGE_CHIP_SIZE * j;
            pos.y = INITIALIZE_GEM_POSITION_Y;
            pos.z = -STAGE_CHIP_SIZE * i;
            objectPosition[i][j] = pos;
            MV1SetPosition(objectModel[i][j], objectPosition[i][j]);
            if (stage.getMap(i, j) != 0)
            {
                obtainedObject[i][j] = false;
            }
            else
            {
                obtainedObject[i][j] = true;
            }
        }
    }
    objectModelRotation = 0;
    obtainedObject[LEFT_SIDE][UP_SIDE] = true;
    obtainedObject[LEFT_SIDE][DOWN_SIDE] = true;
    obtainedObject[RIGHT_SIDE][UP_SIDE] = true;
    obtainedObject[RIGHT_SIDE][DOWN_SIDE] = true;
}

//•óÎ‚ð‰ñ“]‚³‚¹‚é
void ControlGemObject::rollingModel()
{
    //íŽž‰ñ“]
    objectModelRotation++;
    //360“x‚ð‰z‚¦‚½‚çƒŠƒZƒbƒg
    if (objectModelRotation > MAX_ANGLE)
    {
        objectModelRotation = 0;
    }
    //‰ñ“]‚ð”½‰f
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            MV1SetRotationXYZ(objectModel[i][j], VGet(0.0f, objectModelRotation * DX_PI_F / HALF_ANGLE, 0.0f));
        }
    }
}

