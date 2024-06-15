#include "Core/stdafx.h"
#include "DebugSystem.h"

#include "DebugDataComponent.h"

#ifdef _DEBUG

DebugSystem::DebugSystem() = default;
DebugSystem::~DebugSystem() = default;

void DebugSystem::addComponent( size_t _id )
{
	DebugDataComponent* compo = new DebugDataComponent( _id );
	//compo->m_list_of_colliders.reserve( 8u );
	m_indexTable[ _id ] = m_components.size();
	m_components.push_back( compo );
}

DebugDataComponent* DebugSystem::getComponent( size_t _id ) const
{
	const auto itSearch = m_indexTable.find( _id );
	if ( itSearch != m_indexTable.end() )
	{
		return static_cast< DebugDataComponent* >(m_components[ (*itSearch).second ]);
	}
	return nullptr;
}

#endif // _DEBUG