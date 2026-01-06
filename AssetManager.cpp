#include "AssetManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#include "AssetFactory.h"

using json = nlohmann::json;

AssetManager::AssetManager(Game* game){

    if (game == nullptr){
	throw std::runtime_error("Null pointer passed to game");
    }	

    mAssetFactory = std::make_unique<AssetFactory>(game);
}

void AssetManager::LoadAssets(std::string path){

    std::ifstream file(path);	
    json data = json::parse(file);
    file.close();

    // TODO: Make dynamic

    auto& textures = data["textures"];

    for (auto& textureInfo : textures){
	int assetId = textureInfo.at("asset_id").get<int>();
	mAssets[assetId] = mAssetFactory->CreateAsset(textureInfo); 
    }
}


