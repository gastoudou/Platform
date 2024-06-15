#ifndef __GAME_H__
#define __GAME_H__

/// includes
#include "Singleton.h"

/// forward declaration
class NERDGame;
class GS_Sprite;
class Entity;

/// GS_Game
/// This class provides a Game instance
class GS_Game final : public GS_Singleton< GS_Game >
{
public:

	GS_Game();
	virtual	~GS_Game();

	void init();
	void reInit();
	bool update();
	void shutDown();
	float getElapsedTime() const;
	GS_Sprite* loadSprite( const std::string& );
	bool isRunning() const;
	bool shouldRestart() const;

	int getKeyState() const;
	int getJoypadValueX( int id ) const;
	int getJoypadValueY( int id ) const;

	int getJoypadBtn( int id ) const;

	void setLevelClear();
	void setPlayerDead();

	const GS_Vector2& getScroll() const;
	void setScroll( const GS_Vector2& new_scroll );

	size_t getTile( size_t ) const;

private:
	GS_Game( const GS_Game& );
	GS_Game& operator=( const GS_Game& ) = delete;

	void loadLevel();
	void reloadLevel();
	void loadNewLevel();
	void renderLevel();
	void createEnemy( const  int, const int ) const;
	void createPlayer( const int ) const;

	std::vector< size_t > m_level;
	std::vector< GS_Sprite* > m_sprites;

	NERDGame* m_game = nullptr;
	size_t m_maxSprites = 0u;
	size_t m_idLevel = 0u;
	size_t m_id = 0u;
	bool m_isLevelClear = false;
	bool m_isPlayerDead = false;
	bool m_isRunning = false;
	bool m_shouldRestart = false;
	bool m_shouldLoadNewLevel = false;
};

#endif