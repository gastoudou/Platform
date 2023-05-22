#include "stdafx.h"
#include "RenderComponent.h"

#include "NERDSprite.h"
#include "EntitySystem.h"
#include "PositionDataSystem.h"
#include "SpriteDataSystem.h"
#include "ResourceManager.h"
#include "MoveComponent.h"
#include "MoveDataComponent.h"

/// RenderComponent - implementation
GS_RenderComponent::GS_RenderComponent( size_t _parentId )
	: GS_LogicalComponent( _parentId )
{
}

GS_RenderComponent::~GS_RenderComponent()
{
}

void GS_RenderComponent::init()
{
}

void GS_RenderComponent::update( const float )
{
	if ( auto moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
	{
		size_t spriteId = std::numeric_limits< size_t >::max();
		if ( GS_SpriteDataSystem::getInstance()->getSpriteById( m_id, spriteId ) )
		{
			if ( auto sprite = GS_ResourceManager::getInstance()->getSpriteById( spriteId ) )
			{
				auto x = static_cast< int >(moveCompo->m_position.x);
				auto y = static_cast< int >(moveCompo->m_position.y);

				sprite->draw( x, y );
#ifdef _DEBUG
				sprite->draw_debug( x, y );
#endif // _DEBUG
			}
		}
	}
}

void GS_RenderComponent::shutDown()
{
}