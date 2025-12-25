#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <vector>
#include <functional>

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

    SDL_Point& GetSize();
    void SetSize(int w, int h);
    SDL_Point& GetPosition();
    void SetPosition(int x, int y);

    std::function<void()> OnEnter;
    std::function<void()> OnExit;

private:

    int mGameObjectID;
    std::vector<int> mCollisions;

protected:

    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;

};

#endif
