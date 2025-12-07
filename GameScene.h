#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

class GameScene : public Scene {
    
public:

    inline GameScene(Game* game) : Scene(game) {}
    void OnEnter() override;
    void Update() override;
    void OnExit() override;
};

#endif
