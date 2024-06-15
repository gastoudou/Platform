#include "Core/stdafx.h"
#include "PositionDataSystem.h"

#include "MoveDataComponent.h"

/// PositionDataSystem - implementation
GS_PositionDataSystem::GS_PositionDataSystem() = default;

GS_PositionDataSystem::~GS_PositionDataSystem()
{
	shutDown();
}

void GS_PositionDataSystem::addComponent( size_t _id, const GS_Vector2& _initPosition /*= GS_Vector2()*/, const float _speed /*= 0.0f*/ )
{
	GS_MoveDataComponent* compo = new GS_MoveDataComponent( _id, _initPosition, _initPosition, _speed );
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
}

GS_MoveDataComponent* GS_PositionDataSystem::getComponent( size_t _id ) const
{
	const auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.end() )
	{
		return static_cast< GS_MoveDataComponent* >(m_components[ (*itSearch).second ]);
	}
	return nullptr;
}