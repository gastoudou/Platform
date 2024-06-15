#include "Core/stdafx.h"
#include "Entity.h"

/// Entity - implementation
GS_Entity::GS_Entity( size_t _id )
	: m_id( _id )
{
}

GS_Entity::~GS_Entity()
{
	m_id = std::numeric_limits< size_t >::max();
}

size_t GS_Entity::getId() const
{
	return m_id;
}