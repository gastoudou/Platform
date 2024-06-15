#ifndef __PROJECTILE_SYSTEM_H__
#define __PROJECTILE_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "Store.h"

/// forward declaration
class GS_ScrollDataComponent;

/// GS_ScrollSystem
/// This class stores scroll components
class GS_ScrollSystem final : public GS_Singleton< GS_ScrollSystem >, public GS_Store
{
public:
	GS_ScrollSystem();

	void addComponent( size_t, const GS_Vector2& );
	GS_ScrollDataComponent* getComponent( size_t ) const;
};

#endif