#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <unordered_map>
#include <string>

#include <SDL3/SDL.h>
#include "Game.h"
#include "SceneType.h"
#include "AssetID.h"

template<typename T>
using RequestAssetFunction = std::function<std::shared_ptr<T>(int)>;

class Scene{
public:

    inline Scene(Game* game) : mGame(game) {}

    virtual ~Scene() = default;
    std::function<void(SceneType)> RequestChangeScene;

    RequestAssetFunction<Sprite> RequestSprite;

    virtual void OnEnter() = 0;
    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;

protected:

    Game* mGame;
    std::unordered_map<std::string, std::shared_ptr<Sprite>> sprites;

};

#endif 
