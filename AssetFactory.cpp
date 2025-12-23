#include "AssetFactory.h"

#include "Sprite.h"

AssetFactory::AssetFactory(Game* game) : mGame(game) {};

std::shared_ptr<Asset> AssetFactory::CreateAsset(json& data){

    std::string type = data.at("type").get<std::string>();

    if (type == "sprite"){

	std::string path = data.at("path").get<std::string>();
	int width = data.at("width").get<int>();
	int height = data.at("height").get<int>();
	
	SDL_Point size = { width, height }; 
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(mGame->GetRenderer(), path, size);
	return sprite; 

    }

    return nullptr;

}
