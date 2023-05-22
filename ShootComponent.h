#ifndef __SHOOT_COMPONENT_H__
#define __SHOOT_COMPONENT_H__

/// includes
#include "Component.h"

/// GS_ShootComponent
/// This class provides a way to shoot a target
class GS_ShootComponent : public GS_LogicalComponent
{
public:
	explicit GS_ShootComponent( size_t );
	virtual ~GS_ShootComponent();

	void init() override;
	void update( const float ) override;
	void shutDown() override;

private:
	GS_ShootComponent();
	GS_ShootComponent( const GS_ShootComponent& );
	GS_ShootComponent& operator=( const GS_ShootComponent& ) = delete;

	void initTimers();
	void createNewRocket();

	float m_timer = 0.0f;
	float m_timerLimit = 0.0f;
};

#endif