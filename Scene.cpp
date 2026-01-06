#include "Scene.h"

void Scene::ClearGameObjects(){
    for (auto& [key, value] : mGameObjects){
	value.clear();
    }
    mGameObjects.clear();
}

void Scene::FlushPendingGameObjects(){
    for (auto& [keyContainer, container] : pendingGameObjects){
	for (auto& [keyMap, gameObject] : container){
	    mGameObjects[keyContainer][keyMap] = gameObject;
	}
	container.clear();
    }
    pendingGameObjects.clear();
}


