#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL3/SDL.h>
#include "Game.h"
#include "Scene.h"
#include "SceneType.h"
#include <vector>

class Game;

class SceneManager{

public:

    SceneManager(Game* game);
    ~SceneManager();
    bool SetScene(SceneType type);
    void Update();

private:

    Game* mGame;
    Scene* currentScene;
};

#endif
