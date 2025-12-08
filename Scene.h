#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>
#include "Game.h"
#include "SceneType.h"
#include <functional>

class Scene{
public:

    inline Scene(Game* game) : mGame(game) {}

    virtual ~Scene() = default;
    std::function<void(SceneType)> RequestChangeScene;
    virtual void OnEnter() = 0;
    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;

protected:

    Game* mGame;
};

#endif 
