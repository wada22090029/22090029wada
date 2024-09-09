#include"DxLib.h"
#include"Stage.h"
#include"Player.h"
#include"Enemy.h"
#include"ControlGemObject.h"
#include"Title.h"
#include"Result.h"
#include"Pause.h"
#include"HelpfulItems.h"
#include"ControlDraw.h"
#include"CheckClear.h"
#include"ConstantStrage.h"
#include"CheckDevice.h"
#include"ControlFade.h"
#include"Tutorial.h"
#include"Compass.h"
#include"ControlFont.h"
#include"SkyDome.h"

//�v���C�V�[���`��
void ControlDraw::drawPlay(Stage stage,Player player,Enemy enemy,ControlGemObject controlGemObject, HelpfulItems helpfulItems, ControlFade& controlFade, CheckClear checkClear,Tutorial tutorial,CheckDevice checkDevice, Compass compass,SkyDome skyDome,ControlFont font)
{
    //�X�J�C�h�[��
    MV1DrawModel(skyDome.getModel());

    //�X�e�[�W�`��
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            MV1DrawModel(stage.getStageModel(i, j));
        }
    }

    //�N���A�ɕK�v�ȕ�΂�`��
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            if (controlGemObject.getObtainedObject(i, j) == false)
            {
                MV1DrawModel(controlGemObject.getModel(i,j));
            }
        }
    }

    //��΂����ׂďW�߂���S�[����`��
    if (checkClear.getClearFlg_1() == true)
    {
        MV1DrawModel(checkClear.getGoalModel());
    }

    //�A�C�e����`��
    if (helpfulItems.getAlreadyTakenItem(stunItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(stunItem));  //�X�^���A�C�e��
    }
    if (helpfulItems.getAlreadyTakenItem(dashItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(dashItem));  //�X�s�[�h�A�b�v�A�C�e��
    }
    if (helpfulItems.getAlreadyTakenItem(absorbItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(absorbItem));    //�擾�͈͑����A�C�e��
    }
    if (helpfulItems.getAlreadyTakenItem(teleportItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(teleportItem));  //�e���|�[�g�A�C�e��
    }

    MV1DrawModel(enemy.getModel());     //�G��`��

    //�����A�C�e���\���E�B���h�E
    //����f�o�C�X�ɂ���ĕ\���ύX
    if (checkDevice.getDevice() == DEVICE_KEYBORD)
    {
        DrawGraph(ITEM_BACK_WINDOW_X, ITEM_BACK_WINDOW_Y, helpfulItems.getItemBackWindowImgKeybord(), true);
    }
    else
    {
        DrawGraph(ITEM_BACK_WINDOW_X, ITEM_BACK_WINDOW_Y, helpfulItems.getItemBackWindowImgController(), true);
    }

    //�c��̕�΂̐��`��
    DrawFormatStringToHandle(REMINING_GEM_TEXT_X, REMINING_GEM_TEXT_Y, COLOR_WHITE, font.getFontHandle(MAX_FONT),"%d", checkClear.getRemainingControlGemObject());
    //���݂̏����A�C�e����`��
    if (helpfulItems.getUsingItem(helpfulItems.getHavingItem()) == false && helpfulItems.getUsedItem(helpfulItems.getHavingItem()) == false)
    {
        DrawExtendGraph(ITEM_IMG_X_1, ITEM_IMG_Y_1, ITEM_IMG_X_2, ITEM_IMG_Y_2, helpfulItems.getImg(helpfulItems.getHavingItem()), true);
    }

    //�R���p�X��`��
    MV1DrawModel(compass.getModel());


    //�`���[�g���A��
    if (tutorial.getNowTutorialNum() < TUTORIAL_KIND)
    {
        //�e�L�X�g���̃{�b�N�X
        // �`��u�����h���[�h���u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TUTORIAL_TEXT_FADE_FADE);
        DrawBox(TUTORIAL_TEXT_BOX_X_1, TUTORIAL_TEXT_BOX_Y_1, TUTORIAL_TEXT_BOX_X_2, TUTORIAL_TEXT_BOX_Y_2, GetColor(0, 0, 0), TRUE);
        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //�f�o�C�X�ɂ���ĕ\������`���[�g���A����ύX
        if (checkDevice.getDevice() == 0)
        {
            DrawGraph(0, 0, tutorial.getTutorialImgKeybord(tutorial.getNowTutorialNum()), true);
            DrawStringToHandle(TUTORIAL_TEXT_X, TUTORIAL_TEXT_Y, "�X�y�[�X�L�[�Ŏ��̃y�[�W�ɐi��", COLOR_WHITE, font.getFontHandle(MIN_FONT));
        }
        else
        {
            DrawGraph(0, 0, tutorial.getTutorialImgController(tutorial.getNowTutorialNum()), true);
            DrawStringToHandle(TUTORIAL_TEXT_X, TUTORIAL_TEXT_Y, "A�{�^���Ŏ��̃y�[�W�ɐi��", COLOR_WHITE, font.getFontHandle(MIN_FONT));
        }

        //�e�L�X�g�ɂ��Ԃ���{�b�N�X
        // �`��u�����h���[�h���u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TUTORIAL_TEXT_FADE_FADE);
        DrawBox(TUTORIAL_TEXT_BOX_X_1, TUTORIAL_TEXT_BOX_Y_1, TUTORIAL_TEXT_BOX_X_1 + tutorial.getPushButtonTimer() * TUTORIAL_TEXT_BOX_ADD_X, TUTORIAL_TEXT_BOX_Y_2, COLOR_WHITE, TRUE);
        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }

    //�V�[���ړ����̃t�F�[�h
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�^�C�g���V�[���`��
void ControlDraw::drawTitle(Title title, ControlFade& controlFade)
{
    //�w�i
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, COLOR_TITLE_BACK, true);
    //�^�C�g���摜�`��
    DrawExtendGraph(TITLE_TIMG_X_1, TITLE_TIMG_Y_1, TITLE_TIMG_X_2, TITLE_TIMG_Y_2, title.getTitleImg(), true);

    //�^�C�g���e�C�X�g�`��
    DrawGraph(0, 0, title.getMenuTextImg(), true);

    //�e�L�X�g�ɂ��Ԃ���_�Ń{�b�N�X
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
    if (title.getSelectCommand() == playGame)
    {
        DrawBox(TITLE_SELECT_PLAY_X_1, TITLE_SELECT_PLAY_Y_1, TITLE_SELECT_PLAY_X_2, TITLE_SELECT_PLAY_Y_2, COLOR_WHITE, TRUE);
    }
    if (title.getSelectCommand() == endGame)
    {
        DrawBox(TITLE_SELECT_END_X_1, TITLE_SELECT_END_Y_1, TITLE_SELECT_END_X_2, TITLE_SELECT_END_Y_2, COLOR_WHITE, TRUE);
    }
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //�V�[���ړ����̃t�F�[�h
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



void ControlDraw::drawResult(Result result,CheckClear checkClear, ControlFade& controlFade)
{
    if (checkClear.getClearFlg_2() == true)
    {
        //�Q�[���N���A�摜
        DrawGraph(0, 0, result.getGameClearImg(), true);
        //�e�L�X�g�ɂ��Ԃ���_�Ń{�b�N�X
        // �`��u�����h���[�h���u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
        if (result.getSelectCommand() == playGame)
        {
            DrawBox(RESULT_CLEAR_SELECT_PLAY_X_1, RESULT_CLEAR_SELECT_PLAY_Y_1, RESULT_CLEAR_SELECT_PLAY_X_2, RESULT_CLEAR_SELECT_PLAY_Y_2, COLOR_TEXT_BOX, TRUE);
        }
        if (result.getSelectCommand() == endGame)
        {
            DrawBox(RESULT_CLEAR_SELECT_TITLE_X_1, RESULT_CLEAR_SELECT_TITLE_Y_1, RESULT_CLEAR_SELECT_TITLE_X_2, RESULT_CLEAR_SELECT_TITLE_Y_2, COLOR_TEXT_BOX, TRUE);
        }
        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else
    {
        //�Q�[���I�[�o�[�摜
        DrawGraph(0, 0, result.getGameOverImg(), true);
        //�e�L�X�g�ɂ��Ԃ���_�Ń{�b�N�X
        // �`��u�����h���[�h���u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
        if (result.getSelectCommand() == playGame)
        {
            DrawBox(RESULT_MISS_SELECT_PLAY_X_1, RESULT_MISS_SELECT_PLAY_Y_1, RESULT_MISS_SELECT_PLAY_X_2, RESULT_MISS_SELECT_PLAY_Y_2, COLOR_WHITE, TRUE);
        }
        if (result.getSelectCommand() == endGame)
        {
            DrawBox(RESULT_MISS_SELECT_TITLE_X_1, RESULT_MISS_SELECT_TITLE_Y_1, RESULT_MISS_SELECT_TITLE_X_2, RESULT_MISS_SELECT_TITLE_Y_2, COLOR_WHITE, TRUE);
        }
        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    //�V�[���ړ����̃t�F�[�h
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



void ControlDraw::drawPause(Pause pause, ControlFade& controlFade)
{
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_BACK_FADE);
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //�|�[�Y��ʂ̃e�L�X�g�摜
    DrawGraph(0, 0, pause.getPauseText(), true);

    //�e�L�X�g�ɂ��Ԃ���_�Ń{�b�N�X
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
    if (pause.getSelectCommand() == continueGame)
    {
        DrawBox(PAUSE_SELECT_PLAY_X_1, PAUSE_SELECT_PLAY_Y_1, PAUSE_SELECT_PLAY_X_2, PAUSE_SELECT_PLAY_Y_2, COLOR_WHITE, TRUE);
    }
    if (pause.getSelectCommand() == retry)
    {
        DrawBox(PAUSE_SELECT_RETRY_X_1, PAUSE_SELECT_RETRY_Y_1, PAUSE_SELECT_RETRY_X_2, PAUSE_SELECT_RETRY_Y_2, COLOR_WHITE, TRUE);
    }
    if (pause.getSelectCommand() == returnTitle)
    {
        DrawBox(PAUSE_SELECT_TITLE_X_1, PAUSE_SELECT_TITLE_Y_1, PAUSE_SELECT_TITLE_X_2, PAUSE_SELECT_TITLE_Y_2, COLOR_WHITE, TRUE);
    }
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //�V�[���ړ����̃t�F�[�h
    // �`��u�����h���[�h���u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}