#ifndef __DEBUG_DATA_COMPONENT_H__
#define __DEBUG_DATA_COMPONENT_H__

#pragma once

#ifdef _DEBUG

/// includes
#include "Component.h"

class DebugDataComponent : public GS_DataComponent
{
public:
	DebugDataComponent( size_t );
	virtual ~DebugDataComponent();

	std::vector< size_t > m_list_of_colliders;

private:
	DebugDataComponent() = delete;
	DebugDataComponent( const DebugDataComponent& ) = delete;
	DebugDataComponent& operator=( const DebugDataComponent& ) = delete;

};

#endif // _DEBUG

#endif // __DEBUG_DATA_COMPONENT_H__