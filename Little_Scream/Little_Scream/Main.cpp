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
	//基本設定
	SetMainWindowText("onigokko");//ウィンドウ名
	DxLib_Init();           //ライブラリを初期化
	ChangeWindowMode(false);//スクリーンモード設定
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,COLOR_BIT);//描画サイズ
	SetUseZBuffer3D(true);//zバッファを使用する
	SetWriteZBuffer3D(true);//zバッファに書き込みをする
    //裏画面に描画
    SetDrawScreen(DX_SCREEN_BACK);
	//奥行1～500までをカメラの描画範囲とする
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

	//シーン初期化
	int scene = titleScene;
	int checkChangeScene = titleScene;

	//標準ライトを無効化
	SetLightEnable(FALSE);

	//ステージをセット
	stage.setStage();
	//初期化
	initialize.playSceneInitialize(player, collision, enemy, controlGemObject, stage, checkClear, helpfulItems, pause,camera,light,skyDome);

	//メインループ
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		//fps更新
        controlFps.upDate();
		//描画を消す
        ClearDrawScreen();

		//コントローラー判別
		checkDevice.CheckDeviceNum();

		//タイトルシーン
		if (scene == titleScene)
		{
			//タイトルシーン処理
			sceneManager.controlTitleScene(title, scene, controlFade,checkDevice,sound);
			//タイトルシーン描画
			sceneManager.drawTitleScene(ControlDraw, title, controlFade);
		}

		//プレイシーン
		if (scene == playScene || scene == pauseScene)
		{
			//ポーズ画面判定
			if (scene == pauseScene)
			{
				sceneManager.controlPauseScene(pause,scene, controlFade,checkDevice,sound,controlGemObject,helpfulItems);
			}
			else
			{
				//プレイシーン処理
				sceneManager.controlPlayScene(camera, light, player, collision, stage, enemy, controlGemObject, scene, checkClear, helpfulItems, controlFade, pause, tutorial, checkDevice, compass, skyDome,sound);
			}

			//プレイシーン描画
			sceneManager.drawPlayScene(ControlDraw, stage, player, enemy, controlGemObject, helpfulItems, controlFade, checkClear, tutorial, checkDevice,compass,skyDome,font);

			if (scene == playScene && controlFade.getFadeFlg() == false && tutorial.getNowTutorialNum() >= 2 || controlFade.getFadeCount() == 255)
			{
				//ライト消去
				light.deletePlayerLight();
			}

			//ポーズ画面描画
			if (scene == pauseScene)
			{
				sceneManager.drawPauseScene(ControlDraw, pause, controlFade);
			}

			//タイトルへ戻る際あるいはポーズ画面からゲームをリセットする際のデータ初期化
			if (scene == titleScene || (scene == playScene && pause.getResetFlg() == true))
			{
				//データリセット
				initialize.playSceneInitialize(player, collision, enemy, controlGemObject,stage, checkClear, helpfulItems,pause,camera,light,skyDome);
				sound.allSoundStop();
			}
			else if (scene == resultScene)
			{
				//すべての音を止める
				sound.allSoundStop();
			}
		}

		//リザルトシーン
		if (scene == resultScene)
		{
			//リザルトシーン処理
			sceneManager.controlResultScene(result,scene, controlFade, checkDevice,sound,checkClear);
			//リザルトシーン描画
			sceneManager.drawResultScene(ControlDraw,result, checkClear, controlFade);

			//別のシーン移動時
			if (scene != resultScene)
			{
				//データリセット
				initialize.playSceneInitialize(player,collision,enemy,controlGemObject,stage, checkClear, helpfulItems, pause,camera,light,skyDome);
			}
		}

		//裏画面に書いたものを描画
		ScreenFlip();
		//fps待機
		controlFps.wait();   

		//ゲーム終了
        if (scene == endScene)
        {
            break;
        }
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}