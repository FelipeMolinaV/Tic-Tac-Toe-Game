#include "AssetFactory.h"

#include "Texture.h"

AssetFactory::AssetFactory(Game* game) : mGame(game) {};

std::shared_ptr<Asset> AssetFactory::CreateAsset(json& data){

    std::string type = data.at("type").get<std::string>();

    if (type == "texture"){

	std::string path = data.at("path").get<std::string>();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(mGame->GetRenderer(), path);
	return texture; 
    }

    return nullptr;
}
