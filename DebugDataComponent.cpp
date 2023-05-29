#include "stdafx.h"
#include "DebugDataComponent.h"

#ifdef _DEBUG

DebugDataComponent::DebugDataComponent( size_t _parentId )
	: GS_DataComponent( _parentId )
{
}

DebugDataComponent::~DebugDataComponent() = default;

#endif // _DEBUG