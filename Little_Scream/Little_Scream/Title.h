#pragma once

class CheckDevice;
class ControlSound;

class Title
{
private:
    int select;         //選択肢
    int titleImg;       //タイトル画像
    int menuTextImg;    //メニュー画面のテキスト画像
    bool pushFlg;       //連続で押せないようにするためのフラグ
public:
    Title();
    ~Title();
    void selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound);     //選択時処理

    //ゲッター関数
    int getSelectCommand() { return select; }
    int getTitleImg() { return titleImg; }
    int getMenuTextImg() { return menuTextImg; }
};

