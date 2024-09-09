#pragma once

class Stage;
class Player;
class Enemy;
class ControlGemObject;
class HelpfulItems;
class ControlSound;

class Collision
{
private:
    MV1_COLL_RESULT_POLY_DIM HitPolyDim[STAGE_SIZE][STAGE_SIZE];    //ステージと当たったかどうか
public:
    Collision();
    ~Collision();
    void initialize();      //初期化
    void stageCollision(Stage stage,Player& player);    //ステージとプレイヤーの当たり判定
    void checkHitEnemy(Player player, int& scene, Enemy enemy, ControlSound& sound);        //プレイヤーと敵との当たり判定
    void checkHitControlGemObject(Player player, ControlGemObject& controlGemObject, HelpfulItems helpfulItems,ControlSound& sound);        //プレイヤーとクリア用アイテムの宝石との当たり判定
    void checkHitHelpfulItem(Player player, HelpfulItems& helpfulItem, ControlSound& sound);        //プレイヤーとお助けアイテムとの当たり判定
    bool checkHitGoalArea(Player player);       //プレイヤーとゴールエリアとの当たり判定
private:
    //定数
    const int HIT = 1;                      //ヒット時の値
    const int FRAME_INDEX = -1;             //フレーム番号
    const float PUSH_VECTOR = 0.01f;        //押し出し量
    const int DIV_NUM = 2;                  //空間分割数
    const float SPHERE_PLAYER_R = 0.9f;     //プレイヤー当たり判定球の半径
    const float SPHERE_ENEMY_R = 1.5f;      //敵当たり判定球の半径
    const float SPHERE_GEM_R = 0.2f;        //クリア用アイテムの宝石　当たり判定球の半径
    const float SPHERE_HELPFUL_ITEM_R = 0.8f;       //お助けアイテム当たり判定球の半径
    const float SPHERE_GOAL_AREA_R = 2.5f;          //ゴールエリア当たり判定球の半径
    const float INITIALIZE_PLAYER_POSITION_Y = 6.0f;//プレイヤーの初期座標
    const float PLAYER_COLLIDION_POSITION_Y = 5.0f;
    const int CONFIRMATION_COUNTER = 5;     //確認する際に繰り返す数
    const int MAX_REPEAT_COUNT = 10000;     //最大繰り返し数
    const int HIT_POLY_COORDINATE_1 = 0;    //当たったポリゴンの頂点1
    const int HIT_POLY_COORDINATE_2 = 1;    //当たったポリゴンの頂点2
    const int HIT_POLY_COORDINATE_3 = 2;    //当たったポリゴンの頂点3
    const float ADD_ABSORB_RANGE = 7.0f;         //取得範囲増加量
};

