#include"DxLib.h"
#include "ConstantStrage.h"
#include"Camera.h"
#include"Light.h"
#include"Stage.h"
#include"Player.h"
#include"Enemy.h"
#include"Collision.h"
#include"ControlDraw.h"
#include"ControlGemObject.h"
#include"Title.h"
#include"Result.h"
#include"Pause.h"
#include"CheckClear.h"
#include"HelpfulItems.h"
#include"ControlFade.h"
#include"Tutorial.h"
#include"CheckDevice.h"
#include"Compass.h"
#include"SkyDome.h"
#include"ControlFont.h"
#include"ControlSound.h"
#include"SceneStrage.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
    sceneKeeper = 0;
}

SceneManager::~SceneManager()
{

}

//�^�C�g���V�[��
void SceneManager::controlTitleScene(Title& title,int& scene, ControlFade& controlFade, CheckDevice checkDevice,ControlSound& sound)
{
    //�_��
    controlFade.flashingFade();
    if (sceneKeeper != titleScene || controlFade.getFadeCount() != 0)
    {
        sound.stopSound(titleBGM);
        //�t�F�[�h���V�[���ړ��𔽉f
        controlFadeScene(controlFade, scene);
    }
    else
    {
        sound.playSoundLoop(titleBGM);
        //�I������
        title.selectCommand(sceneKeeper,checkDevice,sound);
    }
}

//�|�[�Y�V�[��
void SceneManager::controlPauseScene(Pause& pause, int& scene, ControlFade& controlFade,CheckDevice checkDevice, ControlSound& sound,ControlGemObject& controlGemObject,HelpfulItems& helpfulItems)
{
    //�_��
    controlFade.flashingFade();
    //�I������
    pause.selectCommand(sceneKeeper, checkDevice,sound);
    //�|�[�Y������
    pause.controlPauseKey(sceneKeeper, checkDevice,sound);
    if (sceneKeeper == titleScene || (sceneKeeper == playScene && pause.getResetFlg() == true))
    {
        //�t�F�[�h���V�[���ړ��𔽉f
        controlFadeScene(controlFade, scene);
    }
    if (sceneKeeper == playScene && pause.getResetFlg() == false)
    {
        //�V�[���ꎞ�ۑ�
        scene = sceneKeeper;
    }
    //���f����]
    controlGemObject.rollingModel();
    helpfulItems.rollingModel();
}

//�v���C�V�[��
void SceneManager::controlPlayScene(Camera& camera,Light& light,Player& player,Collision& collision,Stage stage,Enemy& enemy,ControlGemObject& controlGemObject,int& scene, CheckClear& checkClear, HelpfulItems& helpfulItems, ControlFade& controlFade,Pause &pause,Tutorial& tutorial,CheckDevice checkDevice,Compass& compass,SkyDome& skyDome, ControlSound& sound)
{
    if (sceneKeeper == resultScene || controlFade.getFadeCount() != 0)
    {
        //�t�F�[�h���V�[���ړ��𔽉f
        controlFadeScene(controlFade, scene);
        //�}�E�X�g�p���̎��_�ړ������Z�b�g
        player.resetMousePosition();
    }
    else
    {
        //�`���[�g���A��
        if (tutorial.getNowTutorialNum() < TUTORIAL_KIND)
        {
            tutorial.checkPushButton(checkDevice,sound);
            //�}�E�X�g�p���̎��_�ړ������Z�b�g
            player.resetMousePosition();
        }
        else
        {
            player.control(helpfulItems,checkDevice,sound);     //�v���C���[�R���g���[��
            skyDome.setPosition(player);                        //�X�J�C�h�[���|�W�V�����Z�b�g
            enemy.updatePosition(stage, player.getPosition(), player, helpfulItems,sound);      //�G�ړ�
            collision.stageCollision(stage, player);        //�X�e�[�W�����蔻��
            collision.checkHitEnemy(player, sceneKeeper, enemy,sound);      //�G�����蔻��
            collision.checkHitControlGemObject(player, controlGemObject, helpfulItems,sound);       //��Γ����蔻��
            collision.checkHitHelpfulItem(player, helpfulItems,sound);      //�������A�C�e�������蔻��
            camera.mainCamera(player);                      //���C���J����
            light.setPlayerLight(player);                   //���C�g���Z�b�g
            helpfulItems.useItems(checkDevice,sound);       //�A�C�e���g�p
            compass.findObjectDistanceAndDirection(player, controlGemObject,checkClear);    //�I�u�W�F�N�g�Ƃ̕����𓾂�
            pause.controlPauseKey(sceneKeeper, checkDevice,sound);          //�|�[�Y�L�[�������ꂽ�Ƃ��̏���
            checkClear.checkClearConditions_1(controlGemObject);            //�N���A������B�����Ă��邩����@1��
            if (checkClear.getClearFlg_1() == true)     //�B�����Ă����ꍇ
            {
                //��ڂ̏�����B�����Ă��邩����
                checkClear.checkClearConditions_2(player, sceneKeeper, collision);
                checkClear.rollingModel();
            }

            //�V�[���ړ��𔽉f
            if (sceneKeeper == pauseScene)
            {
                scene = sceneKeeper;
            }
        }
    }
    //�I�u�W�F�N�g��]
    controlGemObject.rollingModel();
    helpfulItems.rollingModel();
}

//���U���g�V�[��
void SceneManager::controlResultScene(Result& result,int& scene, ControlFade& controlFade, CheckDevice checkDevice, ControlSound& sound,CheckClear checkClear)
{
    //�_��
    controlFade.flashingFade();
    if (sceneKeeper != resultScene || controlFade.getFadeCount() != 0)
    {
        //�t�F�[�h���V�[���ړ��𔽉f
        controlFadeScene(controlFade,scene);
        sound.stopSound(goalBGM);
    }
    else
    {
        //�I������
        result.selectCommand(sceneKeeper,checkDevice,sound);
        if (checkClear.getClearFlg_2() == true)
        {
            sound.playSoundLoop(goalBGM);
        }
    }
}

//�V�[���ړ����̃t�F�[�h
void SceneManager::controlFadeScene(ControlFade& controlFade, int& scene)
{
    if (controlFade.getFadeFlg() == false)
    {
        //�t�F�[�h�C��
        controlFade.fadeIn();
        //���邭�Ȃ�����
        if (controlFade.getFadeFlg() == true)
        {
            //�V�[���ړ��𔽉f
            scene = sceneKeeper;
        }
    }
    else
    {
        //�t�F�[�h�A�E�g
        controlFade.fadeOut();
    }
}
