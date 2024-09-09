#pragma once

class ControlGemObject;
class Player;
class Collision;

class CheckClear
{
private:
    bool clearFlg_1;                    //クリア用のフラグ一つ目
    bool clearFlg_2;                    //クリア用のフラグ二つ目
    int remainingControlGemObject;      //残りの宝石の数
    int goalModel;                      //ゴールのモデル
    int goalModelRotation;              //ゴールモデルの回転量

public:
    CheckClear();
    ~CheckClear();
    void initialize();      //初期化
    void checkClearConditions_1(ControlGemObject ControlGemObject);                 //宝石をすべて集めているか判定
    void checkClearConditions_2(Player player, int& scene,Collision collision);     //ゴールまでたどり着いているか判定
    void rollingModel();    //ゴールのモデルを回転

    //ゲッター関数
    bool getClearFlg_1() { return clearFlg_1; }
    bool getClearFlg_2() { return clearFlg_2; }
    int getRemainingControlGemObject(){return remainingControlGemObject; }
    int getGoalModel() { return goalModel; }

private:
    //定数
    const VECTOR GOAL_MODEL_SIZE = VGet(0.01f, 0.01f, 0.01f);   //ゴールモデルのサイズ

};

