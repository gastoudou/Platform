#include "Core/stdafx.h"
#include "RenderSystem.h"

#include "RenderComponent.h"
#include "SpriteDataSystem.h"

/// RenderSystem - implementation
GS_RenderSystem::GS_RenderSystem() = default;
GS_RenderSystem::~GS_RenderSystem() = default;

void GS_RenderSystem::addComponent( size_t _id, const char* _path )
{
	GS_RenderComponent* compo = new GS_RenderComponent( _id );
	compo->init();
	GS_SpriteDataSystem::getInstance()->loadSprite( _path );
	m_components.push_back( compo );
}