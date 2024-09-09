#include"Dxlib.h"
#include"ConstantStrage.h"
#include"SceneStrage.h"
#include"ControlFps.h"
#include"Camera.h"
#include"Stage.h"
#include"Player.h"
#include"Enemy.h"
#include"ControlDraw.h"
#include"Light.h"
#include"Collision.h"
#include "ControlGemObject.h"
#include"Title.h"
#include"Result.h"
#include"Pause.h"
#include"ControlFade.h"
#include"CheckClear.h"
#include"HelpfulItems.h"
#include"Tutorial.h"
#include"InitializeManager.h"
#include"CheckDevice.h"
#include"Compass.h"
#include"SkyDome.h"
#include"ControlFont.h"
#include"ControlSound.h"
#include"SceneManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//��{�ݒ�
	SetMainWindowText("onigokko");//�E�B���h�E��
	DxLib_Init();           //���C�u������������
	ChangeWindowMode(false);//�X�N���[�����[�h�ݒ�
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,COLOR_BIT);//�`��T�C�Y
	SetUseZBuffer3D(true);//z�o�b�t�@���g�p����
	SetWriteZBuffer3D(true);//z�o�b�t�@�ɏ������݂�����
    //����ʂɕ`��
    SetDrawScreen(DX_SCREEN_BACK);
	//���s1�`500�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.01f, 500.0f);

    ControlFps controlFps;
    Camera camera;
	Stage stage;
	Player player;
	Enemy enemy;
	ControlDraw ControlDraw;
	SceneManager sceneManager;
	Light light;
	Collision collision;
	ControlGemObject controlGemObject;
	Title title;
	Result result;
	Pause pause;
	CheckClear checkClear;
	InitializeManager initialize;
	HelpfulItems helpfulItems;
	ControlFade controlFade;
	CheckDevice checkDevice;
	Tutorial tutorial;
	Compass compass;
	SkyDome skyDome;
	ControlFont font;
	ControlSound sound;

	//�V�[��������
	int scene = titleScene;
	int checkChangeScene = titleScene;

	//�W�����C�g�𖳌���
	SetLightEnable(FALSE);

	//�X�e�[�W���Z�b�g
	stage.setStage();
	//������
	initialize.playSceneInitialize(player, collision, enemy, controlGemObject, stage, checkClear, helpfulItems, pause,camera,light,skyDome);

	//���C�����[�v
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		//fps�X�V
        controlFps.upDate();
		//�`�������
        ClearDrawScreen();

		//�R���g���[���[����
		checkDevice.CheckDeviceNum();

		//�^�C�g���V�[��
		if (scene == titleScene)
		{
			//�^�C�g���V�[������
			sceneManager.controlTitleScene(title, scene, controlFade,checkDevice,sound);
			//�^�C�g���V�[���`��
			sceneManager.drawTitleScene(ControlDraw, title, controlFade);
		}

		//�v���C�V�[��
		if (scene == playScene || scene == pauseScene)
		{
			//�|�[�Y��ʔ���
			if (scene == pauseScene)
			{
				sceneManager.controlPauseScene(pause,scene, controlFade,checkDevice,sound,controlGemObject,helpfulItems);
			}
			else
			{
				//�v���C�V�[������
				sceneManager.controlPlayScene(camera, light, player, collision, stage, enemy, controlGemObject, scene, checkClear, helpfulItems, controlFade, pause, tutorial, checkDevice, compass, skyDome,sound);
			}

			//�v���C�V�[���`��
			sceneManager.drawPlayScene(ControlDraw, stage, player, enemy, controlGemObject, helpfulItems, controlFade, checkClear, tutorial, checkDevice,compass,skyDome,font);

			if (scene == playScene && controlFade.getFadeFlg() == false && tutorial.getNowTutorialNum() >= 2 || controlFade.getFadeCount() == 255)
			{
				//���C�g����
				light.deletePlayerLight();
			}

			//�|�[�Y��ʕ`��
			if (scene == pauseScene)
			{
				sceneManager.drawPauseScene(ControlDraw, pause, controlFade);
			}

			//�^�C�g���֖߂�ۂ��邢�̓|�[�Y��ʂ���Q�[�������Z�b�g����ۂ̃f�[�^������
			if (scene == titleScene || (scene == playScene && pause.getResetFlg() == true))
			{
				//�f�[�^���Z�b�g
				initialize.playSceneInitialize(player, collision, enemy, controlGemObject,stage, checkClear, helpfulItems,pause,camera,light,skyDome);
				sound.allSoundStop();
			}
			else if (scene == resultScene)
			{
				//���ׂẲ����~�߂�
				sound.allSoundStop();
			}
		}

		//���U���g�V�[��
		if (scene == resultScene)
		{
			//���U���g�V�[������
			sceneManager.controlResultScene(result,scene, controlFade, checkDevice,sound,checkClear);
			//���U���g�V�[���`��
			sceneManager.drawResultScene(ControlDraw,result, checkClear, controlFade);

			//�ʂ̃V�[���ړ���
			if (scene != resultScene)
			{
				//�f�[�^���Z�b�g
				initialize.playSceneInitialize(player,collision,enemy,controlGemObject,stage, checkClear, helpfulItems, pause,camera,light,skyDome);
			}
		}

		//����ʂɏ��������̂�`��
		ScreenFlip();
		//fps�ҋ@
		controlFps.wait();   

		//�Q�[���I��
        if (scene == endScene)
        {
            break;
        }
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}