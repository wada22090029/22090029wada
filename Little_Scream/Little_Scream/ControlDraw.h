#pragma once
class Stage;
class Player;
class Enemy;
class ControlGemObject;
class Title;
class Result;
class Pause;
class CheckClear;
class HelpfulItems;
class ControlFade;
class CheckClear;
class Tutorial;
class CheckDevice;
class Compass;
class SkyDome;
class ControlFont;

class ControlDraw
{
public:
    //�e�V�[���`��
    void drawPlay(Stage stage,Player player,Enemy enemy,ControlGemObject controlGemObject,HelpfulItems, ControlFade& controlFade, CheckClear checkClear,Tutorial tutorial,CheckDevice checkDevice, Compass compass, SkyDome skyDome,ControlFont font);
    void drawTitle(Title title, ControlFade& controlFade);
    void drawResult(Result result, CheckClear checkClear, ControlFade& controlFade);
    void drawPause(Pause pause, ControlFade& controlFade);
private:
    //�萔
    //�v���C�V�[��
    //�A�C�e���w�i�̃E�B���h�E�摜
    const int ITEM_BACK_WINDOW_X = 20;
    const int ITEM_BACK_WINDOW_Y = 800;
    //�c��̕�ΐ��̃e�L�X�g
    const int REMINING_GEM_TEXT_X = 230;
    const int REMINING_GEM_TEXT_Y = 850;
    //�A�C�e���摜
    const int ITEM_IMG_X_1 = 50;
    const int ITEM_IMG_X_2 = 150;
    const int ITEM_IMG_Y_1 = 900;
    const int ITEM_IMG_Y_2 = 1000;
    //�`���[�g���A���́g���֐i�ށh�e�L�X�g�w�i
    const int TUTORIAL_TEXT_BOX_X_1 = 780;
    const int TUTORIAL_TEXT_BOX_X_2 = 1080;
    const int TUTORIAL_TEXT_BOX_Y_1 = 980;
    const int TUTORIAL_TEXT_BOX_Y_2 = 1040;
    const int TUTORIAL_TEXT_BOX_ADD_X = 6;
    //�`���[�g���A���́g���֐i�ށh�e�L�X�g
    const int TUTORIAL_TEXT_X = 800;
    const int TUTORIAL_TEXT_Y = 1000;
    //�`���[�g���A���́g���֐i�ށh�e�L�X�g�ɂ��Ԃ���BOX
    const int TITLE_TIMG_X_1 = 450;
    const int TITLE_TIMG_X_2 = 1500;
    const int TITLE_TIMG_Y_1 = 0;
    const int TITLE_TIMG_Y_2 = 800;

    //�^�C�g���V�[��
    //�^�C�g���V�[������v���C�V�[����I��
    const int TITLE_SELECT_PLAY_X_1 = 70;
    const int TITLE_SELECT_PLAY_X_2 = 310;
    const int TITLE_SELECT_PLAY_Y_1 = 660;
    const int TITLE_SELECT_PLAY_Y_2 = 760;
    //�^�C�g���V�[������G���h�V�[����I��
    const int TITLE_SELECT_END_X_1 = 70;
    const int TITLE_SELECT_END_X_2 = 610;
    const int TITLE_SELECT_END_Y_1 = 810;
    const int TITLE_SELECT_END_Y_2 = 910;

    //���U���g�V�[��
    //�N���A��
    //���U���g�V�[������Z���N�g�V�[����I��
    const int RESULT_CLEAR_SELECT_PLAY_X_1 = 860;
    const int RESULT_CLEAR_SELECT_PLAY_X_2 = 1060;
    const int RESULT_CLEAR_SELECT_PLAY_Y_1 = 620;
    const int RESULT_CLEAR_SELECT_PLAY_Y_2 = 690;
    //���U���g�V�[������^�C�g���V�[����I��
    const int RESULT_CLEAR_SELECT_TITLE_X_1 = 690;
    const int RESULT_CLEAR_SELECT_TITLE_X_2 = 1230;
    const int RESULT_CLEAR_SELECT_TITLE_Y_1 = 740;
    const int RESULT_CLEAR_SELECT_TITLE_Y_2 = 810;
    //�Q�[���I�[�o�[��
    //���U���g�V�[������v���C�V�[����I��
    const int RESULT_MISS_SELECT_PLAY_X_1 = 850;
    const int RESULT_MISS_SELECT_PLAY_X_2 = 1050;
    const int RESULT_MISS_SELECT_PLAY_Y_1 = 530;
    const int RESULT_MISS_SELECT_PLAY_Y_2 = 600;
    //���U���g�V�[������^�C�g���V�[����I��
    const int RESULT_MISS_SELECT_TITLE_X_1 = 700;
    const int RESULT_MISS_SELECT_TITLE_X_2 = 1250;
    const int RESULT_MISS_SELECT_TITLE_Y_1 = 660;
    const int RESULT_MISS_SELECT_TITLE_Y_2 = 730;

    //�|�[�Y�V�[��
    //�|�[�Y�V�[������v���C�V�[����I��
    const int PAUSE_SELECT_PLAY_X_1 = 750;
    const int PAUSE_SELECT_PLAY_X_2 = 1120;
    const int PAUSE_SELECT_PLAY_Y_1 = 520;
    const int PAUSE_SELECT_PLAY_Y_2 = 620;
    //�|�[�Y�V�[�����烊�g���C��I��
    const int PAUSE_SELECT_RETRY_X_1 = 750;
    const int PAUSE_SELECT_RETRY_X_2 = 1000;
    const int PAUSE_SELECT_RETRY_Y_1 = 635;
    const int PAUSE_SELECT_RETRY_Y_2 = 735;
    //�|�[�Y�V�[������^�C�g���V�[����I��
    const int PAUSE_SELECT_TITLE_X_1 = 750;
    const int PAUSE_SELECT_TITLE_X_2 = 1230;
    const int PAUSE_SELECT_TITLE_Y_1 = 755;
    const int PAUSE_SELECT_TITLE_Y_2 = 855;

    //�J���[
    const int COLOR_WHITE = GetColor(255,255,255);       //��
    const int COLOR_TEXT_BOX = GetColor(120, 120, 120);  //�e�L�X�g�ɂ��Ԃ��鎞�̐F
    const int COLOR_TITLE_BACK = GetColor(23, 23, 22);   //�^�C�g���w�i�̐F
    const int PAUSE_BACK_FADE = 180;                    //�|�[�Y��ʔw�i�̃t�F�[�h
    const int TUTORIAL_TEXT_FADE_FADE = 120;            //�`���[�g���A���̃e�L�X�g�w�i�ƁA���Ԃ���BOX�̃t�F�[�h
};

