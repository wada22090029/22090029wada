#include"DxLib.h"
#include"ConstantStrage.h"
#include"Player.h"
#include"Stage.h"
#include"Enemy.h"
#include"ControlGemObject.h"
#include"HelpfulItems.h"
#include"SceneStrage.h"
#include"ConstantStrage.h"
#include"ControlSound.h"
#include "Collision.h"


Collision::Collision()
{
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            HitPolyDim[i][j].HitNum = 0;
        }
    }
}

Collision::~Collision()
{
    
}

//初期化
void Collision::initialize()
{
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            HitPolyDim[i][j].HitNum = 0;
        }
    }
}

//ステージとプレイヤーの当たり判定
void Collision::stageCollision(Stage stage,Player& player)
{
    //現在の座標を保存
    player.setKeepPosition(VAdd(player.getPosition(), player.getMoveVector()));

    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            // モデル全体のコリジョン情報を構築
            MV1SetupCollInfo(stage.getStageModel(i, j), FRAME_INDEX, DIV_NUM, DIV_NUM, DIV_NUM);
            // モデルと球との当たり判定
            HitPolyDim[i][j] = MV1CollCheck_Sphere(stage.getStageModel(i, j), FRAME_INDEX, VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()), SPHERE_PLAYER_R);
        }
    }

    VECTOR slideVector; //移動量
    bool hit = false;   //当たったかどうか
    int counter = 0;    //試行回数制限用カウンター

    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            // 当たったかどうかで処理を分岐
            if (HitPolyDim[i][j].HitNum >= HIT)
            {
                    hit = true;

                    // 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
                    slideVector = VCross(player.getMoveVector(), HitPolyDim[i][j].Dim->Normal);

                    // 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
                    // 元の移動成分から壁方向の移動成分を抜いたベクトル
                    slideVector = VCross(HitPolyDim[i][j].Dim->Normal, slideVector);

                    // それを移動前の座標に足したものを新たな座標とする
                    player.setKeepPosition(VAdd(player.getPosition(), slideVector));
            }
            // 当たり判定情報の後始末
            MV1CollResultPolyDimTerminate(HitPolyDim[i][j]);
        }

    }

    //めり込んでいたら押し出す
    for (int h = 0;h < CONFIRMATION_COUNTER; h++)
    {
        for (int i = 0; i < STAGE_SIZE; i++)
        {
            for (int j = 0; j < STAGE_SIZE; j++)
            {
                // モデルと球との当たり判定
                HitPolyDim[i][j] = MV1CollCheck_Sphere(stage.getStageModel(i, j), FRAME_INDEX, VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()), SPHERE_PLAYER_R);
            }
        }

        if (hit == true)
        {
            for (int i = 0; i < STAGE_SIZE; i++)
            {
                for (int j = 0; j < STAGE_SIZE; j++)
                {
                    //当たっている限り
                    while (HitPolyDim[i][j].HitNum >= HIT)
                    {
                        counter++;
                        //押し出し
                        player.setKeepPosition(VAdd(player.getKeepPosition(), VScale(HitPolyDim[i][j].Dim->Normal, PUSH_VECTOR)));
                        player.setKeepPosition(VGet(player.getKeepPositionX(), INITIALIZE_PLAYER_POSITION_Y, player.getKeepPositionZ()));
                        // 当たらなくなったor移動不可なら脱出
                        if (HitCheck_Sphere_Triangle(VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()),SPHERE_PLAYER_R,
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_1],
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_2],
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_3]) == FALSE || 
                            counter > MAX_REPEAT_COUNT)
                        {
                            counter = 0;
                            break;
                        }
                    }
                    // 当たり判定情報の後始末
                    MV1CollResultPolyDimTerminate(HitPolyDim[i][j]);
                }
            }
        }
    }
    
    //座標を反映
    player.setPosition(player.getKeepPosition());
    
    //プレイヤーの移動量をリセット
    player.resetMoveVector();
}

//プレイヤーと敵との当たり判定
void Collision::checkHitEnemy(Player player, int& scene,Enemy enemy, ControlSound& sound)
{
    //距離を出す
    VECTOR Vec = VSub(enemy.getPosition(), player.getPosition());
    //一定範囲内に入ったらゲームオーバー画面へ
    if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_ENEMY_R)
    {
        sound.playSound(deadSE);
        scene = resultScene;
    }
}

//プレイヤーとクリア用アイテムの宝石との当たり判定
void Collision::checkHitControlGemObject(Player player,ControlGemObject& controlGemObject, HelpfulItems helpfulItems,ControlSound& sound)
{
    float itemBoost = 0;
    //磁石を使っていたら取得範囲拡大
    if (helpfulItems.getUsingItem(absorbItem) == true)
    {
        itemBoost = ADD_ABSORB_RANGE;
    }
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            //距離を出す
            VECTOR Vec = VSub(controlGemObject.getPosition(i,j), player.getPosition());
            //範囲内に入っていたら取得
            if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_GEM_R + itemBoost && controlGemObject.getObtainedObject(i,j) == false)
            {
                sound.playSound(getObjectSE);
                controlGemObject.setObtainedObject(i,j,true);
            }
        }
    }
}

//プレイヤーとお助けアイテムとの当たり判定
void Collision::checkHitHelpfulItem(Player player,HelpfulItems& helpfulItems, ControlSound& sound)
{
    for (int i = 0; i < ALL_HELPFULL_ITEM_KIND; i++)
    {
        //距離を出す
        VECTOR Vec = VSub(helpfulItems.getItemPosition(i), player.getPosition());
        //範囲内に入っていたら取得
        if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_HELPFUL_ITEM_R && helpfulItems.getAlreadyTakenItem(i) == false)
        {
            sound.playSound(getObjectSE);
            helpfulItems.setHavingItem(i);
        }
    }
}

//プレイヤーとゴールエリアとの当たり判定
bool Collision::checkHitGoalArea(Player player)
{
    //距離を出す
    VECTOR Vec = VSub(GOAL_POSITION, player.getPosition());
    //範囲内に入っていたらゴール
    if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_GOAL_AREA_R)
    {
        return true;
    }
    else
    {
        return false;
    }
}
