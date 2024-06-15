#ifndef __DEBUG_DRAW_COMPONENT_H__
#define __DEBUG_DRAW_COMPONENT_H__

#pragma once

#ifdef _DEBUG

/// includes
#include "Component.h"

struct SDL_Renderer;

/// RenderComponent
/// This class represents the rendering component. Used to display data on screen.
class DebugDrawComponent final : public GS_LogicalComponent
{
public:
	DebugDrawComponent( size_t, SDL_Renderer* );
	virtual ~DebugDrawComponent();

	void init() override;
	void update( const float )  override; // render here
	void shutDown() override;

private:
	DebugDrawComponent() = delete;
	DebugDrawComponent( const DebugDrawComponent& ) = delete;
	DebugDrawComponent( const DebugDrawComponent&& ) = delete;
	DebugDrawComponent& operator=( const DebugDrawComponent& ) = delete;
	DebugDrawComponent& operator=( DebugDrawComponent&& other ) = delete;

	SDL_Renderer* m_renderer = nullptr;
	TTF_Font* font = nullptr;
};

#endif // _DEBUG

#endif // __DEBUG_DRAW_COMPONENT_H__