#include "Core/stdafx.h"
#include "NERDGame.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_joystick.h"
#include "NERDSprite.h"
#include "DebugDrawSystem.h"

NERDGame::NERDGame()
{
}

NERDGame::~NERDGame()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool NERDGame::initialize( int _w, int _h )
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
	IMG_Init( IMG_INIT_PNG );
	TTF_Init();
	keyState = 0;
	window = SDL_CreateWindow( "Platform", 150, 150, _w, _h, 0 );
	renderer = SDL_CreateRenderer( window, -1, 0 );
	lastTick = SDL_GetTicks();

	if ( SDL_NumJoysticks() >= 1 )
	{
		gameController = SDL_JoystickOpen( 0 );
		if ( gameController )
		{
			SDL_JoystickEventState( SDL_ENABLE );
		}
	}

#ifdef _DEBUG
	DebugDrawSystem::getInstance()->init( renderer );
#endif // _DEBUG

	return true;
}

void NERDGame::shutdown()
{
	SDL_JoystickClose( gameController );
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
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == SDLK_LEFT )
				{
					keyState |= NERD_KEY_LEFT;
				}
				else if ( event.key.keysym.sym == SDLK_RIGHT )
				{
					keyState |= NERD_KEY_RIGHT;
				}
				else if ( event.key.keysym.sym == SDLK_UP )
				{
					keyState |= NERD_KEY_UP;
				}
				else if ( event.key.keysym.sym == SDLK_DOWN )
				{
					keyState |= NERD_KEY_DOWN;
				}
				break;
			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_LEFT )
				{
					keyState &= ~NERD_KEY_LEFT;
				}
				else if ( event.key.keysym.sym == SDLK_RIGHT )
				{
					keyState &= ~NERD_KEY_RIGHT;
				}
				else if ( event.key.keysym.sym == SDLK_UP )
				{
					keyState &= ~NERD_KEY_UP;
				}
				else if ( event.key.keysym.sym == SDLK_DOWN )
				{
					keyState &= ~NERD_KEY_DOWN;
				}
				break;

			case SDL_JOYAXISMOTION:
				joypads[ event.jaxis.which ][ event.jaxis.axis ] = event.jaxis.value;
				break;

			case SDL_JOYBUTTONDOWN:
				buttons[ event.jbutton.which ][ event.jbutton.button ] = event.jbutton.state;
				break;

			case SDL_JOYBUTTONUP:
				buttons[ event.jbutton.which ][ event.jbutton.button ] = event.jbutton.state;
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
	int diffTick = SDL_GetTicks() - lastTick;
	lastTick = SDL_GetTicks();
	return static_cast< float >(diffTick / 1000.0f);
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

int NERDGame::getJoypadBtn( int id ) const
{
	return buttons[ 0 ][ id ];
}