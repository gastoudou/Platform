#include "Core/stdafx.h"
#include "Store.h"

#include "Component.h"

GS_Store::GS_Store() = default;

GS_Store::~GS_Store()
{
	shutDown();
}

void GS_Store::shutDown()
{
	if ( !m_components.empty() )
	{
		auto it = m_components.begin();
		const auto itEnd = it + m_components.size();
		for ( ; it != itEnd; ++it )
		{
			delete* it;
		}
		m_components.clear();
	}
}