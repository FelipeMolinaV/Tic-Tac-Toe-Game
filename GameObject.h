#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <vector>
#include <functional>
#include <memory>


// TODO: Make more easy to active or deactivate all the collision feature
class GameObject{

public:

    GameObject();
    GameObject(SDL_Point size);
    GameObject(SDL_Point size, SDL_Point position);
    virtual ~GameObject() = default;

    int GetGameObjectID();
    void SetGameObjectID(int gameObjectID);

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

    void SetTag(std::string& tag);
    std::string GetTag();

    void SetActive(bool active);
    bool GetActive();

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
    std::string mTag;
    bool mActive;

protected:

    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;

};

#endif
