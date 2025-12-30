#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <vector>
#include <memory>

#include "GameObject.h"

void HandleCollision(bool collisionState, std::shared_ptr<GameObject>& gameObject_a, std::shared_ptr<GameObject>& gameObject_b){

    if (collisionState){

	if (!gameObject_a->HasCollision(gameObject_b->GetGameObjectID())){
	    gameObject_a->AddCollision(gameObject_b->GetGameObjectID());

	    if (gameObject_a->OnEnter != nullptr){
		gameObject_a->OnEnter(gameObject_b);
	    }
	}
	else {

	    gameObject_a->mCollidingGameObject = gameObject_b;

	    if (gameObject_a->OnStay != nullptr){
		gameObject_a->OnStay(gameObject_b);
	    }
	}

	if (!gameObject_b->HasCollision(gameObject_a->GetGameObjectID())){
	    gameObject_b->AddCollision(gameObject_a->GetGameObjectID());

	    if (gameObject_b->OnEnter != nullptr){
		gameObject_b->OnEnter(gameObject_a);
	    }
	}
	else {

	    gameObject_b->mCollidingGameObject = gameObject_a;

	    if (gameObject_b->OnStay != nullptr){
		gameObject_b->OnStay(gameObject_a);
	    }
	}
    }
    else {

	if (gameObject_a->HasCollision(gameObject_b->GetGameObjectID())){
	    gameObject_a->RemoveCollision(gameObject_b->GetGameObjectID());
	    gameObject_a->mCollidingGameObject = nullptr;

	    if (gameObject_a->OnExit != nullptr){
		gameObject_a->OnExit(gameObject_b);
	    }
	}

	if (gameObject_b->HasCollision(gameObject_a->GetGameObjectID())){
	    gameObject_b->RemoveCollision(gameObject_a->GetGameObjectID());
	    gameObject_b->mCollidingGameObject = nullptr;

	    if (gameObject_b->OnExit != nullptr){
		gameObject_b->OnExit(gameObject_a);
	    }
	}
    }
}


void CheckCollisions(std::vector<std::shared_ptr<GameObject>>& gameObjects){

    auto isColliding = [](std::shared_ptr<GameObject>& a, std::shared_ptr<GameObject>& b){

	const auto& posA = a->GetPosition();
	const auto& sizeA = a->GetSize();
	const auto& posB = b->GetPosition();
	const auto& sizeB = b->GetSize();

	return !(posA.x + sizeA.x < posB.x ||
		 posB.x + sizeB.x < posA.x ||
		 posA.y + sizeA.y < posB.y ||
		 posB.y + sizeB.y < posA.y);
    };

    auto isCursorOverObject = [](std::shared_ptr<GameObject>& cursor, std::shared_ptr<GameObject>& obj){

	const auto& cursorPos = cursor->GetPosition(); 
	const auto& objPos = obj->GetPosition();
	const auto& objSize = obj->GetSize();

	return (cursorPos.x >= objPos.x &&
		cursorPos.x <= objPos.x + objSize.x &&
		cursorPos.y >= objPos.y &&
		cursorPos.y <= objPos.y + objSize.y);
    };

    for (size_t i = 0; i < gameObjects.size(); i++){
	for (size_t j = i+1; j < gameObjects.size(); j++){

	    auto& gameObject_a = gameObjects[i];
	    auto& gameObject_b = gameObjects[j];
	    bool collision;

	    if (!gameObject_a->GetCollisionState() || !gameObject_b->GetCollisionState()){
		continue;
	    }

	    if (gameObject_a->IsQueryOnly() || gameObject_b->IsQueryOnly()){
		if (gameObject_a->IsQueryOnly()){
		    collision = isCursorOverObject(gameObject_a, gameObject_b); 
		}
		else {
		    collision = isCursorOverObject(gameObject_b, gameObject_a); 	
		}
	    }
	    else {
		collision = isColliding(gameObject_a, gameObject_b);
	    }

	    HandleCollision(collision, gameObject_a, gameObject_b);
	}
    }
}

#endif
