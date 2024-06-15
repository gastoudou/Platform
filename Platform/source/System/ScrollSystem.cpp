#include "Core/stdafx.h"
#include "ScrollSystem.h"

#include "ScrollDataComponent.h"
#include "MoveDataComponent.h"
#include "PositionDataSystem.h"

/// ScrollSystem - implementation
GS_ScrollSystem::GS_ScrollSystem() = default;

void GS_ScrollSystem::addComponent( size_t _id, const GS_Vector2& _direction )
{
	GS_ScrollDataComponent* compo = new GS_ScrollDataComponent( _id );
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
	if ( auto* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( _id ) )
	{
		moveCompo->set_direction( _direction );
	}
}

GS_ScrollDataComponent* GS_ScrollSystem::getComponent( size_t _id ) const
{
	std::map< size_t, size_t >::const_iterator itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.cend() )
	{
		return static_cast< GS_ScrollDataComponent* >( m_components[ (*itSearch).second ] );
	}
	return nullptr;
}