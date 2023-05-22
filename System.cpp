#include "stdafx.h"
#include "System.h"

#include "Component.h"

void GS_System::process( const float _dt )
{
	auto it = m_components.begin();
	const auto itEnd = m_components.end();
	for ( ; it != itEnd; ++it )
	{
		if ( *it )
		{
			(*it)->update( _dt );
		}
	}
}

void GS_System::shutDown()
{
	if ( !m_components.empty() )
	{
		auto it = m_components.begin();
		const auto itEnd = it + m_components.size();
		for ( ; it != itEnd; ++it )
		{
			(*it)->shutDown();
			delete* it;
		}
		m_components.clear();
	}
}