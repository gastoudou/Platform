#ifndef __DEBUG_DRAW_SYSTEM_H__
#define __DEBUG_DRAW_SYSTEM_H__

#pragma once

#ifdef _DEBUG

/// includes
#include "Singleton.h"
#include "System.h"

/// forward declaration
class DebugDrawComponent;
struct SDL_Renderer;

/// GS_RenderSystem
/// This class manages rendering part
class DebugDrawSystem : public GS_Singleton< DebugDrawSystem >, public GS_System
{
public:
	DebugDrawSystem();
	virtual ~DebugDrawSystem();

	void init( SDL_Renderer* _renderer );

	void addComponent( size_t _id );

private:
	DebugDrawSystem( const DebugDrawSystem& ) = delete;
	DebugDrawSystem& operator=( const DebugDrawSystem& ) = delete;

	SDL_Renderer* m_renderer = nullptr;
};

#endif // _DEBUG

#endif // __DEBUG_DRAW_SYSTEM_H__