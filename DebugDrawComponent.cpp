#include "stdafx.h"
#include "DebugDrawComponent.h"

#ifdef _DEBUG

#include "DebugSystem.h"
#include "DebugDataComponent.h"
#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

DebugDrawComponent::DebugDrawComponent( size_t _parent, SDL_Renderer* _renderer )
	: GS_LogicalComponent( _parent )
	, m_renderer( _renderer )
{

}

DebugDrawComponent::~DebugDrawComponent() = default;

void DebugDrawComponent::init()
{
}

void DebugDrawComponent::update( const float )
{
	if ( m_renderer == nullptr )
	{
		return;
	}

	if ( auto debugCompo = DebugSystem::getInstance()->getComponent( m_id ) )
	{
		GS_Vector2 scroll = GS_Game::getInstance()->getScroll();

		for ( auto tile_id : debugCompo->m_list_of_colliders )
		{
			SDL_SetRenderDrawColor( m_renderer, 0, 255, 0, 255 );
			SDL_Rect position;
			position.x = int( tile_id % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH - int( scroll.x );
			position.y = int( tile_id / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT - int( scroll.y );
			position.w = k_SPRITE_WIDTH;
			position.h = k_SPRITE_HEIGHT;
			SDL_RenderFillRect( m_renderer, &position );
		}
	}
}

void DebugDrawComponent::shutDown()
{
}

#endif // _DEBUG