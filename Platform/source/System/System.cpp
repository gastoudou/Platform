#include "Core/stdafx.h"
#include "System.h"

#include "Component.h"
#include "Message.h"

void GS_System::process( const float _dt )
{
#ifdef _DEBUG
	OPTICK_EVENT();
#endif // _DEBUG

	//for ( auto message : m_messages )
	//{
	//	handle_message( message );
	//}

	for ( auto& compo : m_components )
	{
		compo->update( _dt );
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
			( *it )->shutDown();
			delete* it;
		}
		m_components.clear();
	}
}