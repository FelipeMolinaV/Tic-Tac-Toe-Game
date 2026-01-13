#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <optional>

#include "Game.h"
#include "Scene.h"
#include "SceneType.h"
#include "SceneDataTransfer.h"

class Game;

class SceneManager{

public:

    SceneManager(Game* game);
    bool SetScene(SceneType type);
    void Tick();

private:

    Game* mGame;
    std::unique_ptr<Scene> mCurrentScene;
    std::optional<SceneType> mNextScene;
    std::shared_ptr<SceneDataTransfer> mSceneDataTransfer;
};

#endif
