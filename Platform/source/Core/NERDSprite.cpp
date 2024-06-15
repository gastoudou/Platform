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
	SDL_FreeSurface( surface );
	surface = nullptr;
}

void GS_Sprite::draw( int _x, int _y, int direction )
{
	SDL_Rect position;
	position.x = _x;
	position.y = _y;
	position.w = width;
	position.h = height;
	// std::cout << __FUNCTION__ << std::endl;
	SDL_RenderCopyEx( renderer, texture, nullptr, &position, 0, nullptr, direction > 0 ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
}

void GS_Sprite::draw_debug( int _x, int _y )
{
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
	SDL_Rect position;
	position.x = _x;
	position.y = _y;
	position.w = width;
	position.h = height;
	// std::cout << __FUNCTION__ << std::endl;
	SDL_RenderDrawRect( renderer, &position );
}

void GS_Sprite::loadBMP( const char* _path )
{
	GS_RenderSystem::getInstance()->lock.lock();

	surface = SDL_LoadBMP( _path );
	assert( surface );
	if ( surface != nullptr )
	{
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		Uint32 format = 0;
		int access = 0;
		SDL_QueryTexture( texture, &format, &access, &width, &height );
	}

	GS_RenderSystem::getInstance()->lock.unlock();

	assert( width > 0 );
	assert( height > 0 );
}