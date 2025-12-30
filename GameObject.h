#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <vector>
#include <functional>
#include <memory>

class GameObject{

public:

    GameObject(int gameObjectID);
    GameObject(int gameObjectID, SDL_Point size);
    GameObject(int gameObjectID, SDL_Point size, SDL_Point position);

    int GetGameObjectID();
    void AddCollision(int gameObjectID);
    void RemoveCollision(int gameObjectID);
    std::vector<int> GetCollisions();
    bool HasCollision(int gameObjectID);
    std::shared_ptr<GameObject> GetCollidingGameObject();
    std::shared_ptr<GameObject> mCollidingGameObject;

    SDL_Point& GetSize();
    void SetSize(int w, int h);
    SDL_Point& GetPosition();
    void SetPosition(int x, int y);

    void SetCollisionState(bool state);
    bool GetCollisionState();

    void SetQueryOnly(bool state);
    bool IsQueryOnly();

    std::function<void(std::shared_ptr<GameObject>)> OnEnter;
    std::function<void(std::shared_ptr<GameObject>)> OnExit;
    std::function<void(std::shared_ptr<GameObject>)> OnStay;
    std::function<void()> OnClick;

private:

    int mGameObjectID;
    std::vector<int> mCollisions;
    bool mCollisionState;
    bool mQueryOnly;

protected:

    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;

};

#endif
