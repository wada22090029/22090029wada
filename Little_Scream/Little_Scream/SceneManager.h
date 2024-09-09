#pragma once
class Camera;
class Light;
class Draw;
class Stage;
class Player;
class Enemy;
class ControlGemObject;
class Collision;
class Title;
class CheckClear;
class Result;
class Pause;
class HelpfulItems;
class ControlFade;
class Tutorial;
class CheckDevice;
class Compass;
class SkyDome;
class ControlFont;
class ControlSound;

class SceneManager
{
private:
	int sceneKeeper;	//�V�[���ړ��O��1���ۑ��p
public:
	SceneManager();
	~SceneManager();

	//�^�C�g���V�[��
	void controlTitleScene(Title& title,int& scene, ControlFade &controlFade, CheckDevice checkDevice,ControlSound& sound);
	//�|�[�Y�V�[��
	void controlPauseScene(Pause& pause, int& scene, ControlFade &controlFade, CheckDevice checkDevice, ControlSound& sound, ControlGemObject& controlGemObject, HelpfulItems& helpfulItems);
	//�v���C�V�[��
	void controlPlayScene(Camera& camera, Light& light, Player& player, Collision& collision, Stage stage,Enemy &enemy, ControlGemObject& controlGemObject,int&scene, CheckClear& checkClear, HelpfulItems& helpfulItems, ControlFade &controlFade,Pause &pause, Tutorial& tutorial, CheckDevice checkDevice,Compass &compass, SkyDome& skyDome, ControlSound& sound);
	//���U���g�V�[��
	void controlResultScene(Result& result, int& scene,ControlFade &controlFade, CheckDevice checkDevice, ControlSound& sound,CheckClear checkClear);
	//�t�F�[�h�V�[��
	void controlFadeScene(ControlFade &controlFade, int& scene);

	//�e�V�[���`��
	void drawPauseScene(ControlDraw ControlDraw, Pause pause, ControlFade controlFade) { ControlDraw.drawPause(pause, controlFade); }
	void drawPlayScene(ControlDraw ControlDraw, Stage stage, Player player,Enemy enemy, ControlGemObject controlGemObject, HelpfulItems helpfulItems, ControlFade controlFade, CheckClear checkClear, Tutorial tutorial,CheckDevice checkDevice,Compass compass, SkyDome skyDome,ControlFont font) { ControlDraw.drawPlay(stage, player,enemy,controlGemObject, helpfulItems, controlFade, checkClear, tutorial,checkDevice,compass, skyDome,font); }
	void drawTitleScene(ControlDraw ControlDraw, Title title, ControlFade controlFade) { ControlDraw.drawTitle(title, controlFade); }
	void drawResultScene(ControlDraw ControlDraw, Result result, CheckClear checkClear, ControlFade controlFade) { ControlDraw.drawResult(result,checkClear, controlFade); }
};

