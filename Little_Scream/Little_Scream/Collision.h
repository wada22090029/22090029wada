#pragma once

class Stage;
class Player;
class Enemy;
class ControlGemObject;
class HelpfulItems;
class ControlSound;

class Collision
{
private:
    MV1_COLL_RESULT_POLY_DIM HitPolyDim[STAGE_SIZE][STAGE_SIZE];    //�X�e�[�W�Ɠ����������ǂ���
public:
    Collision();
    ~Collision();
    void initialize();      //������
    void stageCollision(Stage stage,Player& player);    //�X�e�[�W�ƃv���C���[�̓����蔻��
    void checkHitEnemy(Player player, int& scene, Enemy enemy, ControlSound& sound);        //�v���C���[�ƓG�Ƃ̓����蔻��
    void checkHitControlGemObject(Player player, ControlGemObject& controlGemObject, HelpfulItems helpfulItems,ControlSound& sound);        //�v���C���[�ƃN���A�p�A�C�e���̕�΂Ƃ̓����蔻��
    void checkHitHelpfulItem(Player player, HelpfulItems& helpfulItem, ControlSound& sound);        //�v���C���[�Ƃ������A�C�e���Ƃ̓����蔻��
    bool checkHitGoalArea(Player player);       //�v���C���[�ƃS�[���G���A�Ƃ̓����蔻��
private:
    //�萔
    const int HIT = 1;                      //�q�b�g���̒l
    const int FRAME_INDEX = -1;             //�t���[���ԍ�
    const float PUSH_VECTOR = 0.01f;        //�����o����
    const int DIV_NUM = 2;                  //��ԕ�����
    const float SPHERE_PLAYER_R = 0.9f;     //�v���C���[�����蔻�苅�̔��a
    const float SPHERE_ENEMY_R = 1.5f;      //�G�����蔻�苅�̔��a
    const float SPHERE_GEM_R = 0.2f;        //�N���A�p�A�C�e���̕�΁@�����蔻�苅�̔��a
    const float SPHERE_HELPFUL_ITEM_R = 0.8f;       //�������A�C�e�������蔻�苅�̔��a
    const float SPHERE_GOAL_AREA_R = 2.5f;          //�S�[���G���A�����蔻�苅�̔��a
    const float INITIALIZE_PLAYER_POSITION_Y = 6.0f;//�v���C���[�̏������W
    const float PLAYER_COLLIDION_POSITION_Y = 5.0f;
    const int CONFIRMATION_COUNTER = 5;     //�m�F����ۂɌJ��Ԃ���
    const int MAX_REPEAT_COUNT = 10000;     //�ő�J��Ԃ���
    const int HIT_POLY_COORDINATE_1 = 0;    //���������|���S���̒��_1
    const int HIT_POLY_COORDINATE_2 = 1;    //���������|���S���̒��_2
    const int HIT_POLY_COORDINATE_3 = 2;    //���������|���S���̒��_3
    const float ADD_ABSORB_RANGE = 7.0f;         //�擾�͈͑�����
};

