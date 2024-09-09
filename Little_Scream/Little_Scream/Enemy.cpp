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

//初期化
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
    //ウェイポイント作成
    for (int i = 0; i < ALL_WAYPOINT; i++) {
            waypointPosition.x =  STAGE_CHIP_SIZE * (i % STAGE_SIZE);
            waypointPosition.z =  -STAGE_CHIP_SIZE * (i / STAGE_SIZE);
            waypointArray[i] = waypointPosition;
    }

    //エッジ
    //初期化.
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

    //エッジ設定 該当箇所だけ数値をマイナスにする
    for (int i = ADJACENT_NUM; i < STAGE_SIZE - ADJACENT_NUM; i++) {
        for (int j = ADJACENT_NUM; j < STAGE_SIZE - ADJACENT_NUM; j++) {
            if (stage.getMap(i, j) == 0)
            {
                edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j] = FALSE_COST; //同位置
                edgeCost[i * STAGE_SIZE + j - ADJACENT_NUM][i * STAGE_SIZE + j] = edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j - ADJACENT_NUM] = FALSE_COST; //左の辺
                edgeCost[i * STAGE_SIZE + j][i * STAGE_SIZE + j + ADJACENT_NUM] = edgeCost[i * STAGE_SIZE + j + ADJACENT_NUM][i * STAGE_SIZE + j] = FALSE_COST; //右の辺
                edgeCost[(i - ADJACENT_NUM) * STAGE_SIZE + j][i * STAGE_SIZE + j] = edgeCost[i * STAGE_SIZE + j][(i - ADJACENT_NUM) * STAGE_SIZE + j] = FALSE_COST; //上の辺
                edgeCost[i * STAGE_SIZE + j][(i + ADJACENT_NUM) * STAGE_SIZE + j] = edgeCost[(i + ADJACENT_NUM) * STAGE_SIZE + j][i * STAGE_SIZE + j] = FALSE_COST; //下の辺
            }
        }
    }

}


//位置更新.
void Enemy::updatePosition(Stage stage,const VECTOR targetPos,Player player, HelpfulItems helpfulItems,ControlSound& sound)
{
    //目標のウェイポイントは見つかっている
    if (goalFlg == true) {
        //次のウェイポイントを探す
        const int playerPoint = searchNearestPoint(targetPos);
        if (stage.getMap(playerPoint / STAGE_SIZE, playerPoint % STAGE_SIZE) != 0)
        {
            //ダイクストラ法でターゲットの位置を探す
            targetIndex = dijkstra(stage, targetIndex, playerPoint);
            //最も近いウェイポイントを探す
            targetWayPoint = getWayPointPos(targetIndex);
        }
        goalFlg = false;
    }

    //スタンアイテムが使われていなければ
    if (helpfulItems.getUsingItem(stunItem) == false)
    {
        sound.playSoundLoop(enemyDashSE);
        //移動処理+回転処理
        if (targetWayPoint.x + TARGET_RANGE > position.x && targetWayPoint.x - TARGET_RANGE < position.x)
        {
            //z軸移動
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
            //x軸移動
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

    //回転角度を求める
    float rotationDifference = targetRotation - nowRotation;

    //方向転換時にスムーズに回転
    //最大で360度にする
    if (nowRotation > MAX_ANGLE)
    {
        nowRotation = 0.0f;
    }
    if (nowRotation < 0.0f)
    {
        nowRotation = MAX_ANGLE;
    }

    //回転時目標までの最短距離に近い方向に回転
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

    //アニメーション
    animation();
}

//指定位置から一番近いウェイポイントを探す.
int Enemy::searchNearestPoint(const VECTOR& pos)
{
    const int waypointNum = ALL_WAYPOINT;
    if (!(waypointArray && (waypointNum > 0))) { return -1; }

    //距離で直近かどうか判断.
    int     nextPoint = -1;
    float   minDistance = (float)(1 << MINDISTANCE_SHIFT);
    for (int i = 0; i < waypointNum; i++) {
        //距離を出す
        VECTOR distanceBetween = VSub(waypointArray[i], pos);
        const float distance = sqrtf(distanceBetween.x * distanceBetween.x + distanceBetween.z * distanceBetween.z);
        //近いほうをminDistanceへ
        if (distance > minDistance) { continue; }
        minDistance = distance;
        nextPoint = i;
    }

    return nextPoint;
}

//ウェイポイントの位置を取得.
VECTOR Enemy::getWayPointPos(const int& index)
{
    VECTOR tmp;
    tmp.x = 0.0f;
    tmp.z = 0.0f;

    const int waypointNum = ALL_WAYPOINT;
    //異常がない限りは
    if (!(waypointArray && (waypointNum > 0))) { return tmp; }
    if (0 > index || index >= waypointNum) { return tmp; }

    return waypointArray[index];
}

//ダイクストラ法
int Enemy::dijkstra(Stage stage,const int start,const int goal)
{
    int pDist[ALL_WAYPOINT];//出発地から各地点までの最短距離
    bool visited[ALL_WAYPOINT];//訪れた地点を記録
    int pRoute[ALL_WAYPOINT];//各地点の最短距離の確定状態
    int sRoute[ALL_WAYPOINT];//最短経路上の地点の地点番号
    int sPoint, newDist, i, j;//一時保存用とループ用変数

    //初期化
    for (i = 0; i < ALL_WAYPOINT; i++) {
        sRoute[i] = -1;
        pDist[i] = MAX_DIST;
        visited[i] = false;
        pRoute[i] = 0;
    }

    pDist[start] = 0;

    while (true) { 
        i = 0;
        //いったことのないルートを調べる
        while (i < ALL_WAYPOINT) {
            if (visited[i] == 0) {
                break; 
            }
            i++;
        }

        //全て見終わったら抜ける
        if (i == ALL_WAYPOINT) { 
            break; 
        }

        //より短い地点を探す
        for (j = i + 1; j < ALL_WAYPOINT; j++) { 
            if ((visited[j] == 0) && (pDist[j] < pDist[i])) {
                i = j;
            }
        }

        sPoint = i;
        //訪れたことを記録
        visited[sPoint] = true; 

        //最短経路を入れ替え
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
 
    //最短経路を入れていく
    j = 0;
    i = goal;
    while (i != start) {
        sRoute[j] = i;
        i = pRoute[i];
        j++;
    }
    sRoute[j] = start;

    //現在位置の1つ先を目標に設定
    if (j > 0)
    {
        return sRoute[j - ADJACENT_NUM];
    }
    else
    {
        return sRoute[j];
    }

}

//アニメーション
void Enemy::animation()
{
    //アニメーションによる座標ずれを修正する
    MV1SetFrameUserLocalMatrix(enemyModel, 0, MGetTranslate(ADJUST_ENEMY_POSITION_ANIMATION));

    MV1SetPosition(enemyModel, VSub(position, ADJUST_ENEMY_POSITION_Y));

    MV1SetRotationXYZ(enemyModel, VGet(DX_PI_F / QUARTAR_ANGLE / HALF * ADJUST_ENEMY_ROTATION, nowRotation * DX_PI_F / HALF_ANGLE, 0));

    // 再生時間を進める
    animationPlayTime += ANIMATION_SPEED;

    // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
    if (animationPlayTime >= animationTotalTime)
    {
        animationPlayTime = 0.0f;
    }

    // 再生時間をセットする
    MV1SetAttachAnimTime(enemyModel, attachAnimationIndex, animationPlayTime);
}

