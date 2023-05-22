#include "stdafx.h"
#include "NERDSprite.h"

#include <SDL.h>
#include <SDL_image.h>

GS_Sprite::GS_Sprite( SDL_Renderer* _renderer )
	: renderer( _renderer )
{
}

GS_Sprite::~GS_Sprite() = default;

void GS_Sprite::destroy()
{
	SDL_DestroyTexture( texture );
	texture = NULL;
	SDL_FreeSurface( surface );
	surface = NULL;
}

void GS_Sprite::draw( int _x, int _y )
{
	SDL_Rect position;
	position.x = _x;
	position.y = _y;
	position.w = width;
	position.h = height;
	SDL_RenderCopy( renderer, texture, NULL, &position );
}

void GS_Sprite::draw_debug( int _x, int _y )
{
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_Rect position;
	position.x = _x;
	position.y = _y;
	position.w = width;
	position.h = height;
	SDL_RenderDrawRect( renderer, &position );
}

void GS_Sprite::loadBMP( const char* _path )
{
	surface = SDL_LoadBMP( _path );
	assert( surface );
	if ( surface != NULL )
	{
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		Uint32 format = 0;
		int access = 0;
		SDL_QueryTexture( texture, &format, &access, &width, &height );
	}
	assert( width > 0 );
	assert( height > 0 );
}