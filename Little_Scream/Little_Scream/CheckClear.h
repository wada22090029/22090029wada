#pragma once

class ControlGemObject;
class Player;
class Collision;

class CheckClear
{
private:
    bool clearFlg_1;                    //�N���A�p�̃t���O���
    bool clearFlg_2;                    //�N���A�p�̃t���O���
    int remainingControlGemObject;      //�c��̕�΂̐�
    int goalModel;                      //�S�[���̃��f��
    int goalModelRotation;              //�S�[�����f���̉�]��

public:
    CheckClear();
    ~CheckClear();
    void initialize();      //������
    void checkClearConditions_1(ControlGemObject ControlGemObject);                 //��΂����ׂďW�߂Ă��邩����
    void checkClearConditions_2(Player player, int& scene,Collision collision);     //�S�[���܂ł��ǂ蒅���Ă��邩����
    void rollingModel();    //�S�[���̃��f������]

    //�Q�b�^�[�֐�
    bool getClearFlg_1() { return clearFlg_1; }
    bool getClearFlg_2() { return clearFlg_2; }
    int getRemainingControlGemObject(){return remainingControlGemObject; }
    int getGoalModel() { return goalModel; }

private:
    //�萔
    const VECTOR GOAL_MODEL_SIZE = VGet(0.01f, 0.01f, 0.01f);   //�S�[�����f���̃T�C�Y

};

