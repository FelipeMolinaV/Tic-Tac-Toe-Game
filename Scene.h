#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>
#include "SceneType.h"
#include <functional>

class Scene{
public:
    virtual ~Scene() = default;
    std::function<void(SceneType)> RequestChangeScene;
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
};

#endif 
