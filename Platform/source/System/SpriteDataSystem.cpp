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

void GS_SpriteDataSystem::loadSprite( const char* _path )
{
	m_ids.push_back( GS_ResourceManager::getInstance()->loadSpriteFromFile( _path ) );
}

bool GS_SpriteDataSystem::getSpriteById( size_t _id, size_t& _spriteId ) const
{
	if ( !m_ids.empty() && _id >= 0 && _id < static_cast< int >(m_ids.size()) )
	{
		_spriteId = m_ids[ _id ];
		return true;
	}
	return false;
}