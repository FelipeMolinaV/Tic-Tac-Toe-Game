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
#include "Font.h"
#include "FontAtlas.h"
#include "AssetID.h"


class Game;
class AssetFactory;

class AssetManager{

public:

    AssetManager(Game* game);
    ~AssetManager();
    void LoadAssets(std::string path);

    template <class T>
    std::shared_ptr<T> GetAsset(int assetId){
	static_assert(std::is_base_of_v<Asset, T>, "T must inherit from Asset");
	std::shared_ptr<Asset> asset = mAssets[assetId];
	if (asset == nullptr){
	    return nullptr;
	}	
	return std::static_pointer_cast<T>(asset);
    };


private:

    std::unordered_map<int, std::shared_ptr<Asset>> mAssets; 
    std::unique_ptr<AssetFactory> mAssetFactory;

};

#endif
