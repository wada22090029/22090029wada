#include"DxLib.h"
#include"ConstantStrage.h"
#include"Player.h"
#include"Stage.h"
#include"Enemy.h"
#include"ControlGemObject.h"
#include"HelpfulItems.h"
#include"SceneStrage.h"
#include"ConstantStrage.h"
#include"ControlSound.h"
#include "Collision.h"


Collision::Collision()
{
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            HitPolyDim[i][j].HitNum = 0;
        }
    }
}

Collision::~Collision()
{
    
}

//������
void Collision::initialize()
{
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            HitPolyDim[i][j].HitNum = 0;
        }
    }
}

//�X�e�[�W�ƃv���C���[�̓����蔻��
void Collision::stageCollision(Stage stage,Player& player)
{
    //���݂̍��W��ۑ�
    player.setKeepPosition(VAdd(player.getPosition(), player.getMoveVector()));

    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            // ���f���S�̂̃R���W���������\�z
            MV1SetupCollInfo(stage.getStageModel(i, j), FRAME_INDEX, DIV_NUM, DIV_NUM, DIV_NUM);
            // ���f���Ƌ��Ƃ̓����蔻��
            HitPolyDim[i][j] = MV1CollCheck_Sphere(stage.getStageModel(i, j), FRAME_INDEX, VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()), SPHERE_PLAYER_R);
        }
    }

    VECTOR slideVector; //�ړ���
    bool hit = false;   //�����������ǂ���
    int counter = 0;    //���s�񐔐����p�J�E���^�[

    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            // �����������ǂ����ŏ����𕪊�
            if (HitPolyDim[i][j].HitNum >= HIT)
            {
                    hit = true;

                    // �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
                    slideVector = VCross(player.getMoveVector(), HitPolyDim[i][j].Dim->Normal);

                    // �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
                    // ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
                    slideVector = VCross(HitPolyDim[i][j].Dim->Normal, slideVector);

                    // ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
                    player.setKeepPosition(VAdd(player.getPosition(), slideVector));
            }
            // �����蔻����̌�n��
            MV1CollResultPolyDimTerminate(HitPolyDim[i][j]);
        }

    }

    //�߂荞��ł����牟���o��
    for (int h = 0;h < CONFIRMATION_COUNTER; h++)
    {
        for (int i = 0; i < STAGE_SIZE; i++)
        {
            for (int j = 0; j < STAGE_SIZE; j++)
            {
                // ���f���Ƌ��Ƃ̓����蔻��
                HitPolyDim[i][j] = MV1CollCheck_Sphere(stage.getStageModel(i, j), FRAME_INDEX, VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()), SPHERE_PLAYER_R);
            }
        }

        if (hit == true)
        {
            for (int i = 0; i < STAGE_SIZE; i++)
            {
                for (int j = 0; j < STAGE_SIZE; j++)
                {
                    //�������Ă������
                    while (HitPolyDim[i][j].HitNum >= HIT)
                    {
                        counter++;
                        //�����o��
                        player.setKeepPosition(VAdd(player.getKeepPosition(), VScale(HitPolyDim[i][j].Dim->Normal, PUSH_VECTOR)));
                        player.setKeepPosition(VGet(player.getKeepPositionX(), INITIALIZE_PLAYER_POSITION_Y, player.getKeepPositionZ()));
                        // ������Ȃ��Ȃ���or�ړ��s�Ȃ�E�o
                        if (HitCheck_Sphere_Triangle(VGet(player.getKeepPositionX(), PLAYER_COLLIDION_POSITION_Y, player.getKeepPositionZ()),SPHERE_PLAYER_R,
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_1],
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_2],
                            HitPolyDim[i][j].Dim->Position[HIT_POLY_COORDINATE_3]) == FALSE || 
                            counter > MAX_REPEAT_COUNT)
                        {
                            counter = 0;
                            break;
                        }
                    }
                    // �����蔻����̌�n��
                    MV1CollResultPolyDimTerminate(HitPolyDim[i][j]);
                }
            }
        }
    }
    
    //���W�𔽉f
    player.setPosition(player.getKeepPosition());
    
    //�v���C���[�̈ړ��ʂ����Z�b�g
    player.resetMoveVector();
}

//�v���C���[�ƓG�Ƃ̓����蔻��
void Collision::checkHitEnemy(Player player, int& scene,Enemy enemy, ControlSound& sound)
{
    //�������o��
    VECTOR Vec = VSub(enemy.getPosition(), player.getPosition());
    //���͈͓��ɓ�������Q�[���I�[�o�[��ʂ�
    if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_ENEMY_R)
    {
        sound.playSound(deadSE);
        scene = resultScene;
    }
}

//�v���C���[�ƃN���A�p�A�C�e���̕�΂Ƃ̓����蔻��
void Collision::checkHitControlGemObject(Player player,ControlGemObject& controlGemObject, HelpfulItems helpfulItems,ControlSound& sound)
{
    float itemBoost = 0;
    //���΂��g���Ă�����擾�͈͊g��
    if (helpfulItems.getUsingItem(absorbItem) == true)
    {
        itemBoost = ADD_ABSORB_RANGE;
    }
    for (int i = 0; i < STAGE_SIZE; i++) {
        for (int j = 0; j < STAGE_SIZE; j++) {
            //�������o��
            VECTOR Vec = VSub(controlGemObject.getPosition(i,j), player.getPosition());
            //�͈͓��ɓ����Ă�����擾
            if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_GEM_R + itemBoost && controlGemObject.getObtainedObject(i,j) == false)
            {
                sound.playSound(getObjectSE);
                controlGemObject.setObtainedObject(i,j,true);
            }
        }
    }
}

//�v���C���[�Ƃ������A�C�e���Ƃ̓����蔻��
void Collision::checkHitHelpfulItem(Player player,HelpfulItems& helpfulItems, ControlSound& sound)
{
    for (int i = 0; i < ALL_HELPFULL_ITEM_KIND; i++)
    {
        //�������o��
        VECTOR Vec = VSub(helpfulItems.getItemPosition(i), player.getPosition());
        //�͈͓��ɓ����Ă�����擾
        if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_HELPFUL_ITEM_R && helpfulItems.getAlreadyTakenItem(i) == false)
        {
            sound.playSound(getObjectSE);
            helpfulItems.setHavingItem(i);
        }
    }
}

//�v���C���[�ƃS�[���G���A�Ƃ̓����蔻��
bool Collision::checkHitGoalArea(Player player)
{
    //�������o��
    VECTOR Vec = VSub(GOAL_POSITION, player.getPosition());
    //�͈͓��ɓ����Ă�����S�[��
    if (VSize(Vec) < SPHERE_PLAYER_R + SPHERE_GOAL_AREA_R)
    {
        return true;
    }
    else
    {
        return false;
    }
}
