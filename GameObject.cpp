#include "GameObject.h"
#include <algorithm>

GameObject::GameObject(int gameObjectID){
    mGameObjectID = gameObjectID;
}

GameObject::GameObject(int gameObjectID, SDL_Point size){
    mGameObjectID = gameObjectID;
    mSize = size;
}

GameObject::GameObject(int gameObjectID, SDL_Point size, SDL_Point position){
    mGameObjectID = gameObjectID;
    mSize = size;
    mPosition = position;
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
