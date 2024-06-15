#include "Core/stdafx.h"
#include "MoveDataComponent.h"

#include "Game.h"

/// MoveDataComponent - implementation
GS_MoveDataComponent::GS_MoveDataComponent( size_t id, const GS_Vector2& init_position, const GS_Vector2& position, float speed )
	: GS_DataComponent( id )
	, m_initPosition( init_position )
	, m_position( position )
	, m_speed( speed )
{
}

GS_MoveDataComponent::~GS_MoveDataComponent()
{
}

void GS_MoveDataComponent::Update( Direction _direction )
{
	lock.lock();
	m_velocity.x = static_cast< float >( _direction ) * m_speed;
	m_current_direction = _direction;
	lock.unlock();
}

void GS_MoveDataComponent::StopFalling()
{
	lock.lock();
	m_velocity.y = 0.0f;
	lock.unlock();
}

void GS_MoveDataComponent::SomethingOnX()
{
	lock.lock();
	m_position.x = m_initPosition.x - GS_Game::getInstance()->getScroll().x;
	lock.unlock();
}

const GS_Vector2& GS_MoveDataComponent::get_position() const
{
	return m_position;
}

void GS_MoveDataComponent::update_velocity( float _dt )
{
	lock.lock();
	m_velocity *= _dt;
	lock.unlock();
}

void GS_MoveDataComponent::update_scrolling()
{
	lock.lock();

	bool canMoveOnX = true;
	bool canMoveOnY = true;

	// manage scrolling
	GS_Vector2 potentialScroll = GS_Game::getInstance()->getScroll();

	if ( m_position.x + m_velocity.x < 0.0f )
	{
		m_velocity.x = 0.0f;
	}
	if ( m_position.x + m_velocity.x + k_SPRITE_WIDTH > k_SCREEN_WIDTH * k_SPRITE_WIDTH )
	{
		m_velocity.x = 0.0f;
	}

	// calculate potential position for collisions
	GS_Vector2 potentialPositionOnX = m_position;
	potentialPositionOnX.x += m_velocity.x;
	GS_Vector2 potentialPositionOnY = m_position;
	potentialPositionOnY.y += m_velocity.y;

	// calculate collisions with environment on X axis
	const GS_Vector2 extendSprite( static_cast< float >( k_SPRITE_WIDTH ), static_cast< float >( k_SPRITE_HEIGHT ) );

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
		if ( GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent( m_id ) )
		{
			jumpCompo->StopJump( m_velocity.y );
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
			GS_Vector2 topLeft = enemyMoveCompo->m_position - ( potentialScroll - GS_Game::getInstance()->getScroll() );
			GS_AABB enemyTile( topLeft, extendSprite );

			if ( entityOnX.overlaps( enemyTile ) && entityOnY.overlaps( enemyTile ) )
			{
				GS_Game::getInstance()->setPlayerDead();
				break;
			}
		}
	}

	if ( canMoveOnX
		&& m_velocity.x > 0.0f
		&& m_position.x + m_velocity.x > 250.0f
		&& ( GS_Game::getInstance()->getScroll().x + k_SCREEN_WIDTH * k_SPRITE_WIDTH < k_LEVEL_WIDTH * k_SPRITE_WIDTH ) )
	{
		potentialScroll.x += m_velocity.x;
		m_velocity.x = 0.0f;
	}
	else if ( canMoveOnX
		&& m_velocity.x < 0.0f
		&& GS_Game::getInstance()->getScroll().x > 0.0f
		&& ( m_position.x + m_velocity.x ) < ( k_SCREEN_WIDTH * k_SPRITE_WIDTH - 250.0f )
		&& ( m_position.x + m_velocity.x + k_SPRITE_WIDTH < k_SCREEN_WIDTH * k_SPRITE_WIDTH ) )
	{
		potentialScroll.x += m_velocity.x;
		m_velocity.x = 0.0f;
	}


	// set the position regarding result of collisions calculation
	if ( canMoveOnX )
	{
		if ( fabs( m_velocity.x ) > 0.0f )
		{
			m_position.x = potentialPositionOnX.x;
		}
		else
		{
			GS_Game::getInstance()->setScroll( potentialScroll );
		}
	}
	if ( canMoveOnY )
	{
		if ( fabs( m_velocity.y ) > 0.0f )
		{
			m_position.y = potentialPositionOnY.y;
		}
		else
		{
			GS_Game::getInstance()->setScroll( potentialScroll );
		}
	}
	else
	{
		if ( GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent( m_id ) )
		{
			jumpCompo->ClearJumpForce();
		}
		m_velocity.y = 0.0f;
	}

	lock.unlock();
}

bool GS_MoveDataComponent::checkCollisionsWith( const GS_AABB& _entity, const GS_Vector2& scroll /*= GS_Vector2()*/ ) const
{
	const GS_Vector2 extendSprite( static_cast< float >( k_SPRITE_WIDTH ), static_cast< float >( k_SPRITE_HEIGHT ) );
	const size_t max_cells = k_SPRITE_WIDTH * k_SPRITE_HEIGHT;

	bool collision_found = false;

	for ( size_t i = 0u; i < max_cells; ++i )
	{
		GS_Vector2 topLeft = GS_Vector2( static_cast< float >( ( i % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH ) - scroll.x,
			static_cast< float >( ( i / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT ) - scroll.y );

		GS_AABB tile( topLeft, extendSprite );

		if ( _entity.overlaps( tile ) )
		{
			auto id = GS_Game::getInstance()->getTile( i );
			if ( id > 0u && id != std::numeric_limits< size_t >::max() )
			{
				if ( id == 4u )
				{
					GS_Game::getInstance()->setLevelClear(); // end of level
				}

#ifdef _DEBUG
				if ( auto debugCompo = DebugSystem::getInstance()->getComponent( m_id ) )
				{
					debugCompo->AddCollider( i );
				}
#endif // _DEBUG

				collision_found = true;
			}
		}
	}

	return collision_found;
}

void GS_MoveDataComponent::update_velocity_y( float vel_y )
{
	m_velocity.y += vel_y;
}

const Direction& GS_MoveDataComponent::get_current_direction() const
{
	return m_current_direction;
}

void GS_MoveDataComponent::set_direction( const GS_Vector2& new_direction )
{
	m_direction = new_direction;
}

const GS_Vector2& GS_MoveDataComponent::get_direction() const
{
	return m_direction;
}

void GS_MoveDataComponent::update_direction( float value )
{
	m_direction *= value;
}

const float& GS_MoveDataComponent::get_speed() const
{
	return m_speed;
}

void GS_MoveDataComponent::set_position( const GS_Vector2& new_position )
{
	m_position = new_position;
}