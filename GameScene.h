#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <array>
#include <memory>
#include <utility>

#include "Scene.h"
#include "Sprite.h"

using key_sprite = std::pair<std::string, std::shared_ptr<Sprite>>;

struct CellData{
    bool state;
    int gameObjectID; 
};


class GameScene : public Scene {
    
public:

    inline GameScene(Game* game) : Scene(game) {}
    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override; 

private:

    std::array<std::array<std::shared_ptr<CellData>, 3>, 3> grid;
    std::vector<key_sprite> pendingSprites;
    bool playerTurn;

    void GenerateGrid(int widthGap, int heightGap);

};

#endif
