#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

/// includes
#include "Singleton.h"

/// forward declaration
class GS_Sprite;

/// GS_ResourceManager
/// This class manages all resources for the game (graphics, etc.)
class GS_ResourceManager final : public GS_Singleton< GS_ResourceManager >
{
public:
	GS_ResourceManager();
	virtual ~GS_ResourceManager();

	size_t loadSpriteFromFile( const char* _path );
	GS_Sprite* getSpriteById( size_t _id ) const;

private:
	GS_ResourceManager( const GS_ResourceManager& ) = delete;
	GS_ResourceManager& operator=( const GS_ResourceManager& ) = delete;

	std::vector< GS_Sprite* > m_sprites;
	size_t m_id = 0u; // current sprite id
};

#endif