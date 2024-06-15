#include "Core/stdafx.h"
#include "ScrollDataComponent.h"

/// ScrollDataComponent - implementation
GS_ScrollDataComponent::GS_ScrollDataComponent( size_t _parentId )
	: GS_DataComponent( _parentId )
{
}

GS_ScrollDataComponent::~GS_ScrollDataComponent() = default;

void GS_ScrollDataComponent::update_scroll( const GS_Vector2& new_scroll )
{
	lock.lock();
	m_lastScrollOnX = new_scroll;
	lock.unlock();
}

const GS_Vector2& GS_ScrollDataComponent::get_scroll() const
{
	return m_lastScrollOnX;
}