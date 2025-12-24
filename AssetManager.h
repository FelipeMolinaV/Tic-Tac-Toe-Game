#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL3/SDL.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <type_traits>

#include "Asset.h"
#include "Game.h"
#include "AssetFactory.h"
#include "Texture.h"
#include "AssetID.h"

using asset_map = std::unordered_map<int, std::shared_ptr<Asset>>;

class Game;
class AssetFactory;

class AssetManager{

public:

    AssetManager(Game* game);
    void LoadAssets(std::string path);

    template<typename T>
    std::shared_ptr<T> GetAsset(int assetId){
	if (std::is_same_v<T, Texture>){
	    std::shared_ptr<Texture> texture = std::dynamic_pointer_cast<Texture>(mAssets["texture"][assetId]);
	    return texture; 
	}
    }

private:

    std::unordered_map<std::string, asset_map> mAssets; 
    std::unique_ptr<AssetFactory> mAssetFactory;

};

#endif
