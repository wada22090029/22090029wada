#pragma once
class Player;
class Light
{
private:
    int playerLightHandle; //ライトハンドル
public:
    Light();
    ~Light();
    void setPlayerLight(Player player);     //ライトを配置
    void deletePlayerLight() { DeleteLightHandle(playerLightHandle); }      //ライトを削除

private:
    const float LIGHT_RANGE = 40.0f;    //ライトが届く距離
    const float ATTAN_1 = 0.05f;        //距離減衰 1
    const float ATTAN_2 = 0.02f;        //距離減衰 2
    const float ATTAN_3 = 0.0002f;      //距離減衰 3
};

