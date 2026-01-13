#ifndef SCENEDATATRANSFER_H
#define SCENEDATATRANSFER_H

#include <optional>
#include <type_traits>
#include <cassert>

#include "Utils.h"

class SceneDataTransfer{

public:

    template<class T>
    bool SendData(T data){
	if (std::is_same_v<T, GameData>) {
	    mGameData = data;
	    return true;
	}
	return false;
    };
    
    template<class T>
    T GetData(){
	if (std::is_same_v<T, GameData> && mGameData.has_value()) {
	    GameData data = mGameData.value();
	    mGameData.reset();
	    return data;
	}

	return T{};
    };

private:

    std::optional<GameData> mGameData;

};

#endif
