#include "Scene.h"

#include "Text.h"

void Scene::ClearData(){
    for (auto& [key, value] : mGameObjects){
	value.clear();
    }
    mGameObjects.clear();
    pendingGameObjects.clear();
    mRenderableObjects.clear();
}

void Scene::FlushPendingGameObjects(){
    for (auto& [type, container] : pendingGameObjects){
	for (auto& [key, gameObject] : container){
	    mGameObjects[type][key] = gameObject;

	    if (type == "Sprite"){
		mRenderableObjects.push_back(static_pointer_cast<Sprite>(gameObject));
	    }
	    else if (type == "Text"){
		mRenderableObjects.push_back(static_pointer_cast<Text>(gameObject));
	    }

	}
	container.clear();
    }
    pendingGameObjects.clear();
}

std::vector<std::shared_ptr<Renderable>> Scene::GetRenderableObjects(){
    return mRenderableObjects;
}


