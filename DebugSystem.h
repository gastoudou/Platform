#ifndef __DEBUG_SYSTEM_H__
#define __DEBUG_SYSTEM_H__

#pragma once

#ifdef _DEBUG

/// includes
#include "Singleton.h"
#include "Store.h"

/// forward declaration
class DebugDataComponent;

/// This class stores debug components
class DebugSystem : public GS_Singleton< DebugSystem >, public GS_Store
{
public:
	DebugSystem();
	~DebugSystem();

	void addComponent( size_t );
	DebugDataComponent* getComponent( size_t ) const;
};

#endif // _DEBUG

#endif // __DEBUG_SYSTEM_H__