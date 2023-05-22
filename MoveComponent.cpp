#include "stdafx.h"
#include "MoveComponent.h"

#include "Entity.h"
#include "EntitySystem.h"
#include "Game.h"
#include "PositionDataSystem.h"
#include "MoveDataComponent.h"
#include "JumpDataSystem.h"
#include "JumpDataComponent.h"
#include "InputSystem.h"
#include "InputComponent.h"
#include "ScrollSystem.h"
#include "ScrollDataComponent.h"

/// MoveComponent - implementation
GS_MoveComponent::GS_MoveComponent( size_t _parent, MvtType _type )
	: GS_LogicalComponent( _parent )
	, m_type( _type )
{
}

GS_MoveComponent::~GS_MoveComponent()
{
}

void GS_MoveComponent::init()
{
}

void GS_MoveComponent::update( const float _dt )
{
	switch ( m_type )
	{
		case KEYBOARD:
			updateKeyboard( _dt );
			break;
		case PROJECTILE:
			updateProjectile( _dt );
			break;
		case SLIDER:
			updateSlider( _dt );
			break;
		case NONE:
			updateNone( _dt );
			break;
		default:
			break;
	}
}

void GS_MoveComponent::shutDown()
{
}

void GS_MoveComponent::move( Direction _direction )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo )
	{
		moveCompo->m_velocity.x = static_cast< float >(_direction) * moveCompo->m_speed;
	}
}

void GS_MoveComponent::jump()
{
	GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent( m_id );
	if ( jumpCompo && !jumpCompo->m_isJumping && jumpCompo->m_isTouchingGround )
	{
		jumpCompo->m_isJumping = true;
		jumpCompo->m_isFalling = false;
		jumpCompo->m_jumpForce = jumpCompo->m_JUMP_FORCE_INIT;
		if ( auto moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
		{
			moveCompo->m_velocity.y = 0.0f;
		}
	}
}

void GS_MoveComponent::updateNone( const float )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == NULL )
	{
		return;
	}
	GS_ScrollDataComponent* scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id );
	if ( scrollCompo != NULL )
	{
		moveCompo->m_position.x = moveCompo->m_initPosition.x - GS_Game::getInstance()->getScroll().x;
	}
}

void GS_MoveComponent::updateProjectile( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == NULL )
	{
		return;
	}
	GS_Vector2 newPosition = moveCompo->m_position + moveCompo->m_direction * moveCompo->m_speed * _dt;
	GS_ScrollDataComponent* scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id );
	if ( scrollCompo != NULL )
	{
		newPosition.x -= GS_Game::getInstance()->getScroll().x - scrollCompo->m_lastScrollOnX;
		scrollCompo->m_lastScrollOnX = GS_Game::getInstance()->getScroll().x;
	}
	moveCompo->m_position = newPosition;
	if ( moveCompo->m_position.x < 0.0f || moveCompo->m_position.x > k_LEVEL_WIDTH * k_SPRITE_WIDTH )
	{
		GS_EntitySystem::getInstance()->killEntityById( m_id );
	}
}

void GS_MoveComponent::updateSlider( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == NULL )
	{
		return;
	}
	if ( moveCompo->m_direction.lengthSq() < 0.001f )
	{
		moveCompo->m_direction = GS_Vector2( 1.0f, 0.0f );
	}
	GS_ScrollDataComponent* scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id );
	if ( scrollCompo != NULL )
	{
		GS_Vector2 nextPosition = moveCompo->m_position + moveCompo->m_direction * moveCompo->m_speed * _dt;
		nextPosition.x += scrollCompo->m_lastScrollOnX;

		// get cells around the entity
		int idCellLeft = (static_cast< int >(nextPosition.x) / k_SPRITE_WIDTH) + (static_cast< int >(nextPosition.y) / k_SPRITE_HEIGHT) * k_LEVEL_WIDTH + 1;
		int idCellRight = (static_cast< int >(moveCompo->m_position.x) / k_SPRITE_WIDTH) + (static_cast< int >(moveCompo->m_position.y) / k_SPRITE_HEIGHT) * k_LEVEL_WIDTH - 1;
		int idCellUnder = (static_cast< int >(nextPosition.x) / k_SPRITE_WIDTH) + (static_cast< int >(nextPosition.y) / k_SPRITE_HEIGHT) * k_LEVEL_WIDTH;

		// check collisions
		size_t typeCellLeft = GS_Game::getInstance()->getTile( idCellLeft );
		size_t typeCellRight = GS_Game::getInstance()->getTile( idCellRight );
		size_t typeCellUnder = moveCompo->m_direction.x < 0.0f ?
			GS_Game::getInstance()->getTile( idCellUnder + k_LEVEL_WIDTH ) :
			GS_Game::getInstance()->getTile( idCellUnder + k_LEVEL_WIDTH + static_cast< int >(moveCompo->m_direction.x) );

		// if there's collision, change direction
		if ( typeCellLeft != 0 || typeCellRight != 0 || typeCellUnder == 0 )
		{
			moveCompo->m_direction *= -1.0f;
		}
		else
		{
			GS_Vector2 newPosition = moveCompo->m_position + moveCompo->m_direction * moveCompo->m_speed * _dt;
			newPosition.x -= GS_Game::getInstance()->getScroll().x - scrollCompo->m_lastScrollOnX;
			moveCompo->m_position = newPosition;
		}
		scrollCompo->m_lastScrollOnX = GS_Game::getInstance()->getScroll().x;
	}
}

void GS_MoveComponent::updateKeyboard( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == NULL )
	{
		return;
	}

	// check y position of the main entity
	if ( GS_InputSystem::getInstance()->getComponent( m_id ) && moveCompo->m_position.y > k_SCREEN_HEIGHT * k_SPRITE_HEIGHT )
	{
		GS_Game::getInstance()->setPlayerDead();
		return;
	}

	bool canMoveOnX = true;
	bool canMoveOnY = true;

	// jump management
	GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent(m_id);

	if ( jumpCompo && jumpCompo->m_isJumping )
	{
		jumpCompo->m_jumpForce += jumpCompo->m_GRAVITY;
		moveCompo->m_velocity.y -= jumpCompo->m_jumpForce;
		if ( jumpCompo->m_jumpForce < 0.0f )
		{
			jumpCompo->m_isJumping = false;
			jumpCompo->m_isFalling = true;
			jumpCompo->m_isTouchingGround = false;
		}
	}
	else if ( jumpCompo && jumpCompo->m_isFalling )
	{
		jumpCompo->m_jumpForce += jumpCompo->m_GRAVITY;
		moveCompo->m_velocity.y -= jumpCompo->m_jumpForce;
	}
	else if ( jumpCompo && !jumpCompo->m_isFalling && !jumpCompo->m_isJumping && !jumpCompo->m_isTouchingGround )
	{
		jumpCompo->m_isFalling = true;
	}


	moveCompo->m_velocity *= _dt;

	// manage scrolling
	GS_Vector2 potentialScroll = GS_Game::getInstance()->getScroll();

	if ( moveCompo->m_position.x + moveCompo->m_velocity.x < 0.0f )
	{
		moveCompo->m_velocity.x = 0.0f;
	}
	if ( moveCompo->m_position.x + moveCompo->m_velocity.x + k_SPRITE_WIDTH > k_SCREEN_WIDTH * k_SPRITE_WIDTH )
	{
		moveCompo->m_velocity.x = 0.0f;
	}
	if ( moveCompo->m_velocity.x > 0.0f
		&& moveCompo->m_position.x + moveCompo->m_velocity.x > 250.0f
		&& (GS_Game::getInstance()->getScroll().x + k_SCREEN_WIDTH * k_SPRITE_WIDTH < k_LEVEL_WIDTH * k_SPRITE_WIDTH) )
	{
		potentialScroll.x += moveCompo->m_velocity.x;
		moveCompo->m_velocity.x = 0.0f;
	}
	else if ( moveCompo->m_velocity.x < 0.0f
		&& GS_Game::getInstance()->getScroll().x > 0.0f
		&& (moveCompo->m_position.x + moveCompo->m_velocity.x) < (k_SCREEN_WIDTH * k_SPRITE_WIDTH - 250.0f)
		&& (moveCompo->m_position.x + moveCompo->m_velocity.x + k_SPRITE_WIDTH < k_SCREEN_WIDTH * k_SPRITE_WIDTH) )
	{
		potentialScroll.x += moveCompo->m_velocity.x;
		moveCompo->m_velocity.x = 0.0f;
	}

	// calculate potential position for collisions
	GS_Vector2 potentialPositionOnX = moveCompo->m_position;
	potentialPositionOnX.x += moveCompo->m_velocity.x;
	GS_Vector2 potentialPositionOnY = moveCompo->m_position;
	potentialPositionOnY.y += moveCompo->m_velocity.y;

	// calculate collisions with environment on X axis
	const GS_Vector2 extendSprite( static_cast< float >(k_SPRITE_WIDTH), static_cast< float >(k_SPRITE_HEIGHT) );

	GS_AABB entityOnX( potentialPositionOnX, extendSprite );

	if ( checkCollisionsWith( entityOnX, potentialScroll ) )
	{
		canMoveOnX = false;
	}

	// calculate collisions with environment on Y axis
	GS_AABB entityOnY( potentialPositionOnY, extendSprite );

	if ( checkCollisionsWith( entityOnY, potentialScroll ) )
	{
		canMoveOnY = false;
		if ( jumpCompo )
		{
			jumpCompo->m_isJumping = false;
			if ( moveCompo->m_velocity.y > 0.0f )
			{
				jumpCompo->m_isTouchingGround = true;
			}
			else
			{
				jumpCompo->m_isFalling = true;
			}
		}
	}

	// calculate collisions with enemies/rockets
	const std::vector< GS_Entity* >& enemies = GS_EntitySystem::getInstance()->getAllEntities();
	for ( size_t i = 0; i < enemies.size(); ++i )
	{
		if ( m_id == enemies[ i ]->getId() )
		{
			continue;
		}
		GS_MoveDataComponent* enemyMoveCompo = GS_PositionDataSystem::getInstance()->getComponent( enemies[ i ]->getId() );
		if ( enemyMoveCompo )
		{
			GS_Vector2 topLeft = enemyMoveCompo->m_position - (potentialScroll - GS_Game::getInstance()->getScroll());
			GS_AABB enemyTile( topLeft, extendSprite );

			if ( entityOnX.overlaps( enemyTile ) && entityOnY.overlaps( enemyTile ) )
			{
				GS_Game::getInstance()->setPlayerDead();
				return;
			}
		}
	}

	// set the position regarding result of collisions calculation
	if ( canMoveOnX )
	{
		if ( fabs( moveCompo->m_velocity.x ) > 0.0f )
		{
			moveCompo->m_position.x = potentialPositionOnX.x;
		}
		else
		{
			GS_Game::getInstance()->setScroll( potentialScroll );
		}
	}
	if ( canMoveOnY )
	{
		if ( fabs( moveCompo->m_velocity.y ) > 0.0f )
		{
			moveCompo->m_position.y = potentialPositionOnY.y;
		}
		else
		{
			GS_Game::getInstance()->setScroll( potentialScroll );
		}
	}
	else
	{
		if ( jumpCompo )
		{
			jumpCompo->m_jumpForce = 0.0f;
		}
		moveCompo->m_velocity.y = 0.0f;
	}
}

bool GS_MoveComponent::checkCollisionsWith( const GS_AABB& _entity, const GS_Vector2& _potentialScroll /*= GS_Vector2()*/ ) const
{
	const GS_Vector2 extendSprite( static_cast< float >(k_SPRITE_WIDTH), static_cast< float >(k_SPRITE_HEIGHT) );
	const size_t max_cells = k_SPRITE_WIDTH * k_SPRITE_HEIGHT;

	for ( size_t i = 0u; i < max_cells; ++i )
	{
		GS_Vector2 topLeft = GS_Vector2( (i % k_LEVEL_WIDTH) * k_SPRITE_WIDTH - _potentialScroll.x,
			(i / k_LEVEL_WIDTH) * k_SPRITE_HEIGHT - _potentialScroll.y );

		GS_AABB tile( topLeft, extendSprite );

		if ( _entity.overlaps( tile ) )
		{
			auto id = GS_Game::getInstance()->getTile( i );
			if ( id > 0u )
			{
				if ( id == 4u )
				{
					GS_Game::getInstance()->setLevelClear(); // end of level
				}

				return true;
			}
		}
	}

	return false;
}