#include "Core/stdafx.h"
#include "SpriteDataSystem.h"

#include "ResourceManager.h"

/// SpriteDataSystem - implementation
GS_SpriteDataSystem::GS_SpriteDataSystem()
{
}

GS_SpriteDataSystem::~GS_SpriteDataSystem()
{
}

void GS_SpriteDataSystem::loadSprite( const char* _path, size_t id )
{
	m_ids[id] = GS_ResourceManager::getInstance()->loadSpriteFromFile( _path );
}

bool GS_SpriteDataSystem::getSpriteById( size_t _id, size_t& _spriteId ) const
{
	if ( m_ids.contains( _id ) )
	{
		_spriteId = m_ids.at( _id );
		return true;
	}
	return false;
}