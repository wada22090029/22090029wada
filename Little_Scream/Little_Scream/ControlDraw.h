#pragma once
class Stage;
class Player;
class Enemy;
class ControlGemObject;
class Title;
class Result;
class Pause;
class CheckClear;
class HelpfulItems;
class ControlFade;
class CheckClear;
class Tutorial;
class CheckDevice;
class Compass;
class SkyDome;
class ControlFont;

class ControlDraw
{
public:
    //各シーン描画
    void drawPlay(Stage stage,Player player,Enemy enemy,ControlGemObject controlGemObject,HelpfulItems, ControlFade& controlFade, CheckClear checkClear,Tutorial tutorial,CheckDevice checkDevice, Compass compass, SkyDome skyDome,ControlFont font);
    void drawTitle(Title title, ControlFade& controlFade);
    void drawResult(Result result, CheckClear checkClear, ControlFade& controlFade);
    void drawPause(Pause pause, ControlFade& controlFade);
private:
    //定数
    //プレイシーン
    //アイテム背景のウィンドウ画像
    const int ITEM_BACK_WINDOW_X = 20;
    const int ITEM_BACK_WINDOW_Y = 800;
    //残りの宝石数のテキスト
    const int REMINING_GEM_TEXT_X = 230;
    const int REMINING_GEM_TEXT_Y = 850;
    //アイテム画像
    const int ITEM_IMG_X_1 = 50;
    const int ITEM_IMG_X_2 = 150;
    const int ITEM_IMG_Y_1 = 900;
    const int ITEM_IMG_Y_2 = 1000;
    //チュートリアルの“次へ進む”テキスト背景
    const int TUTORIAL_TEXT_BOX_X_1 = 780;
    const int TUTORIAL_TEXT_BOX_X_2 = 1080;
    const int TUTORIAL_TEXT_BOX_Y_1 = 980;
    const int TUTORIAL_TEXT_BOX_Y_2 = 1040;
    const int TUTORIAL_TEXT_BOX_ADD_X = 6;
    //チュートリアルの“次へ進む”テキスト
    const int TUTORIAL_TEXT_X = 800;
    const int TUTORIAL_TEXT_Y = 1000;
    //チュートリアルの“次へ進む”テキストにかぶせるBOX
    const int TITLE_TIMG_X_1 = 450;
    const int TITLE_TIMG_X_2 = 1500;
    const int TITLE_TIMG_Y_1 = 0;
    const int TITLE_TIMG_Y_2 = 800;

    //タイトルシーン
    //タイトルシーンからプレイシーンを選択
    const int TITLE_SELECT_PLAY_X_1 = 70;
    const int TITLE_SELECT_PLAY_X_2 = 310;
    const int TITLE_SELECT_PLAY_Y_1 = 660;
    const int TITLE_SELECT_PLAY_Y_2 = 760;
    //タイトルシーンからエンドシーンを選択
    const int TITLE_SELECT_END_X_1 = 70;
    const int TITLE_SELECT_END_X_2 = 610;
    const int TITLE_SELECT_END_Y_1 = 810;
    const int TITLE_SELECT_END_Y_2 = 910;

    //リザルトシーン
    //クリア時
    //リザルトシーンからセレクトシーンを選択
    const int RESULT_CLEAR_SELECT_PLAY_X_1 = 860;
    const int RESULT_CLEAR_SELECT_PLAY_X_2 = 1060;
    const int RESULT_CLEAR_SELECT_PLAY_Y_1 = 620;
    const int RESULT_CLEAR_SELECT_PLAY_Y_2 = 690;
    //リザルトシーンからタイトルシーンを選択
    const int RESULT_CLEAR_SELECT_TITLE_X_1 = 690;
    const int RESULT_CLEAR_SELECT_TITLE_X_2 = 1230;
    const int RESULT_CLEAR_SELECT_TITLE_Y_1 = 740;
    const int RESULT_CLEAR_SELECT_TITLE_Y_2 = 810;
    //ゲームオーバー時
    //リザルトシーンからプレイシーンを選択
    const int RESULT_MISS_SELECT_PLAY_X_1 = 850;
    const int RESULT_MISS_SELECT_PLAY_X_2 = 1050;
    const int RESULT_MISS_SELECT_PLAY_Y_1 = 530;
    const int RESULT_MISS_SELECT_PLAY_Y_2 = 600;
    //リザルトシーンからタイトルシーンを選択
    const int RESULT_MISS_SELECT_TITLE_X_1 = 700;
    const int RESULT_MISS_SELECT_TITLE_X_2 = 1250;
    const int RESULT_MISS_SELECT_TITLE_Y_1 = 660;
    const int RESULT_MISS_SELECT_TITLE_Y_2 = 730;

    //ポーズシーン
    //ポーズシーンからプレイシーンを選択
    const int PAUSE_SELECT_PLAY_X_1 = 750;
    const int PAUSE_SELECT_PLAY_X_2 = 1120;
    const int PAUSE_SELECT_PLAY_Y_1 = 520;
    const int PAUSE_SELECT_PLAY_Y_2 = 620;
    //ポーズシーンからリトライを選択
    const int PAUSE_SELECT_RETRY_X_1 = 750;
    const int PAUSE_SELECT_RETRY_X_2 = 1000;
    const int PAUSE_SELECT_RETRY_Y_1 = 635;
    const int PAUSE_SELECT_RETRY_Y_2 = 735;
    //ポーズシーンからタイトルシーンを選択
    const int PAUSE_SELECT_TITLE_X_1 = 750;
    const int PAUSE_SELECT_TITLE_X_2 = 1230;
    const int PAUSE_SELECT_TITLE_Y_1 = 755;
    const int PAUSE_SELECT_TITLE_Y_2 = 855;

    //カラー
    const int COLOR_WHITE = GetColor(255,255,255);       //白
    const int COLOR_TEXT_BOX = GetColor(120, 120, 120);  //テキストにかぶせる時の色
    const int COLOR_TITLE_BACK = GetColor(23, 23, 22);   //タイトル背景の色
    const int PAUSE_BACK_FADE = 180;                    //ポーズ画面背景のフェード
    const int TUTORIAL_TEXT_FADE_FADE = 120;            //チュートリアルのテキスト背景と、かぶせるBOXのフェード
};

