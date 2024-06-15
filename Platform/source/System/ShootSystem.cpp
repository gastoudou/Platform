#include "Core/stdafx.h"
#include "ShootSystem.h"

#include "ShootComponent.h"

/// ShootSystem - implementation
GS_ShootSystem::GS_ShootSystem()
{
}

GS_ShootSystem::~GS_ShootSystem()
{
	shutDown();
}

void GS_ShootSystem::addComponent( size_t _id )
{
	GS_ShootComponent* compo = new GS_ShootComponent( _id );
	compo->init();
	m_components.push_back( compo );
}