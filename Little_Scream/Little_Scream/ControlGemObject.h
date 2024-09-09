#pragma once

class Stage;
class Player;

class ControlGemObject
{
private:
    VECTOR objectPosition[STAGE_SIZE][STAGE_SIZE];  //��΂̍��W
    bool obtainedObject[STAGE_SIZE][STAGE_SIZE];    //��΂��擾������
    int objectModelOriginal;                        //��΂̃��f���@�R�s�[��
    int objectModel[STAGE_SIZE][STAGE_SIZE];        //��΂̃��f���z��@�R�s�[��
    int objectModelRotation;                        //��΂̉�]��
public:
    ControlGemObject();
    ~ControlGemObject();
    void initialize(Stage stage);   //������
    void rollingModel();            //��]

    //�Q�b�^�[�֐�
    VECTOR getPosition(const int i, const  int j) { return objectPosition[i][j]; }
    bool getObtainedObject(const int i, const  int j) { return obtainedObject[i][j]; }
    void setObtainedObject(const int i, const  int j, const  bool flg) { obtainedObject[i][j] = flg; }
    int getModel(const int i, const  int j) { return objectModel[i][j]; }
private:
    //�萔
    const VECTOR GEM_OBJECT_SCALE = VGet(0.005f, 0.005f, 0.005f);   //��΃I�u�W�F�N�g�T�C�Y
    const float INITIALIZE_GEM_POSITION_Y = 5.5f;                   //��Ώ����ʒu�@Y���W
    const int LEFT_SIDE = 0;         //���[
    const int RIGHT_SIDE = 20;       //�E�[
    const int UP_SIDE = 0;           //��
    const int DOWN_SIDE = 20;        //��

};

