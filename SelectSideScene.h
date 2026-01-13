#ifndef SELECTSIDESCENE_H
#define SELECTSIDESCENE_H

#include <memory>

#include "Scene.h"
#include "SceneDataTransfer.h"
#include "RectLayout.h"

class SelectSideScene : public Scene {

public:

    inline SelectSideScene(Game* game, std::shared_ptr<SceneDataTransfer> sceneDataTransfer) 
	: Scene(game), mSceneDataTransfer(sceneDataTransfer) {}

    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override; 

private:

    SDL_Point mMousePosition;

    std::shared_ptr<SceneDataTransfer> mSceneDataTransfer;
    std::unique_ptr<RectLayout> mScreenLayout;
    std::unique_ptr<RectLayout> mCrossLayout;
    std::unique_ptr<RectLayout> mCircleLayout;
    std::unique_ptr<RectLayout> mTextLayout;
};

#endif
