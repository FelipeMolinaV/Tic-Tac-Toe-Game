#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <memory>

#include "Scene.h"
#include "RectLayout.h"
#include "Utils.h"

const int ORIGEN_X = 0;
const int ORIGEN_Y = 0;
const int PADDING_X = 20;
const int PADDING_Y = 20;

class TestScene : public Scene {


public:

    inline TestScene(Game* game) : Scene(game) {}
    void OnEnter() override;
    void Input() override;
    void Update() override;
    void Render() override;
    void OnExit() override; 

private:
    
    std::unique_ptr<RectLayout> mScreenLayout;
    std::unique_ptr<RectLayout> mLeftColumn;
    std::unique_ptr<RectLayout> mRightColumn;
    std::unique_ptr<RectLayout> mCenterColumn;
};

#endif
