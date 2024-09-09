#pragma once

class CheckDevice;
class ControlSound;

class HelpfulItems
{
private:
    static const int ITEM_KIND = 4;                 //アイテムの種類
    static const int NOTHING_NUM = 1;               //背景ウィンドウ表示用
    bool checkHavingItem;                           //現在アイテムを持っているかどうか
    int havingItem;                                 //現在持っているアイテム
    int itemTimer[ITEM_KIND];                       //アイテム使用時間計測
    int itemModel[ITEM_KIND];                       //アイテムモデル
    int itemModelRotation;                          //アイテム回転量   
    int itemImg[ITEM_KIND + NOTHING_NUM];           //アイテム画像
    int itemBackWindowImgKeybord;                   //アイテム画像背景　キーボード用
    int itemBackWindowImgController;                //アイテム画像背景　コントローラー用
    bool usingItem[ITEM_KIND];                      //アイテム使用フラグ
    bool usedItem[ITEM_KIND];                       //アイテムを過去に使用したかのフラグ
    bool alreadyTakenItem[ITEM_KIND];               //すでに手に入れたアイテムか
    VECTOR itemPos[ITEM_KIND];                      //アイテムの座標
public:
    HelpfulItems();
    ~HelpfulItems();
    void initialize();      //初期化
    void useItems(CheckDevice checkDevice,ControlSound& sound);     //アイテム使用
    void rollingModel();    //アイテムモデル回転
    void setHavingItem(int i)   //取得したアイテムをセット
    {
        havingItem = i;
        alreadyTakenItem[i] = true;
    }

    //ゲッター関数
    VECTOR getItemPosition(int i) { return itemPos[i]; }
    int getHavingItem() { return havingItem; }
    bool getAlreadyTakenItem(int i) { return alreadyTakenItem[i]; }
    bool getUsingItem(int i) { return usingItem[i]; }
    bool getUsedItem(int i) { return usedItem[i]; }
    int getModel(int i) { return itemModel[i]; }
    int getImg(int i) { return itemImg[i]; }
    int getItemBackWindowImgKeybord() { return itemBackWindowImgKeybord; }
    int getItemBackWindowImgController() { return itemBackWindowImgController; }
private:
    const VECTOR INITIALIZE_ITEM_POSITION = VGet(0, 5.5f, 0);   //初期座標
    const VECTOR ITEM_POSITION_1 = VGet(0, 5.5f, 0);            //端　1
    const VECTOR ITEM_POSITION_2 = VGet(80, 5.5, 0);            //端　2
    const VECTOR ITEM_POSITION_3 = VGet(0, 5.5, -80);           //端　3
    const VECTOR ITEM_POSITION_4 = VGet(80, 5.5, -80);          //端　4
    const VECTOR ITEM_MODEL_SCALE = VGet(0.01f, 0.01f, 0.01f);  //モデルサイズ
    const int STUN_TIME = 200;        //スタンさせる時間
    const int DASH_TIME = 300;        //ダッシュできる時間
    const int ABSORB_TIME = 300;      //取得範囲上昇時間
    const int TELEPORT_TIME = 1;      //テレポートにかかる時間
    const int MAX_RANDOM = 3;         //ランダム最大数
};

