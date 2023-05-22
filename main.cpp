#include "stdafx.h"

#include "Game.h"
#include "Entity.h"

int main( int, char** )
{
	GS_Game* game = GS_Game::getInstance();
	if ( !game )
	{
		std::cout << "Impossible to create GS_Game instance." << std::endl;
		return -1;
	}

	game->init();

	while ( game->isRunning() )
	{
		game->update();
		if ( game->shouldRestart() )
		{
			game->reInit();
		}
	}
	game->shutDown();
	return 0;
}

