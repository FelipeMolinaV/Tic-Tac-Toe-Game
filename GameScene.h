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
#include "SceneDataTransfer.h"

using key_sprite = std::pair<std::string, std::shared_ptr<Sprite>>;


class GameScene : public Scene {
    
public:

    inline GameScene(Game* game, std::shared_ptr<SceneDataTransfer> sceneDataTransfer) 
	: Scene(game), mSceneDataTransfer(sceneDataTransfer) {}
    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override; 

private:

    PlayerData mCurrentPlayer;
    GameData mGameData;
    SDL_Point mousePosition;
    Timer mTimer;

    std::vector<key_sprite> pendingSprites;
    std::unique_ptr<AIController> mAIController;
    std::shared_ptr<SceneDataTransfer> mSceneDataTransfer;

    // vector to deactivate al pieces
    std::vector<std::shared_ptr<GameObject>> mPieces;

    // unordered_map to restore cellID
    std::unordered_map<std::shared_ptr<GameObject>, std::shared_ptr<Cell>> mGameObjectOnBoard;

    std::unique_ptr<RectLayout> mScreenLayout;
    std::unique_ptr<RectLayout> mLeftColumnLayout;
    std::unique_ptr<RectLayout> mRightColumnLayout;
    std::unique_ptr<RectLayout> mCenterColumnLayout;

    void ConfigureGameData();
    void GenerateLayouts();
    void GenerateBoard();
    void GenerateSprites();
    void CreatePieces();
    void DeactivatePieces();
    void AddGameObjectToBoard(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Cell> cell);
    std::shared_ptr<Cell> GetCellFromGameObject(std::shared_ptr<GameObject> gameObject);
    void GenerateTexts();
    void ForEachCell(std::function<void(int, int)> function);
    void SetCurrentPlayer(PlayerData& player);
    void UpdatePoints();
    void HandleGameState(GameData gameData);
};

#endif
