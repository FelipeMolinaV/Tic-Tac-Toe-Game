#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <memory>
#include <utility>
#include <type_traits>

#include "GameObject.h"

class GameObjectFactory{

public:

    GameObjectFactory() : countID(-1) {};

    template <class T, class... Args>
    std::shared_ptr<T> CreateGameObject(Args&&... args){
	static_assert(std::is_base_of_v<GameObject, T>, "T must inherit from GameObject");
	std::shared_ptr<T> newGameObject = std::make_shared<T>(std::forward<Args>(args)...);
	newGameObject->SetGameObjectID(++countID);
	return newGameObject;
    }

    template <class T, class... Args>
    T CreateRawGameObject(Args&&... args){
	static_assert(std::is_base_of_v<GameObject, T>, "T must inherit from GameObject");
	T newGameObject = T(std::forward<Args>(args)...);
	newGameObject.SetGameObjectID(++countID);
	return newGameObject;
    }
    

private:

    int countID;

};

#endif 
