#include "Core/stdafx.h"
#include "NERDSprite.h"

GS_Sprite::GS_Sprite( SDL_Renderer* _renderer )
	: renderer( _renderer )
{
}

GS_Sprite::~GS_Sprite() = default;

void GS_Sprite::destroy()
{
	SDL_DestroyTexture( texture );
	texture = nullptr;
	SDL_DestroySurface( surface );
	surface = nullptr;
}

void GS_Sprite::draw( int _x, int _y, int direction )
{
	SDL_FRect position;
	position.x = float( _x );
	position.y = float( _y );
	position.w = float( width );
	position.h = float( height );
	SDL_RenderTextureRotated( renderer, texture,
							  nullptr, &position,
							  0.0, nullptr,
							  direction > 0 ? SDL_FlipMode::SDL_FLIP_NONE : SDL_FlipMode::SDL_FLIP_HORIZONTAL );
}

void GS_Sprite::draw_debug( int _x, int _y )
{
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_FRect position;
	position.x = float( _x );
	position.y = float( _y );
	position.w = float( width );
	position.h = float( height );
	SDL_RenderRect( renderer, &position );
}

void GS_Sprite::loadBMP( const char* _path )
{
	GS_RenderSystem::getInstance()->lock.lock();

	surface = SDL_LoadBMP( _path );
	assert( surface );
	if ( surface != nullptr )
	{
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		if ( texture )
		{
			SDL_GetTextureSize( texture, &width, &height );
		}
		else
		{
			SDL_Log( "Failed to create texture from surface: %s", SDL_GetError() );
		}
	}

// 	texture = IMG_LoadTexture( renderer, _path );
// 	if ( texture )
// 	{
// 		SDL_GetTextureSize( texture, &width, &height );
// 	}
// 	else
// 	{
// 		SDL_Log( "Failed to create texture from surface: %s", SDL_GetError() );
// 	}

	GS_RenderSystem::getInstance()->lock.unlock();

	assert( width > 0 );
	assert( height > 0 );
}