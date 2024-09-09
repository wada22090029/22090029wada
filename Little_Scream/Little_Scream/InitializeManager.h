#pragma once

class Player;
class Enemy;
class ControlGemObject;
class Collision;
class Stage;
class CheckClear;
class HelpfulItems;
class Pause;
class Camera;
class Light;
class SkyDome;

class InitializeManager
{
public:
    //Ç‹Ç∆ÇﬂÇƒèâä˙âª
    void playSceneInitialize(Player& player, Collision& collision, Enemy& enemy, ControlGemObject& ControlGemObject,Stage stage, CheckClear& checkClear, HelpfulItems& helpfulItems,Pause &pause, Camera& camera, Light& light,SkyDome&skyDome);
};

