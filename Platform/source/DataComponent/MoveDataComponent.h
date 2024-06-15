#ifndef __MOVE_DATA_COMPONENT_H__
#define __MOVE_DATA_COMPONENT_H__

enum Direction : int;

/// includes
#include "Component.h"

/// GS_MoveDataComponent
/// This class represents the moving part of an entity
class GS_MoveDataComponent final : public GS_DataComponent
{
public:
	GS_MoveDataComponent( size_t id, const GS_Vector2& init_position, const GS_Vector2& position, float speed );
	virtual ~GS_MoveDataComponent();

	void Update( Direction _direction );
	void StopFalling();
	void SomethingOnX();

	const GS_Vector2& get_position() const;
	void set_position( const GS_Vector2& );

	void update_velocity( float _dt );
	void update_scrolling();

	void update_velocity_y( float vel_y );
	const Direction& get_current_direction() const;

	void set_direction( const GS_Vector2& );
	const GS_Vector2& get_direction() const;
	void update_direction( float );

	const float& get_speed() const;

private:
	GS_MoveDataComponent();
	GS_MoveDataComponent( const GS_MoveDataComponent& );
	GS_MoveDataComponent& operator=( const GS_MoveDataComponent& ) = delete;

	bool checkCollisionsWith( const GS_AABB&, const GS_Vector2& scroll = GS_Vector2() ) const;

	GS_Vector2 m_position;
	GS_Vector2 m_initPosition;
	GS_Vector2 m_direction;
	GS_Vector2 m_velocity;
	float m_speed = 0.0f;
	Direction m_current_direction = static_cast< Direction >( 1 );

	std::mutex lock;
};

#endif