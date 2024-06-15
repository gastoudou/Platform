#include "Core/stdafx.h"
#include "JumpDataSystem.h"

#include "JumpDataComponent.h"

/// JumpDataSystem - implementation
GS_JumpDataSystem::GS_JumpDataSystem() = default;
GS_JumpDataSystem::~GS_JumpDataSystem() = default;

void GS_JumpDataSystem::addComponent( size_t _id )
{
	GS_JumpDataComponent* compo = new GS_JumpDataComponent( _id );
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
}

GS_JumpDataComponent* GS_JumpDataSystem::getComponent( size_t _id ) const
{
	auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.cend() )
	{
		return static_cast< GS_JumpDataComponent* >( m_components[ (*itSearch).second ] );
	}
	return nullptr;
}