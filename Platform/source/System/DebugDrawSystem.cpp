#include "Core/stdafx.h"
#include "DebugDrawSystem.h"

#include "DebugDrawComponent.h"

#ifdef _DEBUG

DebugDrawSystem::DebugDrawSystem() = default;
DebugDrawSystem::~DebugDrawSystem() = default;

void DebugDrawSystem::init( SDL_Renderer* _renderer )
{
	m_renderer = _renderer;
}

void DebugDrawSystem::addComponent( size_t _id )
{
	assert( m_renderer != nullptr );

	DebugDrawComponent* compo = new DebugDrawComponent( _id, m_renderer );
	compo->init();
	m_components.push_back( compo );
}

#endif // _DEBUG