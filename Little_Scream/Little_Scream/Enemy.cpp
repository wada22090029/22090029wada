#include "DxLib.h"
#include "math.h"
#include "ConstantStrage.h"
#include "Stage.h"
#include "Player.h"
#include "HelpfulItems.h"
#include"ControlSound.h"
#include "SceneStrage.h"
#include "Enemy.h"

Enemy::Enemy()
{
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            waypointPosition = INITIALIZE_WAYPOINT_POSITION;
            waypointArray[i] = waypointPosition;
            edgeCost[i][j] = 0;
        }
    }
    position = INITIALIZE_ENEMY_POSITION;

    targetIndex = 0;
    enemyModel = MV1LoadModel("../model/EnemyModel/CursedPriest.mv1");
    MV1SetScale(enemyModel, ENEMY_MODEL_SCALE);
    attachAnimationIndex = MV1AttachAnim(enemyModel, 0, -1, FALSE);
    animationTotalTime = MV1GetAttachAnimTotalTime(enemyModel, attachAnimationIndex);
    animationPlayTime = 0.0f;
    targetWayPoint = INITIALIZE_WAYPOINT_POSITION;
    goalFlg = true;
    nowRotation = 0;
    targetRotation = 0;
}

Enemy::~Enemy()
{

}

//������
void Enemy::initialize()
{
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            waypointPosition = INITIALIZE_WAYPOINT_POSITION;
            waypointArray[i] = waypointPosition;
            edgeCost[i][j] = 0;
        }
    }
    position = INITIALIZE_ENEMY_POSITION;
    MV1SetPosition(enemyModel, position);

    targetIndex = 0;
    targetWayPoint = INITIALIZE_WAYPOINT_POSITION;
    goalFlg = true;
}

int Enemy::edgeCost[ALL_WAYPOINT][ALL_WAYPOINT];

void Enemy::createWaypointAndEdge(Stage stage, const VECTOR targetPos)
{
    //�E�F�C�|�C���g�쐬
    for (int i = 0; i < ALL_WAYPOINT; i++) {
            waypointPosition.x =  STAGE_CHIP_SIZE * (i % STAGE_SIZE);
            waypointPosition.z =  -STAGE_CHIP_SIZE * (i / STAGE_SIZE);
            waypointArray[i] = waypointPosition;
    }

    //�G�b�W
    //������.
    for (int i = 0; i < ALL_WAYPOINT; i++) {
        for (int j = 0; j < ALL_WAYPOINT; j++) {

            if (i == j)
            {
                edgeCost[i][j] = 0;
            }
            else if (i >= STAGE_SIZE && j == i - STAGE_SIZE)
            {
                edgeCost[i][j] = TRUE_COST;
            }
            else if (i < ALL_WAYPOINT - STAGE_SIZE && j == i + STAGE_SIZE)
            {
                edgeCost[i][j] = TRUE_COST;
            }
            else if (i > 0 && j == i - ADJACENT_NUM && i % STAGE_SIZE != 0)
            {
                edgeCost[i][j] = TRUE_COST;
            }
            else if (i < ALL_WAYPOINT - ADJACENT_NUM && j == i + ADJACENT_NUM && j % STAGE_SIZE != 0)
            {
                edgeCost[i][j] = TRUE_COST;
            }
            else
            {
                edgeCost[i][j] = FALSE_COST;
            }
        }
    }

    //�G�b�W�ݒ� �Y���ӏ��������l���}�C�i�X�ɂ���
    for (int i = ADJACENT_NUM; i < STAGE_SIZE - ADJACENT_NUM; i++) {
        for (int j = ADJACENT_NUM; j < STAGE_SIZE - ADJACENT_NUM; j++) {
            if (stage.getMap(i, j) == 0)
            {
                edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j] = FALSE_COST; //���ʒu
                edgeCost[i * STAGE_SIZE + j - ADJACENT_NUM][i * STAGE_SIZE + j] = edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j - ADJACENT_NUM] = FALSE_COST; //���̕�
                edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j + ADJACENT_NUM] = edgeCost[i * STAGE_SIZE + j + ADJACENT_NUM][i * STAGE_SIZE + j] = FALSE_COST; //�E�̕�
                edgeCost[(i - ADJACENT_NUM) * STAGE_SIZE + j][i * STAGE_SIZE + j] = edgeCost[i * STAGE_SIZE + j][(i - ADJACENT_NUM) * STAGE_SIZE + j] = FALSE_COST; //��̕�
                edgeCost[i * STAGE_SIZE + j][(i + ADJACENT_NUM) * STAGE_SIZE + j] = edgeCost[(i + ADJACENT_NUM) * STAGE_SIZE + j][i * STAGE_SIZE + j] = FALSE_COST; //���̕�
            }
        }
    }

}


//�ʒu�X�V.
void Enemy::updatePosition(Stage stage,const VECTOR targetPos,Player player, HelpfulItems helpfulItems,ControlSound& sound)
{
    //�ڕW�̃E�F�C�|�C���g�͌������Ă���
    if (goalFlg == true) {
        //���̃E�F�C�|�C���g��T��
        const int playerPoint = searchNearestPoint(targetPos);
        if (stage.getMap(playerPoint / STAGE_SIZE, playerPoint % STAGE_SIZE) != 0)
        {
            //�_�C�N�X�g���@�Ń^�[�Q�b�g�̈ʒu��T��
            targetIndex = dijkstra(stage, targetIndex, playerPoint);
            //�ł��߂��E�F�C�|�C���g��T��
            targetWayPoint = getWayPointPos(targetIndex);
        }
        goalFlg = false;
    }

    //�X�^���A�C�e�����g���Ă��Ȃ����
    if (helpfulItems.getUsingItem(stunItem) == false)
    {
        sound.playSoundLoop(enemyDashSE);
        //�ړ�����+��]����
        if (targetWayPoint.x + TARGET_RANGE > position.x && targetWayPoint.x - TARGET_RANGE < position.x)
        {
            //z���ړ�
            if (targetWayPoint.z - TARGET_RANGE > position.z)
            {
                targetRotation = HALF_ANGLE;
                position.z += ENEMY_SPEED;
            }
            else if (targetWayPoint.z + TARGET_RANGE < position.z)
            {
                targetRotation = 0;
                position.z -= ENEMY_SPEED;
            }
            else
            {
                goalFlg = true;
            }
        }
        else
        {
            //x���ړ�
            if (targetWayPoint.x - TARGET_RANGE > position.x)
            {
                targetRotation = QUARTAR_ANGLE + HALF_ANGLE;
                position.x += ENEMY_SPEED;
            }
            else if (targetWayPoint.x + TARGET_RANGE < position.x)
            {
                targetRotation = QUARTAR_ANGLE;
                position.x -= ENEMY_SPEED;
            }
        }
    }

    //��]�p�x�����߂�
    float rotationDifference = targetRotation - nowRotation;

    //�����]�����ɃX���[�Y�ɉ�]
    //�ő��360�x�ɂ���
    if (nowRotation > MAX_ANGLE)
    {
        nowRotation = 0.0f;
    }
    if (nowRotation < 0.0f)
    {
        nowRotation = MAX_ANGLE;
    }

    //��]���ڕW�܂ł̍ŒZ�����ɋ߂������ɉ�]
    if (rotationDifference > 0 && rotationDifference < HALF_ANGLE || rotationDifference < -HALF_ANGLE)
    {
        if (targetRotation != nowRotation)
        {
            nowRotation += ROTATION_RANGE;
        }
    }
    else
    {
        if (targetRotation != nowRotation)
        {
            nowRotation -= ROTATION_RANGE;
        }
    }

    //�A�j���[�V����
    animation();
}

//�w��ʒu�����ԋ߂��E�F�C�|�C���g��T��.
int Enemy::searchNearestPoint(const VECTOR& pos)
{
    const int waypointNum = ALL_WAYPOINT;
    if (!(waypointArray && (waypointNum > 0))) { return -1; }

    //�����Œ��߂��ǂ������f.
    int     nextPoint = -1;
    float   minDistance = (float)(1 << MINDISTANCE_SHIFT);
    for (int i = 0; i < waypointNum; i++) {
        //�������o��
        VECTOR distanceBetween = VSub(waypointArray[i], pos);
        const float distance = sqrtf(distanceBetween.x * distanceBetween.x + distanceBetween.z * distanceBetween.z);
        //�߂��ق���minDistance��
        if (distance > minDistance) { continue; }
        minDistance = distance;
        nextPoint = i;
    }

    return nextPoint;
}

//�E�F�C�|�C���g�̈ʒu���擾.
VECTOR Enemy::getWayPointPos(const int& index)
{
    VECTOR tmp;
    tmp.x = 0.0f;
    tmp.z = 0.0f;

    const int waypointNum = ALL_WAYPOINT;
    //�ُ킪�Ȃ������
    if (!(waypointArray && (waypointNum > 0))) { return tmp; }
    if (0 > index || index >= waypointNum) { return tmp; }

    return waypointArray[index];
}

//�_�C�N�X�g���@
int Enemy::dijkstra(Stage stage,const int start,const int goal)
{
    int pDist[ALL_WAYPOINT];//�o���n����e�n�_�܂ł̍ŒZ����
    bool visited[ALL_WAYPOINT];//�K�ꂽ�n�_���L�^
    int pRoute[ALL_WAYPOINT];//�e�n�_�̍ŒZ�����̊m����
    int sRoute[ALL_WAYPOINT];//�ŒZ�o�H��̒n�_�̒n�_�ԍ�
    int sPoint, newDist, i, j;//�ꎞ�ۑ��p�ƃ��[�v�p�ϐ�

    //������
    for (i = 0; i < ALL_WAYPOINT; i++) {
        sRoute[i] = -1;
        pDist[i] = MAX_DIST;
        visited[i] = false;
        pRoute[i] = 0;
    }

    pDist[start] = 0;

    while (true) { 
        i = 0;
        //���������Ƃ̂Ȃ����[�g�𒲂ׂ�
        while (i < ALL_WAYPOINT) {
            if (visited[i] == 0) {
                break; 
            }
            i++;
        }

        //�S�Č��I������甲����
        if (i == ALL_WAYPOINT) { 
            break; 
        }

        //���Z���n�_��T��
        for (j = i + 1; j < ALL_WAYPOINT; j++) { 
            if ((visited[j] == 0) && (pDist[j] < pDist[i])) {
                i = j;
            }
        }

        sPoint = i;
        //�K�ꂽ���Ƃ��L�^
        visited[sPoint] = true; 

        //�ŒZ�o�H�����ւ�
        for (j = 0; j < ALL_WAYPOINT; j++) {
            if ((edgeCost[sPoint][j] > 0) && (visited[j] == 0)) {
                newDist = pDist[sPoint] + edgeCost[sPoint][j];
                if (newDist < pDist[j]) {
                    pDist[j] = newDist;
                    pRoute[j] = sPoint;
                }
            }
        }
    }
 
    //�ŒZ�o�H�����Ă���
    j = 0;
    i = goal;
    while (i != start) {
        sRoute[j] = i;
        i = pRoute[i];
        j++;
    }
    sRoute[j] = start;

    //���݈ʒu��1���ڕW�ɐݒ�
    if (j > 0)
    {
        return sRoute[j - ADJACENT_NUM];
    }
    else
    {
        return sRoute[j];
    }

}

//�A�j���[�V����
void Enemy::animation()
{
    //�A�j���[�V�����ɂ����W������C������
    MV1SetFrameUserLocalMatrix(enemyModel, 0, MGetTranslate(ADJUST_ENEMY_POSITION_ANIMATION));

    MV1SetPosition(enemyModel, VSub(position, ADJUST_ENEMY_POSITION_Y));

    MV1SetRotationXYZ(enemyModel, VGet(DX_PI_F / QUARTAR_ANGLE / HALF * ADJUST_ENEMY_ROTATION, nowRotation * DX_PI_F / HALF_ANGLE, 0));

    // �Đ����Ԃ�i�߂�
    animationPlayTime += ANIMATION_SPEED;

    // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
    if (animationPlayTime >= animationTotalTime)
    {
        animationPlayTime = 0.0f;
    }

    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(enemyModel, attachAnimationIndex, animationPlayTime);
}

