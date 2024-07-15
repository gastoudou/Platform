#ifndef NERD_GAME_H
#define NERD_GAME_H

class GS_Sprite;
struct SDL_Window;
struct SDL_Renderer;

class NERDGame
{
	friend class GS_Game;

public:
	enum KeyNames
	{
		NERD_KEY_UP = 1 << 0,
		NERD_KEY_DOWN = 1 << 1,
		NERD_KEY_LEFT = 1 << 2,
		NERD_KEY_RIGHT = 1 << 3,
		NERD_KEY_SPACE = 1 << 4
	};

	NERDGame();
	~NERDGame();

	bool initialize( int _w, int _h );
	void shutdown();
	bool update();
	void postUpdate() const;
	GS_Sprite* createSpriteFromBMP( const char* _path );
	float getElapsedTime();
	int getKeyState() const;

	int getJoypadValueX( int id ) const;
	int getJoypadValueY( int id ) const;

	int getJoypadBtn( int id ) const;

private:
	NERDGame( const NERDGame& );
	NERDGame& operator=( const NERDGame& ) = delete;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Joystick* gameController = nullptr;

	int joypads[ 1 ][ 2 ] = { 0 };
	int buttons[ 1 ][ 8 ] = { 0 };
	int keyState = 0;
	int lastTick = 0;
};

#endif // NERD_GAME_H

