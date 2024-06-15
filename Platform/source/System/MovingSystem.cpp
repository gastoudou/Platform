#include "Core/stdafx.h"
#include "MovingSystem.h"

#include "MoveComponent.h"
#include "MoveDataComponent.h"

/// MovingSystem - implementation
GS_MovingSystem::GS_MovingSystem() = default;

void GS_MovingSystem::addComponent( size_t _id, MvtType _mvtType )
{
	GS_MoveComponent* compo = new GS_MoveComponent( _id, _mvtType );
	compo->init();
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
}

void GS_MovingSystem::setMove( size_t _id, Direction _direction )
{
	lock.lock();
	auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.end() )
	{
		static_cast< GS_MoveComponent* >( m_components[ (*itSearch).second ] )->move( _direction );
	}
	lock.unlock();
}

void GS_MovingSystem::setJump( size_t _id )
{
	lock.lock();
	auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.end() )
	{
		static_cast< GS_MoveComponent* >( m_components[ (*itSearch).second ] )->jump();
	}
	lock.unlock();
}