#pragma once

class CheckDevice;
class ControlSound;

class Result
{
private:
    int select;         //選択
    int gameOverImg;    //ゲームオーバー時の画像
    int gameClearImg;   //ゲームクリア時の画像
    bool pushFlg;       //連続で押せないようにするためのフラグ
public:
    Result();
    ~Result();
    void selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound);     //選択処理

    //ゲッター関数
    int getSelectCommand() { return select; }
    int getGameOverImg() { return gameOverImg; }
    int getGameClearImg() { return gameClearImg; }
};

