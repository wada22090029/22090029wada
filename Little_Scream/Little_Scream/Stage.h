#pragma once
#include"ConstantStrage.h"

class Stage
{
private:
    static const int ALL_FLOOR_MODEL = 13;  //�X�e�[�W�̏��S��

    int map[STAGE_SIZE][STAGE_SIZE];    //�}�b�v�`�b�v�ۊǗp
    int floorModel[ALL_FLOOR_MODEL];    //���̃��f���̎��
    int mapModel[STAGE_SIZE][STAGE_SIZE];    //�}�b�v���f��

public:

    Stage();
    ~Stage();
    void setStage();     //�X�e�[�W���Z�b�g

    //�Q�b�^�[�֐�
    int getMap(const int i, const  int j) { return map[i][j]; }
    int getStageModel(const int i, const int j) { return mapModel[i][j]; }

private:
    //�X�e�[�W�̊e�`��
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
    const VECTOR STAGE_MODEL_SIZE = VGet(0.01f, 0.01f, 0.01f);  //�X�e�[�W�T�C�Y
};

