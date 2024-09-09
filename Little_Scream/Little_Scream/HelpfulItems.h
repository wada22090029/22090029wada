#pragma once

class CheckDevice;
class ControlSound;

class HelpfulItems
{
private:
    static const int ITEM_KIND = 4;                 //�A�C�e���̎��
    static const int NOTHING_NUM = 1;               //�w�i�E�B���h�E�\���p
    bool checkHavingItem;                           //���݃A�C�e���������Ă��邩�ǂ���
    int havingItem;                                 //���ݎ����Ă���A�C�e��
    int itemTimer[ITEM_KIND];                       //�A�C�e���g�p���Ԍv��
    int itemModel[ITEM_KIND];                       //�A�C�e�����f��
    int itemModelRotation;                          //�A�C�e����]��   
    int itemImg[ITEM_KIND + NOTHING_NUM];           //�A�C�e���摜
    int itemBackWindowImgKeybord;                   //�A�C�e���摜�w�i�@�L�[�{�[�h�p
    int itemBackWindowImgController;                //�A�C�e���摜�w�i�@�R���g���[���[�p
    bool usingItem[ITEM_KIND];                      //�A�C�e���g�p�t���O
    bool usedItem[ITEM_KIND];                       //�A�C�e�����ߋ��Ɏg�p�������̃t���O
    bool alreadyTakenItem[ITEM_KIND];               //���łɎ�ɓ��ꂽ�A�C�e����
    VECTOR itemPos[ITEM_KIND];                      //�A�C�e���̍��W
public:
    HelpfulItems();
    ~HelpfulItems();
    void initialize();      //������
    void useItems(CheckDevice checkDevice,ControlSound& sound);     //�A�C�e���g�p
    void rollingModel();    //�A�C�e�����f����]
    void setHavingItem(int i)   //�擾�����A�C�e�����Z�b�g
    {
        havingItem = i;
        alreadyTakenItem[i] = true;
    }

    //�Q�b�^�[�֐�
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
    const VECTOR INITIALIZE_ITEM_POSITION = VGet(0, 5.5f, 0);   //�������W
    const VECTOR ITEM_POSITION_1 = VGet(0, 5.5f, 0);            //�[�@1
    const VECTOR ITEM_POSITION_2 = VGet(80, 5.5, 0);            //�[�@2
    const VECTOR ITEM_POSITION_3 = VGet(0, 5.5, -80);           //�[�@3
    const VECTOR ITEM_POSITION_4 = VGet(80, 5.5, -80);          //�[�@4
    const VECTOR ITEM_MODEL_SCALE = VGet(0.01f, 0.01f, 0.01f);  //���f���T�C�Y
    const int STUN_TIME = 200;        //�X�^�������鎞��
    const int DASH_TIME = 300;        //�_�b�V���ł��鎞��
    const int ABSORB_TIME = 300;      //�擾�͈͏㏸����
    const int TELEPORT_TIME = 1;      //�e���|�[�g�ɂ����鎞��
    const int MAX_RANDOM = 3;         //�����_���ő吔
};

