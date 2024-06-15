#ifndef __SHOOT_SYSTEM_H__
#define __SHOOT_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "System.h"

/// forward declaration
class GS_ShootComponent;

/// GS_ShootSystem
/// This class manages shooting part
class GS_ShootSystem : public GS_Singleton< GS_ShootSystem >, public GS_System
{
public:
	GS_ShootSystem();
	~GS_ShootSystem();

	void addComponent( size_t );

private:
	GS_ShootSystem( const GS_ShootSystem& ) = delete;
	GS_ShootSystem& operator=( const GS_ShootSystem& ) = delete;
};

#endif