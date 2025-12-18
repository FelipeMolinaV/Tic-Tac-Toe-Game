#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Sprite.h"

class GameScene : public Scene {
    
public:

    inline GameScene(Game* game) : Scene(game) {}
    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override;

};

#endif
