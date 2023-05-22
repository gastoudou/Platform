#include "stdafx.h"
#include "EntitySystem.h"

#include "Entity.h"
#include "InputSystem.h"
#include "ShootSystem.h"
#include "MovingSystem.h"
#include "RenderSystem.h"
#include "JumpDataSystem.h"
#include "PositionDataSystem.h"

/// EntitySystem - implementation
GS_EntitySystem::GS_EntitySystem()
	: m_entities()
	, m_nextId( std::numeric_limits< size_t >::max() )
{
}

GS_EntitySystem::~GS_EntitySystem()
{
	if ( !m_entities.empty() )
	{
		std::vector< GS_Entity* >::iterator it = m_entities.begin();
		const std::vector< GS_Entity* >::const_iterator itEnd = it + m_entities.size();
		for ( ; it != itEnd; ++it )
		{
			delete* it;
		}
	}
}

void GS_EntitySystem::process( const float _dt )
{
	std::vector< GS_Entity* >::const_iterator it = m_toRemove.begin();
	const std::vector< GS_Entity* >::const_iterator itEnd = m_toRemove.end();
	for ( ; it != itEnd; ++it )
	{
		std::vector< GS_Entity* >::iterator itSearch = m_entities.begin() + (*it)->m_id;
		if ( itSearch != m_entities.end() )
		{
			delete* itSearch;
			m_entities.erase( itSearch );
		}
	}
	m_toRemove.clear();
	// update sub-systems
	GS_InputSystem::getInstance()->process( _dt );
	GS_ShootSystem::getInstance()->process( _dt );
	GS_MovingSystem::getInstance()->process( _dt );
	GS_RenderSystem::getInstance()->process( _dt );
}

void GS_EntitySystem::shutDown()
{
	std::vector< GS_Entity* >::iterator it = m_entities.begin();
	const std::vector< GS_Entity* >::const_iterator itEnd = m_entities.end();
	for ( ; it != itEnd; ++it )
	{
		delete* it;
	}
	m_entities.clear();

	GS_JumpDataSystem::getInstance()->shutDown();
	GS_PositionDataSystem::getInstance()->shutDown();
	GS_InputSystem::getInstance()->shutDown();
	GS_ShootSystem::getInstance()->shutDown();
	GS_MovingSystem::getInstance()->shutDown();
	GS_RenderSystem::getInstance()->shutDown();
}

size_t GS_EntitySystem::registerEntity()
{
	GS_Entity* newEntity = new GS_Entity( ++m_nextId );
	m_entities.push_back( newEntity );
	return m_nextId;
}

GS_Entity* GS_EntitySystem::getEntityById( size_t _id ) const
{
	if ( !m_entities.empty() && _id < m_entities.size() )
	{
		return m_entities[ _id ];
	}
	return nullptr;
}

void GS_EntitySystem::killEntityById( size_t _id )
{
	if ( m_entities.empty() && _id < m_entities.size() )
	{
		m_toRemove.push_back( m_entities[ _id ] );
	}
}

const std::vector< GS_Entity* >& GS_EntitySystem::getAllEntities() const
{
	return m_entities;
}