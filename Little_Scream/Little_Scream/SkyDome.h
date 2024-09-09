#pragma once

class Player;

class SkyDome
{
private:
    int model;      //スカイドームモデル

public:
    SkyDome();
    ~SkyDome();
    void setPosition(Player player);    //座標をセット

    //ゲッター関数
    int getModel() { return model; }
};

