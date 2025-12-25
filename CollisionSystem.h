#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <vector>
#include <memory>

#include "GameObject.h"

void HandleCollision(bool collisionState, std::shared_ptr<GameObject> gameObject_a, std::shared_ptr<GameObject> gameObject_b){

    if (collisionState){

	if (!gameObject_a->HasCollision(gameObject_b->GetGameObjectID())){
	    gameObject_a->AddCollision(gameObject_b->GetGameObjectID());

	    if (gameObject_a->OnEnter != nullptr){
		gameObject_a->OnEnter();
	    }
	}

	if (!gameObject_b->HasCollision(gameObject_a->GetGameObjectID())){
	    gameObject_b->AddCollision(gameObject_a->GetGameObjectID());

	    if (gameObject_b->OnEnter != nullptr){
		gameObject_b->OnEnter();
	    }
	}
    }
    else {

	if (gameObject_a->HasCollision(gameObject_b->GetGameObjectID())){
	    gameObject_a->RemoveCollision(gameObject_b->GetGameObjectID());

	    if (gameObject_a->OnExit != nullptr){
		gameObject_a->OnExit();
	    }
	}

	if (gameObject_b->HasCollision(gameObject_a->GetGameObjectID())){
	    gameObject_b->RemoveCollision(gameObject_a->GetGameObjectID());

	    if (gameObject_b->OnExit != nullptr){
		gameObject_b->OnExit();
	    }
	}
    }
}


void CheckCollisions(std::vector<std::shared_ptr<GameObject>>& gameObjects){

    auto isColliding = [](std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b){

	auto posA = a->GetPosition();
	auto sizeA = a->GetSize();
	auto posB = b->GetPosition();
	auto sizeB = b->GetSize();

	return !(posA.x + sizeA.x <= posB.x ||
		 posB.x + sizeB.x <= posA.x ||
		 posA.y + sizeA.y <= posB.y ||
		 posB.y + sizeB.y <= posA.y);
    };

    for (size_t i = 0; i < gameObjects.size(); i++){
	for (size_t j = i+1; j < gameObjects.size(); j++){
	    auto& gameObject_a = gameObjects[i];
	    auto& gameObject_b = gameObjects[j];
	    HandleCollision(isColliding(gameObject_a, gameObject_b), gameObject_a, gameObject_b);
	}
    }
}

#endif
