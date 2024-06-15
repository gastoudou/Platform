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

	void Clear();
	void AddCollider( size_t i );

	void ClearText();
	void AddText( const char* new_text );

	const std::vector< size_t >& get_colliders() const;
	const char* get_text() const;

private:
	DebugDataComponent() = delete;
	DebugDataComponent( const DebugDataComponent& ) = delete;
	DebugDataComponent& operator=( const DebugDataComponent& ) = delete;

	std::vector< size_t > m_list_of_colliders;
	std::string m_debug_text;
};

#endif // _DEBUG

#endif // __DEBUG_DATA_COMPONENT_H__