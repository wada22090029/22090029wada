#pragma once

class CheckDevice;
class ControlSound;

class Pause
{
private:
    int select;             //選択
    int pauseTextImg;       //ポーズテキスト画像
    bool pushFlg;           //連続で押せないようにするためのフラグ
    bool pushEscapeKeyFlg;  //エスケープキーを押したかどうか
    bool resetFlg;          //リセットするか
public:
    Pause();
    ~Pause();
    void initialize();  //初期化
    void selectCommand(int& scene,CheckDevice checkDevice, ControlSound& sound);    //選択肢処理
    void controlPauseKey(int& scene, CheckDevice checkDevice, ControlSound& sound); //ポーズキーが押されたときの処理

    //ゲッター関数
    int getSelectCommand() { return select; }
    int getPauseText() { return pauseTextImg; }
    bool getResetFlg() { return resetFlg; }
};

