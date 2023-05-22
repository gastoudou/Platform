#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "System.h"

/// forward declaration
class GS_InputComponent;

/// GS_InputSystem
/// This class stores input components
class GS_InputSystem : public GS_Singleton< GS_InputSystem >, public GS_System
{
public:
	GS_InputSystem();
	~GS_InputSystem();

	void addComponent( size_t );
	GS_InputComponent* getComponent( size_t ) const;

};

#endif