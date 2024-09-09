#pragma once
#include"ConstantStrage.h"

class Stage
{
private:
    static const int ALL_FLOOR_MODEL = 13;  //ステージの床全種

    int map[STAGE_SIZE][STAGE_SIZE];    //マップチップ保管用
    int floorModel[ALL_FLOOR_MODEL];    //床のモデルの種類
    int mapModel[STAGE_SIZE][STAGE_SIZE];    //マップモデル

public:

    Stage();
    ~Stage();
    void setStage();     //ステージをセット

    //ゲッター関数
    int getMap(const int i, const  int j) { return map[i][j]; }
    int getStageModel(const int i, const int j) { return mapModel[i][j]; }

private:
    //ステージの各形状
    enum STAGE_FLOOR_KIND {
        VERTICAL_RAIL = 1,
        SIDEWAYS_RAIL,
        T_RAIL_UP,
        T_RAIL_DOWN,
        T_RAIL_RIGHT,
        T_RAIL_LEFT,
        NORMAL,
        JUMP_ZONE,
        CORNER_LEFT_UP,
        CORNER_RIGHT_UP,
        CORNER_LEFT_DOWN,
        CORNER_RIGHT_DOWN,
    };
    const VECTOR STAGE_MODEL_SIZE = VGet(0.01f, 0.01f, 0.01f);  //ステージサイズ
};

