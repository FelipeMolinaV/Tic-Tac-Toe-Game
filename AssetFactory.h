#ifndef ASSETFACTORY_H
#define ASSETFACTORY_H

#include <SDL3/SDL.h>
#include <memory>
#include <nlohmann/json.hpp>

#include "Game.h"
#include "Asset.h"

using json = nlohmann::json;

class Game; 

class AssetFactory{

public:

    AssetFactory(Game* game);
    std::shared_ptr<Asset> CreateAsset(json& data);

private:

    Game* mGame;
};

#endif
