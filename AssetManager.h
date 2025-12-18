#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL3/SDL.h>
#include <unordered_map>
#include <memory>
#include <string>

#include "Asset.h"
#include "Game.h"
#include "AssetFactory.h"

using asset_map = std::unordered_map<std::string, std::shared_ptr<Asset>>;

class Game;
class AssetFactory;

class AssetManager{

public:

    AssetManager(Game* game);
    void LoadAssets(std::string path);
    std::shared_ptr<Asset> GetAsset(std::string key);

private:

    std::unordered_map<std::string, asset_map> mAssets; 
    std::unique_ptr<AssetFactory> mAssetFactory;

};

#endif
