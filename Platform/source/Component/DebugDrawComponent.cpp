#include "Core/stdafx.h"
#include "Component/DebugDrawComponent.h"

#ifdef _DEBUG

#include "System/DebugSystem.h"
#include "DataComponent/DebugDataComponent.h"
#include "Core/Game.h"

DebugDrawComponent::DebugDrawComponent( size_t _parent, SDL_Renderer* _renderer )
	: GS_LogicalComponent( _parent )
	, m_renderer( _renderer )
{

}

DebugDrawComponent::~DebugDrawComponent() = default;

void DebugDrawComponent::init()
{
	font = TTF_OpenFont( "data//arial.ttf", 15 );
}

void DebugDrawComponent::update( const float )
{
	if ( m_renderer == nullptr )
	{
		return;
	}

	GS_RenderSystem::getInstance()->lock.lock();

	if ( auto debugCompo = DebugSystem::getInstance()->getComponent( m_id ) )
	{
		GS_Vector2 scroll = GS_Game::getInstance()->getScroll();

		for ( auto tile_id : debugCompo->get_colliders() )
		{
			SDL_SetRenderDrawColor( m_renderer, 255, 0, 255, 255 );
			SDL_Rect position;
			position.x = int( tile_id % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH - int( scroll.x );
			position.y = int( tile_id / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT - int( scroll.y );
			position.w = k_SPRITE_WIDTH;
			position.h = k_SPRITE_HEIGHT;
			// std::cout << __FUNCTION__ << std::endl;
			SDL_RenderFillRect( m_renderer, &position );
		}

		SDL_Color color = { 255, 255, 255 };
		SDL_Surface* surface = TTF_RenderText_Solid( font, debugCompo->get_text(), color );
		SDL_Texture* texture = SDL_CreateTextureFromSurface( m_renderer, surface );

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
		SDL_Rect dstrect = { 0, 0, texW, texH };

		SDL_RenderCopy( m_renderer, texture, NULL, &dstrect );

		SDL_DestroyTexture( texture );
		SDL_FreeSurface( surface );
	}

	GS_RenderSystem::getInstance()->lock.unlock();
}

void DebugDrawComponent::shutDown()
{
	TTF_CloseFont( font );
}

#endif // _DEBUG