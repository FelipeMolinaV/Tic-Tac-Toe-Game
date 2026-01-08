#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <type_traits>
#include <SDL3/SDL.h>

#include "Game.h"
#include "SceneType.h"
#include "Asset.h"
#include "Timer.h"
#include "AssetID.h"
#include "Sprite.h"
#include "GameState.h"
#include "Texture.h"
#include "FontAtlas.h"
#include "Renderable.h"

template<typename T>
using RequestGameObjectFunction = std::function<std::shared_ptr<T>(int)>;

class Scene{
public:

    inline Scene(Game* game) : mGame(game) {}

    virtual ~Scene() = default;

    std::function<void(SceneType)> RequestSceneChange;
    std::function<void(std::function<void(SDL_Event)>)> RequestInput;
    std::function<void(std::function<void()>)> RequestRender;
    std::function<void(std::vector<std::shared_ptr<GameObject>>)> RequestCheckCollisions;
    std::function<void(GameState)> RequestGameStateChange;

    std::function<std::shared_ptr<Texture>(int)> RequestTexture;
    std::function<std::shared_ptr<FontAtlas>(int)> RequestFontAtlas;


    virtual void OnEnter() = 0;
    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;
    
private:

    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<GameObject>>> pendingGameObjects;
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<GameObject>>> mGameObjects;
    std::vector<std::shared_ptr<Renderable>> mRenderableObjects;

protected:

    Game* mGame;

    enum class Layers : int;

    void ClearData();

    std::vector<std::shared_ptr<Renderable>> GetRenderableObjects();

    void FlushPendingGameObjects();

    template <class T, class... Args>
    std::shared_ptr<T> Create(std::string_view key, Args&&... args){

	static_assert(std::is_base_of_v<GameObject, T>, "T must inherit from GameObject");

	if (mGameObjects[T::TypeName].contains(std::string(key))){
	    return nullptr;
	}

	std::shared_ptr<T> newGameObject = mGame->GetGameObjectFactory()->CreateGameObject<T>(std::forward<Args>(args)...);
	pendingGameObjects[T::TypeName][std::string(key)] =  newGameObject;

	std::cout << "-------------" << std::endl;
	std::cout << "ID  : " << newGameObject->GetGameObjectID() << std::endl;
	std::cout << "KEY : " << key << std::endl;
	std::cout << "SIZE: " << newGameObject->GetSize().x << " " << newGameObject->GetSize().y << std::endl; 
	std::cout << "POS : " << newGameObject->GetPosition().x << " " << std::endl;
	std::cout << "COLLISION STATE: " << newGameObject->GetCollisionState() << std::endl;
	std::cout << "QUERY ONLY: " << newGameObject->IsQueryOnly() << std::endl;
	std::cout << "LAYER     : " << newGameObject->GetLayer() << std::endl;
	std::cout << "ALPHA     : " << newGameObject->GetAlpha() << std::endl;

	return newGameObject;
    }

    template <class T>
    std::shared_ptr<T> GetGameObject(const std::string& key){
	static_assert(std::is_base_of_v<GameObject, T>, "T must inherit from GameObject");
	return static_pointer_cast<T>(mGameObjects[T::TypeName][key]);
    }

    template <class T>
    std::shared_ptr<T> GetGameObject(int gameObjectID){
	static_assert(std::is_base_of_v<GameObject, T>, "T must inherit from GameObject");
	for (auto& [keyContainer, container] : mGameObjects){
	    if (keyContainer != T::TypeName) continue;
	    for (auto& [keyGameObject, gameObject] : container){
		if (gameObject->GetGameObjectID() == gameObjectID){
		    return static_pointer_cast<T>(gameObject);
		}
	    }
	}
	return nullptr;
    }


    template <class T>
    std::unordered_map<std::string, std::shared_ptr<GameObject>> GetGameObjects(){
	return mGameObjects[T::TypeName];
    }


};

#endif 
