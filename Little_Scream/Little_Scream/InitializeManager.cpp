#include "DxLib.h"
#include "Player.h"
#include "Collision.h"
#include "Enemy.h"
#include "ControlGemObject.h"
#include "Stage.h"
#include "CheckClear.h"
#include "HelpfulItems.h"
#include "Pause.h"
#include"Camera.h"
#include"Light.h"
#include"SkyDome.h"
#include "InitializeManager.h"

void InitializeManager::playSceneInitialize(Player& player, Collision& collision, Enemy& enemy, ControlGemObject& ControlGemObject,Stage stage,CheckClear& checkClear, HelpfulItems& helpfulItems,Pause& pause,Camera& camera,Light& light,SkyDome& skyDome)
{
    //äeéÌÉNÉâÉXÇÃèâä˙âª
    player.initialize();
    enemy.initialize();
    collision.initialize();
    ControlGemObject.initialize(stage);
    checkClear.initialize();
    helpfulItems.initialize();
    enemy.createWaypointAndEdge(stage, player.getPosition());
    pause.initialize();
    camera.mainCamera(player);
    light.setPlayerLight(player);
    skyDome.setPosition(player);
}