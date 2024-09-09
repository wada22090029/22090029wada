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

//タイトルシーン
void SceneManager::controlTitleScene(Title& title,int& scene, ControlFade& controlFade, CheckDevice checkDevice,ControlSound& sound)
{
    //点滅
    controlFade.flashingFade();
    if (sceneKeeper != titleScene || controlFade.getFadeCount() != 0)
    {
        sound.stopSound(titleBGM);
        //フェード兼シーン移動を反映
        controlFadeScene(controlFade, scene);
    }
    else
    {
        sound.playSoundLoop(titleBGM);
        //選択処理
        title.selectCommand(sceneKeeper,checkDevice,sound);
    }
}

//ポーズシーン
void SceneManager::controlPauseScene(Pause& pause, int& scene, ControlFade& controlFade,CheckDevice checkDevice, ControlSound& sound,ControlGemObject& controlGemObject,HelpfulItems& helpfulItems)
{
    //点滅
    controlFade.flashingFade();
    //選択処理
    pause.selectCommand(sceneKeeper, checkDevice,sound);
    //ポーズ時処理
    pause.controlPauseKey(sceneKeeper, checkDevice,sound);
    if (sceneKeeper == titleScene || (sceneKeeper == playScene && pause.getResetFlg() == true))
    {
        //フェード兼シーン移動を反映
        controlFadeScene(controlFade, scene);
    }
    if (sceneKeeper == playScene && pause.getResetFlg() == false)
    {
        //シーン一時保存
        scene = sceneKeeper;
    }
    //モデル回転
    controlGemObject.rollingModel();
    helpfulItems.rollingModel();
}

//プレイシーン
void SceneManager::controlPlayScene(Camera& camera,Light& light,Player& player,Collision& collision,Stage stage,Enemy& enemy,ControlGemObject& controlGemObject,int& scene, CheckClear& checkClear, HelpfulItems& helpfulItems, ControlFade& controlFade,Pause &pause,Tutorial& tutorial,CheckDevice checkDevice,Compass& compass,SkyDome& skyDome, ControlSound& sound)
{
    if (sceneKeeper == resultScene || controlFade.getFadeCount() != 0)
    {
        //フェード兼シーン移動を反映
        controlFadeScene(controlFade, scene);
        //マウス使用時の視点移動をリセット
        player.resetMousePosition();
    }
    else
    {
        //チュートリアル
        if (tutorial.getNowTutorialNum() < TUTORIAL_KIND)
        {
            tutorial.checkPushButton(checkDevice,sound);
            //マウス使用時の視点移動をリセット
            player.resetMousePosition();
        }
        else
        {
            player.control(helpfulItems,checkDevice,sound);     //プレイヤーコントロール
            skyDome.setPosition(player);                        //スカイドームポジションセット
            enemy.updatePosition(stage, player.getPosition(), player, helpfulItems,sound);      //敵移動
            collision.stageCollision(stage, player);        //ステージ当たり判定
            collision.checkHitEnemy(player, sceneKeeper, enemy,sound);      //敵当たり判定
            collision.checkHitControlGemObject(player, controlGemObject, helpfulItems,sound);       //宝石当たり判定
            collision.checkHitHelpfulItem(player, helpfulItems,sound);      //お助けアイテム当たり判定
            camera.mainCamera(player);                      //メインカメラ
            light.setPlayerLight(player);                   //ライトをセット
            helpfulItems.useItems(checkDevice,sound);       //アイテム使用
            compass.findObjectDistanceAndDirection(player, controlGemObject,checkClear);    //オブジェクトとの方向を得る
            pause.controlPauseKey(sceneKeeper, checkDevice,sound);          //ポーズキーを押されたときの処理
            checkClear.checkClearConditions_1(controlGemObject);            //クリア条件を達成しているか判定　1つ目
            if (checkClear.getClearFlg_1() == true)     //達成していた場合
            {
                //二つ目の条件を達成しているか判定
                checkClear.checkClearConditions_2(player, sceneKeeper, collision);
                checkClear.rollingModel();
            }

            //シーン移動を反映
            if (sceneKeeper == pauseScene)
            {
                scene = sceneKeeper;
            }
        }
    }
    //オブジェクト回転
    controlGemObject.rollingModel();
    helpfulItems.rollingModel();
}

//リザルトシーン
void SceneManager::controlResultScene(Result& result,int& scene, ControlFade& controlFade, CheckDevice checkDevice, ControlSound& sound,CheckClear checkClear)
{
    //点滅
    controlFade.flashingFade();
    if (sceneKeeper != resultScene || controlFade.getFadeCount() != 0)
    {
        //フェード兼シーン移動を反映
        controlFadeScene(controlFade,scene);
        sound.stopSound(goalBGM);
    }
    else
    {
        //選択処理
        result.selectCommand(sceneKeeper,checkDevice,sound);
        if (checkClear.getClearFlg_2() == true)
        {
            sound.playSoundLoop(goalBGM);
        }
    }
}

//シーン移動時のフェード
void SceneManager::controlFadeScene(ControlFade& controlFade, int& scene)
{
    if (controlFade.getFadeFlg() == false)
    {
        //フェードイン
        controlFade.fadeIn();
        //明るくなったら
        if (controlFade.getFadeFlg() == true)
        {
            //シーン移動を反映
            scene = sceneKeeper;
        }
    }
    else
    {
        //フェードアウト
        controlFade.fadeOut();
    }
}
