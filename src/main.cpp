#include "Game.hpp"
#include <assert.h>

int main() {
	PattyEngine::Game* game = new PattyEngine::Game(1920,1080);
	assert(game);
	PattyEngine::setGame(game);

	//Start up SDL and create window
	if(!game->init("Supermassive Omega")) printf("Failed to initialize!\n");
	else {
		//Load media
		if(!game->loadMedia()) printf("Failed to load media!\n");
		else game->run();
	}

	game->close();

	delete game;

	return 0;
}
