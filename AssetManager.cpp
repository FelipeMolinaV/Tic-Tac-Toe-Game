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

    auto& sprites = data["sprites"];

    for (auto& sprite : sprites){
	std::string key = sprite["key"];
	mAssets["sprite"][key] = mAssetFactory->CreateAsset(sprite); 
    }
}

std::shared_ptr<Asset> AssetManager::GetAsset(std::string key){
    // TODO: make dynamic
    return mAssets["sprite"][key];
}
