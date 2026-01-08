#include "AssetFactory.h"

#include "Texture.h"
#include "FontAtlas.h"

AssetFactory::AssetFactory(Game* game) : mGame(game) {};

std::shared_ptr<Asset> AssetFactory::CreateAsset(json& data){

    std::string type = data.at("type").get<std::string>();

    if (type == "texture"){

	std::string path = data.at("path").get<std::string>();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(mGame->GetRenderer(), path);
	return texture; 
    }
    else if (type == "font_atlas"){

	std::string path = data.at("path").get<std::string>();
	int pixelSize = data.at("pixel_size").get<int>();
	Uint8 red = data.at("red").get<Uint8>();
	Uint8 green = data.at("green").get<Uint8>();
	Uint8 blue = data.at("blue").get<Uint8>();
	Uint8 alpha = data.at("alpha").get<Uint8>();

	SDL_Color fg = {red, green, blue, alpha};

	std::shared_ptr<FontAtlas> fontAtlas = std::make_shared<FontAtlas>(mGame->GetRenderer(), path, pixelSize, fg);
	return fontAtlas;
    }

    return nullptr;
}
