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
			SDL_FRect position;
			position.x = float( int( tile_id % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH - int( scroll.x ) );
			position.y = float( int( tile_id / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT - int( scroll.y ) );
			position.w = float( k_SPRITE_WIDTH );
			position.h = float( k_SPRITE_HEIGHT );
			// std::cout << __FUNCTION__ << std::endl;
			SDL_RenderFillRect( m_renderer, &position );
		}

		SDL_Color color = { 255, 255, 255 };
		SDL_Surface* surface = TTF_RenderText_Solid( font, debugCompo->get_text(), debugCompo->get_text_size(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface( m_renderer, surface );

		float texW = 0;
		float texH = 0;
		SDL_GetTextureSize( texture, &texW, &texH );
		SDL_FRect dstrect = { 0.f, 0.f, texW, texH };

		SDL_RenderTexture( m_renderer, texture, NULL, &dstrect );

		SDL_DestroyTexture( texture );
		SDL_DestroySurface( surface );
	}

	GS_RenderSystem::getInstance()->lock.unlock();
}

void DebugDrawComponent::shutDown()
{
	TTF_CloseFont( font );
	font = nullptr;
}

#endif // _DEBUG