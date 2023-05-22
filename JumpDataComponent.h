#ifndef __JUMP_DATA_COMPONENT_H__
#define __JUMP_DATA_COMPONENT_H__

/// includes
#include "Component.h"

/// JumpDataComponent
/// This class provides data for jump
class GS_JumpDataComponent final : public GS_DataComponent
{
public:
	explicit GS_JumpDataComponent( size_t );
	virtual ~GS_JumpDataComponent();

	// jump data
	float m_JUMP_FORCE_INIT = 750.0f;
#ifdef _DEBUG
	float m_GRAVITY = -0.5f;
#else
	float m_GRAVITY = -0.25f;
#endif // _DEBUG
	float m_jumpForce = 0.0f;
	// flags
	bool m_isJumping = false;
	bool m_isFalling = false;
	bool m_isTouchingGround = false;

private:
	GS_JumpDataComponent();
	GS_JumpDataComponent( const GS_JumpDataComponent& );
	GS_JumpDataComponent& operator=( const GS_JumpDataComponent& ) = delete;
};

#endif