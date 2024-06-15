#include "Core/stdafx.h"

int main( int, char** )
{
	JobSystem::Initialize();

	GS_Game* game = GS_Game::getInstance();
	if ( !game )
	{
		std::cout << "Impossible to create GS_Game instance." << std::endl;
		return -1;
	}

	game->init();

	while ( game->isRunning() )
	{
#ifdef _DEBUG
		OPTICK_FRAME( "MainThread" );
#endif // _DEBUG

		game->update();
		if ( game->shouldRestart() )
		{
			game->reInit();
		}
	}
	game->shutDown();
	return 0;
}

