#include "AssetFactory.h"

#include "Texture.h"
#include "Font.h"

AssetFactory::AssetFactory(Game* game) : mGame(game) {};

std::shared_ptr<Asset> AssetFactory::CreateAsset(json& data){

    std::string type = data.at("type").get<std::string>();

    if (type == "texture"){

	std::string path = data.at("path").get<std::string>();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(mGame->GetRenderer(), path);
	return texture; 
    }
    else if (type == "font"){

	std::string path = data.at("path").get<std::string>();
	int pixelSize = data.at("pixel_size").get<int>();
	std::shared_ptr<Font> font = std::make_shared<Font>(mGame->GetRenderer(), path, pixelSize);
	return font;
    }

    return nullptr;
}
