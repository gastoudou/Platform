#ifndef __SPRITE_H__
#define __SPRITE_H__

#pragma once

struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

class GS_Sprite
{
public:
	explicit GS_Sprite( SDL_Renderer* _renderer );
	~GS_Sprite();

	void destroy();
	void draw( int _x, int _y, int direction );
	void draw_debug( int _x, int _y ); // just shadow draw
	void loadBMP( const char* _path );

private:
	GS_Sprite() = delete;
	GS_Sprite( const GS_Sprite& ) = delete;
	GS_Sprite& operator=( const GS_Sprite& ) = delete;

	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	int width = 0;
	int height = 0;
};

#endif