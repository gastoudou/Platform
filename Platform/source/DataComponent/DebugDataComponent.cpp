#include "Core/stdafx.h"
#include "DebugDataComponent.h"

#ifdef _DEBUG

DebugDataComponent::DebugDataComponent( size_t _parentId )
	: GS_DataComponent( _parentId )
{
	m_list_of_colliders.reserve( 8u );
}

DebugDataComponent::~DebugDataComponent() = default;

void DebugDataComponent::Clear()
{
	m_list_of_colliders.clear();
}

void DebugDataComponent::AddCollider( size_t i )
{
	lock.lock();
	auto itSearch = std::find( m_list_of_colliders.cbegin(), m_list_of_colliders.cend(), i );
	if ( itSearch == m_list_of_colliders.cend() )
	{
		m_list_of_colliders.push_back( i );
	}
	lock.unlock();
}

void DebugDataComponent::ClearText()
{
	lock.lock();
	m_debug_text.clear();
	lock.unlock();
}

void DebugDataComponent::AddText( const char* new_text )
{
	lock.lock();
	m_debug_text = new_text;
	lock.unlock();
}

const std::vector< size_t >& DebugDataComponent::get_colliders() const
{
	return m_list_of_colliders;
}

const char* DebugDataComponent::get_text() const
{
	return m_debug_text.c_str();
}

#endif // _DEBUG