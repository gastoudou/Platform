#include "Core/stdafx.h"
#include "InputSystem.h"

#include "InputComponent.h"

/// InputSystem - implementation
GS_InputSystem::GS_InputSystem() = default;

GS_InputSystem::~GS_InputSystem() = default;

void GS_InputSystem::addComponent( size_t _id )
{
	GS_InputComponent* compo = new GS_InputComponent( _id );
	compo->init();
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
}

GS_InputComponent* GS_InputSystem::getComponent( size_t _id ) const
{
	auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.cend() )
	{
		return static_cast< GS_InputComponent* >( m_components[ (*itSearch).second ] );
	}
	return nullptr;
}