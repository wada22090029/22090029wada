#pragma once

static const int STAGE_SIZE = 21;  //マップサイズ縦横

const float STAGE_CHIP_SIZE = 4.0f;  //ステージのモデル1タイルサイズ

//ウィンドウサイズ
const int WINDOW_SIZE_WIDTH = 1920;
const int WINDOW_SIZE_HEIGHT = 1080;

const int COLOR_BIT = 32;//カラービット

//デバイス判定
const int DEVICE_CONTROLLER = 1;
const int DEVICE_KEYBORD = 0;

const int ALL_HELPFULL_ITEM_KIND = 4;//お助けアイテムの種類
const float MAX_ANGLE = 360.0f;      //360度
const float HALF_ANGLE = 180.0f;     //180度
const float QUARTAR_ANGLE = 90.0f;   //90度
const int HALF = 2;                  //2分の一にする
const VECTOR GOAL_POSITION = VGet(40.0f, 8.0f, -40.0f);     //ゴールの座標
const int TUTORIAL_KIND = 2;    //チュートリアルの総ページ数
const int MIN_FONT = 0;			//小さいフォント 番号
const int MAX_FONT = 1;			//大きいフォント 番号

//タイトルで選べるコマンド
enum TitleCommand {
    playGame,
    endGame
};

//リザルトとポーズ画面で選べるコマンド
enum ResultAndPauseCommand {
    retry,
    returnTitle,
    continueGame = -1   //このコマンドのみポーズで使用
};

//アイテムの名前
enum ItemName {
    stunItem,
    dashItem,
    absorbItem,
    teleportItem,
    nothing
};

//音関連のストレージ
enum soundStrage {
	titleBGM,
	goalBGM,
	playerDashSE,
	enemyDashSE,
	selectSE,
	decisionSE,
	deadSE,
	getObjectSE,
	itemUseSE
};