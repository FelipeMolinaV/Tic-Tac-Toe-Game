#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <unordered_map>
#include <string>
#include <memory>

#include <SDL3/SDL.h>
#include "Game.h"
#include "SceneType.h"
#include "Asset.h"
#include "Timer.h"

// TODO: RequestSprite(AssetID...) change asset id from other identifier
#include "AssetID.h"
#include "Sprite.h"

template<typename T>
using RequestGameObjectFunction = std::function<std::shared_ptr<T>(int)>;

class Scene{
public:

    inline Scene(Game* game) : mGame(game) {}

    virtual ~Scene() = default;

    std::function<void(SceneType)> RequestChangeScene;
    std::function<void(std::function<void(SDL_Event)>)> RequestInput;
    std::function<void(std::function<void()>)> RequestRender;
    std::function<std::shared_ptr<Texture>(int)> RequestTexture;
    RequestGameObjectFunction<Sprite> RequestSprite;
    std::function<void(std::vector<std::shared_ptr<GameObject>>)> RequestCheckCollisions;

    virtual void OnEnter() = 0;
    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;

protected:

    Game* mGame;
    std::unordered_map<std::string, std::shared_ptr<Sprite>> sprites;
    SDL_Point mousePosition;
    bool mouseClick;
    enum class Layers : int;
    Timer timer;

};

#endif 
