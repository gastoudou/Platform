#include "stdafx.h"
#include "ResourceManager.h"

#include "Game.h"
#include "NERDSprite.h"

/// GS_ResourceManager - implementation
GS_ResourceManager::GS_ResourceManager()
{
}

GS_ResourceManager::~GS_ResourceManager()
{
	std::vector< GS_Sprite* >::iterator it = m_sprites.begin();
	const std::vector< GS_Sprite* >::const_iterator itEnd = m_sprites.end();
	for ( ; it != itEnd; ++it )
	{
		(*it)->destroy();
	}
}

size_t GS_ResourceManager::loadSpriteFromFile( const char* _path )
{
	m_sprites.push_back( GS_Game::getInstance()->loadSprite( _path ) );
	return m_id++;
}

GS_Sprite* GS_ResourceManager::getSpriteById( size_t _id ) const
{
	if ( !m_sprites.empty() && _id < m_id )
	{
		return m_sprites[ _id ];
	}
	return nullptr;
}