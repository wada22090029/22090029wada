#pragma once

#include "ConstantStrage.h"

class Stage;
class Player;
class HelpfulItems;
class ControlSound;

class Enemy
{
private:
    static const int ALL_WAYPOINT = 441;
    static int edgeCost[][ALL_WAYPOINT];        //�ړ��R�X�g�p�z��
    int enemyModel;             //�G���f��
    VECTOR position;            //�G���W
    VECTOR waypointArray[ALL_WAYPOINT];  //�E�F�C�|�C���g���W�ۑ��p
    VECTOR waypointPosition;             //�E�F�C�|�C���g�ʍ��W�����߂�ۂɎg�p
    int targetIndex;                     //�ڕW�n�_
    int attachAnimationIndex;            //�G�̃A�j���[�V����
    float animationTotalTime;            //�A�j���[�V�����̑�����
    float animationPlayTime;             //���݂̃A�j���[�V�����̍Đ�����
    VECTOR targetWayPoint;               //�ڕW�Ƃ���E�F�C�|�C���g
    bool goalFlg;                        //�ڕW�n�_�ɂ���������
    float targetRotation;                //�G�̖ڕW�Ƃ����]��
    float nowRotation;                   //�G�̌��݂̉�]��


public:
    Enemy();
    ~Enemy();
    void initialize();      //������
    void createWaypointAndEdge(Stage stage, const VECTOR targetPos);      //�E�F�C�|�C���g�ƈړ��R�X�g�쐬
    void updatePosition(Stage stage,const VECTOR targetPos, Player player, HelpfulItems helpfulItems,ControlSound& sound);      //�G�̍��W�X�V
    int searchNearestPoint(const VECTOR& pos);                  //�ł��߂��E�F�C�|�C���g��T��
    int dijkstra(Stage stage,const int start,const int goal);   //�_�C�N�X�g���@�Ōo�H�T��
    void animation();                                           //�A�j���[�V������t����

    //�Q�b�^�[�֐�
    int getEdgeCost(const int i,const int j) { return edgeCost[i][j]; }
    VECTOR getWayPointPos(const int& index);
    VECTOR getWaypointArray(const int i) { return waypointArray[i]; }
    VECTOR getPosition() { return position; }
    int getModel() { return enemyModel; }

private:    
    //�萔
    const float ROTATION_RANGE = 5.625f;        //�G�̂̉�]���x
    const float ENEMY_SPEED = 0.2f;             //�G�̈ړ����x
    const int TRUE_COST = 1;                    //�ʂ��ꏊ�̈ړ��R�X�g
    const int FALSE_COST = -1;                  //�ʂ�Ȃ��ꏊ�̈ړ��R�X�g
    const float TARGET_RANGE = 0.15f;           //�ڕW�n�_�ɂ����ƔF������͈�
    const int MAX_DIST = 99999;                 //�ő�ړ��萔
    const float ANIMATION_SPEED = 0.55f;        //�A�j���[�V�����Đ����x
    const VECTOR INITIALIZE_WAYPOINT_POSITION = VGet(0, 5.5f, 0);       //�E�F�C�|�C���g�������W
    const VECTOR INITIALIZE_ENEMY_POSITION = VGet(0.0f, 5.5f, 0.0f);          //�G�������W
    const VECTOR ENEMY_MODEL_SCALE = VGet(0.015f, 0.015f, 0.015f);      //�G���f���T�C�Y
    const VECTOR ADJUST_ENEMY_POSITION_ANIMATION = VGet(0.0f, -25.0f, 0.0f);      //�A�j���[�V�����g�p���̍��W�����l
    const VECTOR ADJUST_ENEMY_POSITION_Y = VGet(0, 1.0f, 0);
    const int ADJUST_ENEMY_ROTATION = -5;       //�A�j���[�V�����ɂ��G�̉�]������
    const int MINDISTANCE_SHIFT = 30;           //minDistance�̃V�t�g��
    const int ADJACENT_NUM = 1;                 //�[����אڂ��������擾���邽�߂̒萔
};

