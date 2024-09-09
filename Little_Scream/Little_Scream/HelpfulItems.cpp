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

//������
void HelpfulItems::initialize()
{
    int random = 0;//�����_���ϐ�
    VECTOR posStrage[ITEM_KIND] = { ITEM_POSITION_1,ITEM_POSITION_2 ,ITEM_POSITION_3 ,ITEM_POSITION_4 };//�A�C�e�����W��ۊ�
    bool usedPos[ITEM_KIND] = {false};//���łɃA�C�e����������Ă��邩�m�F���邽�߂̃t���O
    checkHavingItem = false;
    havingItem = nothing;
    itemModelRotation = 0;

    //�A�C�e�����Ĕz�u
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

//�A�C�e���g�p
void HelpfulItems::useItems(CheckDevice checkDevice,ControlSound& sound)
{
    //�A�C�e���������Ă��Ă܂��g���Ă��Ȃ��ꍇE�Ŏg�p
    if ((CheckHitKey(KEY_INPUT_E) || (checkDevice.getPadInput() & PAD_INPUT_1)) && havingItem != nothing && usedItem[havingItem] == false && usingItem[havingItem] == false)
    {
        sound.playSound(itemUseSE);
        usingItem[havingItem] = true;
    }

    //�X�^���A�C�e��
    if (usingItem[stunItem] == true && usedItem[stunItem] == false)
    {
        itemTimer[stunItem]++;
        //���Ԍo�߂ŉ���
        if (itemTimer[stunItem] > STUN_TIME)
        {
            usingItem[stunItem] = false;
            usedItem[stunItem] = true;
        }
    }
    //�_�b�V���A�C�e��
    if (usingItem[dashItem] == true && usedItem[dashItem] == false)
    {
        itemTimer[dashItem]++;
        //���Ԍo�߂ŉ���
        if (itemTimer[dashItem] > DASH_TIME)
        {
            usingItem[dashItem] = false;
            usedItem[dashItem] = true;
        }
    }
    //�擾�͈͏㏸�A�C�e��
    if (usingItem[absorbItem] == true && usedItem[absorbItem] == false)
    {
        itemTimer[absorbItem]++;
        //���Ԍo�߂ŉ���
        if (itemTimer[absorbItem] > ABSORB_TIME)
        {
            usingItem[absorbItem] = false;
            usedItem[absorbItem] = true;
        }
    }
    //�e���|�[�g�A�C�e��
    if (usingItem[teleportItem] == true && usedItem[teleportItem] == false)
    {
        itemTimer[teleportItem]++;
        //�g�p�㑦���Ƀe���|�[�g
        if (itemTimer[teleportItem] > TELEPORT_TIME)
        {
            usingItem[teleportItem] = false;
            usedItem[teleportItem] = true;
        }
    }
    
}

//���f����]
void HelpfulItems::rollingModel()
{
    //�펞��]
    itemModelRotation++;
    //360�x�𒴂����珉����
    if (itemModelRotation > MAX_ANGLE)
    {
        itemModelRotation = 0;
    }
    //��]�𔽉f
    for (int i = 0; i < ITEM_KIND; i++) {
        MV1SetRotationXYZ(itemModel[i], VGet(0.0f, itemModelRotation * DX_PI_F / HALF_ANGLE, 0.0f));
    }
}