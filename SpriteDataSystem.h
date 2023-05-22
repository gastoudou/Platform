#ifndef __SPRITE_DATA_MANAGER_H__
#define __SPRITE_DATA_MANAGER_H__

/// includes
#include "Singleton.h"

/// GS_SpriteDataSystem
/// This class manages the sprite interface for the game
class GS_SpriteDataSystem final : public GS_Singleton< GS_SpriteDataSystem >
{
public:
	GS_SpriteDataSystem();
	~GS_SpriteDataSystem();

	void loadSprite( const char* );
	bool getSpriteById( size_t, size_t& ) const;

private:
	GS_SpriteDataSystem( const GS_SpriteDataSystem& );
	GS_SpriteDataSystem& operator=( const GS_SpriteDataSystem& ) = delete;

	std::vector< size_t > m_ids;
};

#endif