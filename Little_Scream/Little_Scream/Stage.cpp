#include"DxLib.h"
#include "Stage.h"

Stage::Stage()
{
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            map[i][j] = 0;
            mapModel[i][j] = 0;
        }
    }
    floorModel[VERTICAL_RAIL] = MV1LoadModel("../model/StageModel/scaffold_high_railing_2.mv1");
    floorModel[SIDEWAYS_RAIL] = MV1LoadModel("../model/StageModel/scaffold_high_railing_2.mv1");
    floorModel[T_RAIL_UP] = MV1LoadModel("../model/StageModel/scaffold_high_t_railing_2.mv1");
    floorModel[T_RAIL_DOWN] = MV1LoadModel("../model/StageModel/scaffold_high_t_railing_2.mv1");
    floorModel[T_RAIL_RIGHT] = MV1LoadModel("../model/StageModel/scaffold_high_t_railing_2.mv1");
    floorModel[T_RAIL_LEFT] = MV1LoadModel("../model/StageModel/scaffold_high_t_railing_2.mv1");
    floorModel[NORMAL] = MV1LoadModel("../model/StageModel/scaffold_high_normal.mv1");
    floorModel[CORNER_LEFT_UP] = MV1LoadModel("../model/StageModel/scaffold_high_corner_2.mv1");
    floorModel[CORNER_RIGHT_UP] = MV1LoadModel("../model/StageModel/scaffold_high_corner_2.mv1");
    floorModel[CORNER_LEFT_DOWN] = MV1LoadModel("../model/StageModel/scaffold_high_corner_2.mv1");
    floorModel[CORNER_RIGHT_DOWN] = MV1LoadModel("../model/StageModel/scaffold_high_corner_2.mv1");

}

Stage::~Stage()
{

}

//�X�e�[�W���Z�b�g
void Stage::setStage()
{
    FILE* file;
    errno_t error;

    //�t�@�C�����J��    
    error = fopen_s(&file, "../map1.csv", "r");

    //�����J���Ȃ���΃G���[���b�Z�[�W
    if (error != 0)
        printf("�t�@�C�����J���܂���ł���");
    else {
        //�X�e�[�W�̌`��ƍ��W�����Ă���
        for (int i = 0; i < STAGE_SIZE; i++)
        {
            for (int j = 0; j < STAGE_SIZE; j++)
            {
                //�t�@�C���ǂݍ���
                fscanf_s(file,"%d,",&map[i][j]);
                mapModel[i][j] = MV1DuplicateModel(floorModel[map[i][j]]);
                if (map[i][j] == VERTICAL_RAIL)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == SIDEWAYS_RAIL)
                {
                    //�����Ȃ�
                }
                if (map[i][j] == T_RAIL_UP)
                {
                    //�����Ȃ�
                }
                if (map[i][j] == T_RAIL_DOWN)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, HALF_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == T_RAIL_RIGHT)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == T_RAIL_LEFT)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, (HALF_ANGLE + QUARTAR_ANGLE) * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_LEFT_UP)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_RIGHT_UP)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, HALF_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_LEFT_DOWN)
                {
                    //�����Ȃ�
                }
                if (map[i][j] == CORNER_RIGHT_DOWN)
                {
                    //��]
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, (HALF_ANGLE + QUARTAR_ANGLE) * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] != NORMAL)
                {
                    //�T�C�Y����
                    MV1SetScale(mapModel[i][j], STAGE_MODEL_SIZE);
                }
                //���W�m��
                MV1SetPosition(mapModel[i][j], VGet(j * STAGE_CHIP_SIZE, 0.0f, i * -STAGE_CHIP_SIZE));
            } 
        }
        fclose(file);
    }
}