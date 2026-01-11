#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <array>
#include <memory>
#include <utility>

#include "Scene.h"
#include "Sprite.h"
#include "Utils.h"
#include "GameLogic.h"
#include "AIController.h"
#include "RectLayout.h"

using key_sprite = std::pair<std::string, std::shared_ptr<Sprite>>;


class GameScene : public Scene {
    
public:

    inline GameScene(Game* game) : Scene(game) {}
    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override; 

private:

    PlayerData mPlayer;
    PlayerData mAdversary;
    PlayerData mCurrentPlayer;
    GameData mGameData;
    SDL_Point mousePosition;
    Timer mTimer;
    std::vector<key_sprite> pendingSprites;
    std::unique_ptr<AIController> mAIController;

    void GenerateGrid(int widthGap, int heightGap);
};

#endif
