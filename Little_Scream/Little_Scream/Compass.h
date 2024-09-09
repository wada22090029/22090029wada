#pragma once

class Player;
class ControlGemObject;
class CheckClear;

class Compass
{
private:
	VECTOR minDistance;			//目標との最小距離
	VECTOR pos;					//コンパスの座標
	bool target[STAGE_SIZE][STAGE_SIZE];	//目標とするオブジェクト
	float objectDirection;		//オブジェクトの向く方向
	int model;					//オブジェクトモデルモデル
public:
	Compass();
	~Compass();
	//目標とするオブジェクトまでの距離と角度を求める
	void findObjectDistanceAndDirection(Player player, ControlGemObject ControlGemObject, CheckClear checkClear);

	//ゲッター関数
	float getObjectDirection() { return objectDirection; }
	int getModel() { return model; }
private:
	//定数
	const VECTOR INITIALIZE_MIN_DISTANCE = VGet(1000.0f, 1000.0f, 1000.0f);	//最小目標距離初期値
	const float INITIALIZE_COMPAS_POSITION_Y = 5.0f;						//コンパスy座標の初期値
	const VECTOR COMPAS_MODEL_SIZE = VGet(0.001f, 0.001f, 0.001f);			//コンパスモデルサイズ
};

