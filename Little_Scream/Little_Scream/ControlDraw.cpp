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

//プレイシーン描画
void ControlDraw::drawPlay(Stage stage,Player player,Enemy enemy,ControlGemObject controlGemObject, HelpfulItems helpfulItems, ControlFade& controlFade, CheckClear checkClear,Tutorial tutorial,CheckDevice checkDevice, Compass compass,SkyDome skyDome,ControlFont font)
{
    //スカイドーム
    MV1DrawModel(skyDome.getModel());

    //ステージ描画
    for (int i = 0; i < STAGE_SIZE; i++)
    {
        for (int j = 0; j < STAGE_SIZE; j++)
        {
            MV1DrawModel(stage.getStageModel(i, j));
        }
    }

    //クリアに必要な宝石を描画
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

    //宝石をすべて集めたらゴールを描画
    if (checkClear.getClearFlg_1() == true)
    {
        MV1DrawModel(checkClear.getGoalModel());
    }

    //アイテムを描画
    if (helpfulItems.getAlreadyTakenItem(stunItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(stunItem));  //スタンアイテム
    }
    if (helpfulItems.getAlreadyTakenItem(dashItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(dashItem));  //スピードアップアイテム
    }
    if (helpfulItems.getAlreadyTakenItem(absorbItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(absorbItem));    //取得範囲増加アイテム
    }
    if (helpfulItems.getAlreadyTakenItem(teleportItem) == false)
    {
        MV1DrawModel(helpfulItems.getModel(teleportItem));  //テレポートアイテム
    }

    MV1DrawModel(enemy.getModel());     //敵を描画

    //所持アイテム表示ウィンドウ
    //操作デバイスによって表示変更
    if (checkDevice.getDevice() == DEVICE_KEYBORD)
    {
        DrawGraph(ITEM_BACK_WINDOW_X, ITEM_BACK_WINDOW_Y, helpfulItems.getItemBackWindowImgKeybord(), true);
    }
    else
    {
        DrawGraph(ITEM_BACK_WINDOW_X, ITEM_BACK_WINDOW_Y, helpfulItems.getItemBackWindowImgController(), true);
    }

    //残りの宝石の数描画
    DrawFormatStringToHandle(REMINING_GEM_TEXT_X, REMINING_GEM_TEXT_Y, COLOR_WHITE, font.getFontHandle(MAX_FONT),"%d", checkClear.getRemainingControlGemObject());
    //現在の所持アイテムを描画
    if (helpfulItems.getUsingItem(helpfulItems.getHavingItem()) == false && helpfulItems.getUsedItem(helpfulItems.getHavingItem()) == false)
    {
        DrawExtendGraph(ITEM_IMG_X_1, ITEM_IMG_Y_1, ITEM_IMG_X_2, ITEM_IMG_Y_2, helpfulItems.getImg(helpfulItems.getHavingItem()), true);
    }

    //コンパスを描画
    MV1DrawModel(compass.getModel());


    //チュートリアル
    if (tutorial.getNowTutorialNum() < TUTORIAL_KIND)
    {
        //テキスト裏のボックス
        // 描画ブレンドモードをブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TUTORIAL_TEXT_FADE_FADE);
        DrawBox(TUTORIAL_TEXT_BOX_X_1, TUTORIAL_TEXT_BOX_Y_1, TUTORIAL_TEXT_BOX_X_2, TUTORIAL_TEXT_BOX_Y_2, GetColor(0, 0, 0), TRUE);
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //デバイスによって表示するチュートリアルを変更
        if (checkDevice.getDevice() == 0)
        {
            DrawGraph(0, 0, tutorial.getTutorialImgKeybord(tutorial.getNowTutorialNum()), true);
            DrawStringToHandle(TUTORIAL_TEXT_X, TUTORIAL_TEXT_Y, "スペースキーで次のページに進む", COLOR_WHITE, font.getFontHandle(MIN_FONT));
        }
        else
        {
            DrawGraph(0, 0, tutorial.getTutorialImgController(tutorial.getNowTutorialNum()), true);
            DrawStringToHandle(TUTORIAL_TEXT_X, TUTORIAL_TEXT_Y, "Aボタンで次のページに進む", COLOR_WHITE, font.getFontHandle(MIN_FONT));
        }

        //テキストにかぶせるボックス
        // 描画ブレンドモードをブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TUTORIAL_TEXT_FADE_FADE);
        DrawBox(TUTORIAL_TEXT_BOX_X_1, TUTORIAL_TEXT_BOX_Y_1, TUTORIAL_TEXT_BOX_X_1 + tutorial.getPushButtonTimer() * TUTORIAL_TEXT_BOX_ADD_X, TUTORIAL_TEXT_BOX_Y_2, COLOR_WHITE, TRUE);
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }

    //シーン移動時のフェード
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//タイトルシーン描画
void ControlDraw::drawTitle(Title title, ControlFade& controlFade)
{
    //背景
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, COLOR_TITLE_BACK, true);
    //タイトル画像描画
    DrawExtendGraph(TITLE_TIMG_X_1, TITLE_TIMG_Y_1, TITLE_TIMG_X_2, TITLE_TIMG_Y_2, title.getTitleImg(), true);

    //タイトルテイスト描画
    DrawGraph(0, 0, title.getMenuTextImg(), true);

    //テキストにかぶせる点滅ボックス
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
    if (title.getSelectCommand() == playGame)
    {
        DrawBox(TITLE_SELECT_PLAY_X_1, TITLE_SELECT_PLAY_Y_1, TITLE_SELECT_PLAY_X_2, TITLE_SELECT_PLAY_Y_2, COLOR_WHITE, TRUE);
    }
    if (title.getSelectCommand() == endGame)
    {
        DrawBox(TITLE_SELECT_END_X_1, TITLE_SELECT_END_Y_1, TITLE_SELECT_END_X_2, TITLE_SELECT_END_Y_2, COLOR_WHITE, TRUE);
    }
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //シーン移動時のフェード
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



void ControlDraw::drawResult(Result result,CheckClear checkClear, ControlFade& controlFade)
{
    if (checkClear.getClearFlg_2() == true)
    {
        //ゲームクリア画像
        DrawGraph(0, 0, result.getGameClearImg(), true);
        //テキストにかぶせる点滅ボックス
        // 描画ブレンドモードをブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
        if (result.getSelectCommand() == playGame)
        {
            DrawBox(RESULT_CLEAR_SELECT_PLAY_X_1, RESULT_CLEAR_SELECT_PLAY_Y_1, RESULT_CLEAR_SELECT_PLAY_X_2, RESULT_CLEAR_SELECT_PLAY_Y_2, COLOR_TEXT_BOX, TRUE);
        }
        if (result.getSelectCommand() == endGame)
        {
            DrawBox(RESULT_CLEAR_SELECT_TITLE_X_1, RESULT_CLEAR_SELECT_TITLE_Y_1, RESULT_CLEAR_SELECT_TITLE_X_2, RESULT_CLEAR_SELECT_TITLE_Y_2, COLOR_TEXT_BOX, TRUE);
        }
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else
    {
        //ゲームオーバー画像
        DrawGraph(0, 0, result.getGameOverImg(), true);
        //テキストにかぶせる点滅ボックス
        // 描画ブレンドモードをブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFlashingFadeCount());
        if (result.getSelectCommand() == playGame)
        {
            DrawBox(RESULT_MISS_SELECT_PLAY_X_1, RESULT_MISS_SELECT_PLAY_Y_1, RESULT_MISS_SELECT_PLAY_X_2, RESULT_MISS_SELECT_PLAY_Y_2, COLOR_WHITE, TRUE);
        }
        if (result.getSelectCommand() == endGame)
        {
            DrawBox(RESULT_MISS_SELECT_TITLE_X_1, RESULT_MISS_SELECT_TITLE_Y_1, RESULT_MISS_SELECT_TITLE_X_2, RESULT_MISS_SELECT_TITLE_Y_2, COLOR_WHITE, TRUE);
        }
        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    //シーン移動時のフェード
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



void ControlDraw::drawPause(Pause pause, ControlFade& controlFade)
{
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_BACK_FADE);
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //ポーズ画面のテキスト画像
    DrawGraph(0, 0, pause.getPauseText(), true);

    //テキストにかぶせる点滅ボックス
    // 描画ブレンドモードをブレンドにする
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
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //シーン移動時のフェード
    // 描画ブレンドモードをブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, controlFade.getFadeCount());
    DrawBox(0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}