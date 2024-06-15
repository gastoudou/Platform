#ifndef __MOVE_COMPONENT_H__
#define __MOVE_COMPONENT_H__

/// includes
#include "Component.h"

/// forward declaration
class GS_Entity;

/// GS_MoveComponent

// type of movement for the entity
enum MvtType : size_t
{
	KEYBOARD,	// player
	PROJECTILE,	// go straight forward
	SLIDER,	// go from A to B
	NONE
};

/// This class is used to manage inputs info got from keyState function from NERDGame
class GS_MoveComponent : public GS_LogicalComponent
{
public:

	explicit GS_MoveComponent( size_t, MvtType );
	virtual ~GS_MoveComponent();
	void init() override;
	void update( const float ) override;
	void shutDown() override;

	void move( Direction );
	void jump();

private:
	GS_MoveComponent();
	GS_MoveComponent( const GS_MoveComponent& );
	GS_MoveComponent& operator=( const GS_MoveComponent& ) = delete;

	void updateKeyboard( const float );
	void updateProjectile( const float );
	void updateNone( const float );
	void updateSlider( const float );

	MvtType m_type;
};

#endif