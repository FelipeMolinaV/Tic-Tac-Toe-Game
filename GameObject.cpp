#include "GameObject.h"
#include <algorithm>

GameObject::GameObject(int gameObjectID){
    mGameObjectID = gameObjectID;
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
}

GameObject::GameObject(int gameObjectID, SDL_Point size){
    mGameObjectID = gameObjectID;
    mSize = size;
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
}

GameObject::GameObject(int gameObjectID, SDL_Point size, SDL_Point position){
    mGameObjectID = gameObjectID;
    mSize = size;
    mPosition = position;
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
}

int GameObject::GetGameObjectID(){
    return mGameObjectID;
}

std::vector<int> GameObject::GetCollisions(){
    return mCollisions;
}

void GameObject::AddCollision(int gameObjectID){
    mCollisions.push_back(gameObjectID);
}

void GameObject::RemoveCollision(int gameObjectID){
    std::erase(mCollisions, gameObjectID);
}

bool GameObject::HasCollision(int gameObjectID){

    auto pointer = std::find(mCollisions.begin(), mCollisions.end(), gameObjectID);

    return pointer != mCollisions.end();

}

std::shared_ptr<GameObject> GameObject::GetCollidingGameObject(){
    return mCollidingGameObject; 
}

SDL_Point& GameObject::GetSize(){
    return mSize;
}

void GameObject::SetSize(int w, int h){
    mSize.x = w;
    mSize.y = h;
}

SDL_Point& GameObject::GetPosition(){
    return mPosition;
}

void GameObject::SetPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

void GameObject::SetCollisionState(bool state){
    mCollisionState = state;
}

bool GameObject::GetCollisionState(){
    return mCollisionState;
}

void GameObject::SetQueryOnly(bool state){
    mQueryOnly = state;
}

bool GameObject::IsQueryOnly(){
    return mQueryOnly;
}
