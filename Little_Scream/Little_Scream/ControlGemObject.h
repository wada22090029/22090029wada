#pragma once

class Stage;
class Player;

class ControlGemObject
{
private:
    VECTOR objectPosition[STAGE_SIZE][STAGE_SIZE];  //宝石の座標
    bool obtainedObject[STAGE_SIZE][STAGE_SIZE];    //宝石を取得したか
    int objectModelOriginal;                        //宝石のモデル　コピー元
    int objectModel[STAGE_SIZE][STAGE_SIZE];        //宝石のモデル配列　コピー先
    int objectModelRotation;                        //宝石の回転量
public:
    ControlGemObject();
    ~ControlGemObject();
    void initialize(Stage stage);   //初期化
    void rollingModel();            //回転

    //ゲッター関数
    VECTOR getPosition(const int i, const  int j) { return objectPosition[i][j]; }
    bool getObtainedObject(const int i, const  int j) { return obtainedObject[i][j]; }
    void setObtainedObject(const int i, const  int j, const  bool flg) { obtainedObject[i][j] = flg; }
    int getModel(const int i, const  int j) { return objectModel[i][j]; }
private:
    //定数
    const VECTOR GEM_OBJECT_SCALE = VGet(0.005f, 0.005f, 0.005f);   //宝石オブジェクトサイズ
    const float INITIALIZE_GEM_POSITION_Y = 5.5f;                   //宝石初期位置　Y座標
    const int LEFT_SIDE = 0;         //左端
    const int RIGHT_SIDE = 20;       //右端
    const int UP_SIDE = 0;           //上
    const int DOWN_SIDE = 20;        //下

};

