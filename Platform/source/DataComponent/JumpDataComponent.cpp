#include "Core/stdafx.h"
#include "JumpDataComponent.h"

/// JumpDataComponent - implementation
GS_JumpDataComponent::GS_JumpDataComponent( size_t _parentId )
	: GS_DataComponent( _parentId )
{
	/*char buffer[ 256 ];
	GetPrivateProfileString( "Jump", "JumpForceInit", "55", buffer, 256, ".\\data\\config.ini");
	m_JUMP_FORCE_INIT = static_cast< float >( atof( buffer ) );
	GetPrivateProfileString( "Jump", "Gravity", "-0.055", buffer, 256, ".\\data\\config.ini");
	m_GRAVITY = static_cast< float >( atof( buffer ) );*/
}

GS_JumpDataComponent::~GS_JumpDataComponent()
{
}

void GS_JumpDataComponent::Jump()
{
	lock.lock();

	if ( !m_isJumping && m_isTouchingGround )
	{
		m_isJumping = true;
		m_isFalling = false;
		m_jumpForce = m_JUMP_FORCE_INIT;
		if ( auto moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
		{
			moveCompo->StopFalling();
		}
	}
	lock.unlock();
}

void GS_JumpDataComponent::StopJump( float vel_y )
{
	lock.lock();

	m_isJumping = false;
	if ( vel_y > 0.0f )
	{
		m_isFalling = false;
		m_isTouchingGround = true;
	}
	else
	{
		m_isFalling = true;
		m_isTouchingGround = false;
	}
	lock.unlock();
}

void GS_JumpDataComponent::Update()
{
	lock.lock();

	if ( m_isJumping )
	{
		m_jumpForce += m_GRAVITY;
		if ( GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
		{
			moveCompo->update_velocity_y( -m_jumpForce );
		}

		if ( m_jumpForce < 0.0f )
		{
			m_isJumping = false;
			m_isFalling = true;
			m_isTouchingGround = false;
		}
	}
	else if ( m_isFalling )
	{
		m_jumpForce += m_GRAVITY;
		if ( GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
		{
			moveCompo->update_velocity_y( -m_jumpForce );
		}
	}
	else // if ( !m_isFalling && !m_isJumping && !m_isTouchingGround )
	{
		m_isFalling = true;
	}

	lock.unlock();
}