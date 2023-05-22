#ifndef __MOVE_DATA_COMPONENT_H__
#define __MOVE_DATA_COMPONENT_H__

/// includes
#include "Component.h"

/// GS_MoveDataComponent
/// This class represents the moving part of an entity
class GS_MoveDataComponent final : public GS_DataComponent
{
public:
	GS_MoveDataComponent( size_t );
	virtual ~GS_MoveDataComponent();

	GS_Vector2 m_position;
	GS_Vector2 m_initPosition;
	GS_Vector2 m_direction;
	GS_Vector2 m_velocity;
	float m_speed = 0.0f;

private:
	GS_MoveDataComponent();
	GS_MoveDataComponent( const GS_MoveDataComponent& );
	GS_MoveDataComponent& operator=( const GS_MoveDataComponent& ) = delete;
};

#endif