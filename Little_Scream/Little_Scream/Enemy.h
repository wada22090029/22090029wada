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
    static int edgeCost[][ALL_WAYPOINT];        //移動コスト用配列
    int enemyModel;             //敵モデル
    VECTOR position;            //敵座標
    VECTOR waypointArray[ALL_WAYPOINT];  //ウェイポイント座標保存用
    VECTOR waypointPosition;             //ウェイポイント個別座標を求める際に使用
    int targetIndex;                     //目標地点
    int attachAnimationIndex;            //敵のアニメーション
    float animationTotalTime;            //アニメーションの総時間
    float animationPlayTime;             //現在のアニメーションの再生時間
    VECTOR targetWayPoint;               //目標とするウェイポイント
    bool goalFlg;                        //目標地点についたか判定
    float targetRotation;                //敵の目標とする回転量
    float nowRotation;                   //敵の現在の回転量


public:
    Enemy();
    ~Enemy();
    void initialize();      //初期化
    void createWaypointAndEdge(Stage stage, const VECTOR targetPos);      //ウェイポイントと移動コスト作成
    void updatePosition(Stage stage,const VECTOR targetPos, Player player, HelpfulItems helpfulItems,ControlSound& sound);      //敵の座標更新
    int searchNearestPoint(const VECTOR& pos);                  //最も近いウェイポイントを探す
    int dijkstra(Stage stage,const int start,const int goal);   //ダイクストラ法で経路探索
    void animation();                                           //アニメーションを付ける

    //ゲッター関数
    int getEdgeCost(const int i,const int j) { return edgeCost[i][j]; }
    VECTOR getWayPointPos(const int& index);
    VECTOR getWaypointArray(const int i) { return waypointArray[i]; }
    VECTOR getPosition() { return position; }
    int getModel() { return enemyModel; }

private:    
    //定数
    const float ROTATION_RANGE = 5.625f;        //敵のの回転速度
    const float ENEMY_SPEED = 0.2f;             //敵の移動速度
    const int TRUE_COST = 1;                    //通れる場所の移動コスト
    const int FALSE_COST = -1;                  //通れない場所の移動コスト
    const float TARGET_RANGE = 0.15f;           //目標地点についたと認識する範囲
    const int MAX_DIST = 99999;                 //最大移動手数
    const float ANIMATION_SPEED = 0.55f;        //アニメーション再生速度
    const VECTOR INITIALIZE_WAYPOINT_POSITION = VGet(0, 5.5f, 0);       //ウェイポイント初期座標
    const VECTOR INITIALIZE_ENEMY_POSITION = VGet(0.0f, 5.5f, 0.0f);          //敵初期座標
    const VECTOR ENEMY_MODEL_SCALE = VGet(0.015f, 0.015f, 0.015f);      //敵モデルサイズ
    const VECTOR ADJUST_ENEMY_POSITION_ANIMATION = VGet(0.0f, -25.0f, 0.0f);      //アニメーション使用時の座標調整値
    const VECTOR ADJUST_ENEMY_POSITION_Y = VGet(0, 1.0f, 0);
    const int ADJUST_ENEMY_ROTATION = -5;       //アニメーションによる敵の回転両調整
    const int MINDISTANCE_SHIFT = 30;           //minDistanceのシフト数
    const int ADJACENT_NUM = 1;                 //端から隣接した物を取得するための定数
};

