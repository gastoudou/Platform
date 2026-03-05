#include "Core/stdafx.h"
#include "NERDGame.h"

#include "NERDSprite.h"
#include "DebugDrawSystem.h"

NERDGame::NERDGame()
{
}

NERDGame::~NERDGame()
{
	TTF_Quit();
	SDL_Quit();
}

bool NERDGame::initialize( int _w, int _h )
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
	TTF_Init();
	keyState = 0;
	window = SDL_CreateWindow( "Platform", _w, _h, 0 );
	if ( !window )
	{
		SDL_Log( "Failed SDL_CreateWindow: %s", SDL_GetError() );
		return false;
	}

	renderer = SDL_CreateRenderer( window, nullptr );
	if ( !renderer )
	{
		SDL_Log( "Failed SDL_CreateRenderer: %s", SDL_GetError() );
		return false;
	}

	lastTick = SDL_GetTicks();

	gameController = SDL_OpenJoystick( 0 );
	if ( !gameController )
	{
		SDL_Log( "Failed to open joystick: %s", SDL_GetError() );
	}

#ifdef _DEBUG
	DebugDrawSystem::getInstance()->init( renderer );
#endif // _DEBUG

	return true;
}

void NERDGame::shutdown()
{
	SDL_CloseJoystick( gameController );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
}

bool NERDGame::update()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
			case SDL_EVENT_QUIT:
				return false;
				break;
			case SDL_EVENT_KEY_DOWN:
				if ( event.key.key == SDLK_LEFT )
				{
					keyState |= NERD_KEY_LEFT;
				}
				else if ( event.key.key == SDLK_RIGHT )
				{
					keyState |= NERD_KEY_RIGHT;
				}
				else if ( event.key.key == SDLK_UP )
				{
					keyState |= NERD_KEY_UP;
				}
				else if ( event.key.key == SDLK_DOWN )
				{
					keyState |= NERD_KEY_DOWN;
				}
				break;
			case SDL_EVENT_KEY_UP:
				if ( event.key.key == SDLK_LEFT )
				{
					keyState &= ~NERD_KEY_LEFT;
				}
				else if ( event.key.key == SDLK_RIGHT )
				{
					keyState &= ~NERD_KEY_RIGHT;
				}
				else if ( event.key.key == SDLK_UP )
				{
					keyState &= ~NERD_KEY_UP;
				}
				else if ( event.key.key == SDLK_DOWN )
				{
					keyState &= ~NERD_KEY_DOWN;
				}
				break;

			case SDL_EVENT_JOYSTICK_AXIS_MOTION:
				joypads[ event.jaxis.which ][ event.jaxis.axis ] = event.jaxis.value;
				break;

			case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
				buttons[ event.jbutton.which ][ event.jbutton.button ] = event.jbutton.down;
				break;

			case SDL_EVENT_JOYSTICK_BUTTON_UP:
				buttons[ event.jbutton.which ][ event.jbutton.button ] = event.jbutton.down;
				break;

			default:
				break;
		}
	}

	{
		GS_RenderSystem::getInstance()->lock.lock();
		SDL_SetRenderDrawColor( renderer, 0x33, 0x99, 0xCC, 0xFF );
		SDL_RenderClear( renderer );
		GS_RenderSystem::getInstance()->lock.unlock();
	}

	return true;
}

void NERDGame::postUpdate() const
{
	// std::cout << __FUNCTION__ << std::endl;
	SDL_RenderPresent( renderer );
}

GS_Sprite* NERDGame::createSpriteFromBMP( const char* _path )
{
	GS_Sprite* sprite = new GS_Sprite( renderer );
	sprite->loadBMP( _path );
	return sprite;
}

float NERDGame::getElapsedTime()
{
#ifdef _DEBUG
	return 0.016f; // 60 fps
#else
	uint64_t diffTick = SDL_GetTicks() - lastTick;
	lastTick = SDL_GetTicks();
	return static_cast< float >(diffTick / 1000.0f);
#endif // _DEBUG
}

int NERDGame::getKeyState() const
{
	return keyState;
}

int NERDGame::getJoypadValueX( int id ) const
{
	return joypads[ id ][ 0 ];
}

int NERDGame::getJoypadValueY( int id ) const
{
	return joypads[ id ][ 1 ];
}

bool NERDGame::getJoypadBtn( int id ) const
{
	return buttons[ 0 ][ id ];
}