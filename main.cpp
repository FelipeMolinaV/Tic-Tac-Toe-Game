#include <SDL3/SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]){
    
    Game game(640, 480);

    if ( !game.Init() ){
	std::cout << "Failed to initialize the game";	
    }
    else {
	game.Run();
    }

    return 0;
}
