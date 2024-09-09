#include"DxLib.h"
#include"CheckDevice.h"
#include"ConstantStrage.h"
#include"ControlSound.h"
#include "HelpfulItems.h"

HelpfulItems::HelpfulItems()
{
    checkHavingItem = false;
    havingItem = nothing;
    for (int i = 0; i < ITEM_KIND; i++)
    {
        itemTimer[i] = 0;
        usingItem[i] = false;
        usedItem[i] = false;
        alreadyTakenItem[i] = false;
        itemPos[i] = INITIALIZE_ITEM_POSITION;
    }
    itemModel[stunItem] = MV1LoadModel("../model/ItemModel/stun_item.mv1");
    itemModel[dashItem] = MV1LoadModel("../model/ItemModel/speedup_Item.mv1");
    itemModel[absorbItem] = MV1LoadModel("../model/ItemModel/magnet.mv1");
    itemModel[teleportItem] = MV1LoadModel("../model/ItemModel/Door.mv1");
    itemImg[stunItem] = LoadGraph("../img/stun_item.png");
    itemImg[dashItem] = LoadGraph("../img/speed_up_Item.png");
    itemImg[absorbItem] = LoadGraph("../img/magnet.png");
    itemImg[teleportItem] = LoadGraph("../img/Door.png");
    itemImg[nothing] = 0;
    itemBackWindowImgKeybord = LoadGraph("../img/item_window_Keybord.png");
    itemBackWindowImgController = LoadGraph("../img/item_window_Controller.png");
    MV1SetPosition(itemModel[stunItem], INITIALIZE_ITEM_POSITION);
    MV1SetPosition(itemModel[dashItem], INITIALIZE_ITEM_POSITION);
    MV1SetPosition(itemModel[absorbItem], INITIALIZE_ITEM_POSITION);
    MV1SetPosition(itemModel[teleportItem], INITIALIZE_ITEM_POSITION);
    itemModelRotation = 0;
}

HelpfulItems::~HelpfulItems()
{

}

//初期化
void HelpfulItems::initialize()
{
    int random = 0;//ランダム変数
    VECTOR posStrage[ITEM_KIND] = { ITEM_POSITION_1,ITEM_POSITION_2 ,ITEM_POSITION_3 ,ITEM_POSITION_4 };//アイテム座標を保管
    bool usedPos[ITEM_KIND] = {false};//すでにアイテムがおかれているか確認するためのフラグ
    checkHavingItem = false;
    havingItem = nothing;
    itemModelRotation = 0;

    //アイテムを再配置
    for (int i = 0; i < ITEM_KIND;)
    {
        random = GetRand(MAX_RANDOM);
        if (usedPos[random] == false)
        {
            itemPos[i] = posStrage[random];
            MV1SetPosition(itemModel[i], itemPos[i]);
            MV1SetScale(itemModel[i], ITEM_MODEL_SCALE);
            usedPos[random] = true;
            alreadyTakenItem[i] = false;
            itemTimer[i] = 0;
            usingItem[i] = false;
            usedItem[i] = false;
            i++;
        }
    }
}

//アイテム使用
void HelpfulItems::useItems(CheckDevice checkDevice,ControlSound& sound)
{
    //アイテムを持っていてまだ使っていない場合Eで使用
    if ((CheckHitKey(KEY_INPUT_E) || (checkDevice.getPadInput() & PAD_INPUT_1)) && havingItem != nothing && usedItem[havingItem] == false && usingItem[havingItem] == false)
    {
        sound.playSound(itemUseSE);
        usingItem[havingItem] = true;
    }

    //スタンアイテム
    if (usingItem[stunItem] == true && usedItem[stunItem] == false)
    {
        itemTimer[stunItem]++;
        //時間経過で解除
        if (itemTimer[stunItem] > STUN_TIME)
        {
            usingItem[stunItem] = false;
            usedItem[stunItem] = true;
        }
    }
    //ダッシュアイテム
    if (usingItem[dashItem] == true && usedItem[dashItem] == false)
    {
        itemTimer[dashItem]++;
        //時間経過で解除
        if (itemTimer[dashItem] > DASH_TIME)
        {
            usingItem[dashItem] = false;
            usedItem[dashItem] = true;
        }
    }
    //取得範囲上昇アイテム
    if (usingItem[absorbItem] == true && usedItem[absorbItem] == false)
    {
        itemTimer[absorbItem]++;
        //時間経過で解除
        if (itemTimer[absorbItem] > ABSORB_TIME)
        {
            usingItem[absorbItem] = false;
            usedItem[absorbItem] = true;
        }
    }
    //テレポートアイテム
    if (usingItem[teleportItem] == true && usedItem[teleportItem] == false)
    {
        itemTimer[teleportItem]++;
        //使用後即座にテレポート
        if (itemTimer[teleportItem] > TELEPORT_TIME)
        {
            usingItem[teleportItem] = false;
            usedItem[teleportItem] = true;
        }
    }
    
}

//モデル回転
void HelpfulItems::rollingModel()
{
    //常時回転
    itemModelRotation++;
    //360度を超えたら初期化
    if (itemModelRotation > MAX_ANGLE)
    {
        itemModelRotation = 0;
    }
    //回転を反映
    for (int i = 0; i < ITEM_KIND; i++) {
        MV1SetRotationXYZ(itemModel[i], VGet(0.0f, itemModelRotation * DX_PI_F / HALF_ANGLE, 0.0f));
    }
}