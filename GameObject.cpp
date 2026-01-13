#include "GameObject.h"
#include <algorithm>

GameObject::GameObject(){
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
    mTag = "";
    mActive = true;
}

GameObject::GameObject(SDL_Point size){
    mSize = size;
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
    mTag = "";
    mActive = true;
}

GameObject::GameObject(SDL_Point size, SDL_Point position){
    mSize = size;
    mPosition = position;
    OnEnter = nullptr;
    OnExit = nullptr;
    OnStay = nullptr;
    OnClick = nullptr;
    mQueryOnly = false;
    mCollidingGameObject = nullptr;
    mTag = "";
    mActive = true;
}

int GameObject::GetGameObjectID(){
    return mGameObjectID;
}

void GameObject::SetGameObjectID(int gameObjectID){
    mGameObjectID = gameObjectID;
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

void GameObject::SetTag(std::string& tag){
    mTag = tag;
}

std::string GameObject::GetTag(){
    return mTag;
}

void GameObject::SetActive(bool active){
    mActive = active;
}

bool GameObject::GetActive(){
    return mActive;
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
