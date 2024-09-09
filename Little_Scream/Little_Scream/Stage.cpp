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

//ステージをセット
void Stage::setStage()
{
    FILE* file;
    errno_t error;

    //ファイルを開く    
    error = fopen_s(&file, "../map1.csv", "r");

    //もし開けなければエラーメッセージ
    if (error != 0)
        printf("ファイルを開けませんでした");
    else {
        //ステージの形状と座標を入れていく
        for (int i = 0; i < STAGE_SIZE; i++)
        {
            for (int j = 0; j < STAGE_SIZE; j++)
            {
                //ファイル読み込み
                fscanf_s(file,"%d,",&map[i][j]);
                mapModel[i][j] = MV1DuplicateModel(floorModel[map[i][j]]);
                if (map[i][j] == VERTICAL_RAIL)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == SIDEWAYS_RAIL)
                {
                    //処理なし
                }
                if (map[i][j] == T_RAIL_UP)
                {
                    //処理なし
                }
                if (map[i][j] == T_RAIL_DOWN)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, HALF_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == T_RAIL_RIGHT)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == T_RAIL_LEFT)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, (HALF_ANGLE + QUARTAR_ANGLE) * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_LEFT_UP)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, QUARTAR_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_RIGHT_UP)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, HALF_ANGLE * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] == CORNER_LEFT_DOWN)
                {
                    //処理なし
                }
                if (map[i][j] == CORNER_RIGHT_DOWN)
                {
                    //回転
                    MV1SetRotationXYZ(mapModel[i][j], VGet(0.0f, (HALF_ANGLE + QUARTAR_ANGLE) * DX_PI_F / HALF_ANGLE, 0.0f));
                }
                if (map[i][j] != NORMAL)
                {
                    //サイズ調整
                    MV1SetScale(mapModel[i][j], STAGE_MODEL_SIZE);
                }
                //座標確定
                MV1SetPosition(mapModel[i][j], VGet(j * STAGE_CHIP_SIZE, 0.0f, i * -STAGE_CHIP_SIZE));
            } 
        }
        fclose(file);
    }
}