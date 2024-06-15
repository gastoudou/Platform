#include "Core/stdafx.h"
#include "MoveComponent.h"

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
	lock.lock();

#ifdef _DEBUG
	if ( auto debugCompo = DebugSystem::getInstance()->getComponent( m_id ) )
	{
		debugCompo->Clear();
	}
#endif // _DEBUG

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
	lock.unlock();
}

void GS_MoveComponent::shutDown()
{
}

void GS_MoveComponent::move( Direction _direction )
{
	lock.lock();

	if ( GS_MoveDataComponent* data_move_compo = GS_PositionDataSystem::getInstance()->getComponent( m_id ) )
	{
		data_move_compo->Update( _direction );
	}
	lock.unlock();
}

void GS_MoveComponent::jump()
{
	lock.lock();
	if ( GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent( m_id ) )
	{
		jumpCompo->Jump();
	}
	lock.unlock();
}

void GS_MoveComponent::updateNone( const float )
{
	auto moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	auto scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id );

	if ( moveCompo && scrollCompo )
	{
		moveCompo->SomethingOnX();
	}
}

void GS_MoveComponent::updateProjectile( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == nullptr )
	{
		return;
	}
	GS_Vector2 newPosition = moveCompo->get_position() + moveCompo->get_direction() * moveCompo->get_speed() * _dt;
	
	if ( GS_ScrollDataComponent* scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id ) )
	{
		newPosition.x -= GS_Game::getInstance()->getScroll().x - scrollCompo->get_scroll().x;
		scrollCompo->update_scroll( GS_Game::getInstance()->getScroll() );
	}
	moveCompo->set_position( newPosition );
	if ( moveCompo->get_position().x < 0.0f || moveCompo->get_position().x > k_LEVEL_WIDTH * k_SPRITE_WIDTH )
	{
		GS_EntitySystem::getInstance()->killEntityById( m_id );
	}
}

void GS_MoveComponent::updateSlider( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == nullptr )
	{
		return;
	}
	if ( moveCompo->get_direction().lengthSq() < 0.001f )
	{
		moveCompo->set_direction( GS_Vector2( 1.0f, 0.0f ) );
	}

	GS_ScrollDataComponent* scrollCompo = GS_ScrollSystem::getInstance()->getComponent( m_id );
	if ( scrollCompo != nullptr )
	{
		GS_Vector2 nextPosition = moveCompo->get_position() + moveCompo->get_direction() * moveCompo->get_speed() * _dt;
		nextPosition.x += scrollCompo->get_scroll().x;

		// get cells around the entity
		int idCellLeft = ( static_cast< int >( nextPosition.x ) / k_SPRITE_WIDTH ) + ( static_cast< int >( nextPosition.y ) / k_SPRITE_HEIGHT ) * k_LEVEL_WIDTH + 1;
		int idCellRight = ( static_cast< int >( moveCompo->get_position().x ) / k_SPRITE_WIDTH ) + ( static_cast< int >( moveCompo->get_position().y ) / k_SPRITE_HEIGHT ) * k_LEVEL_WIDTH - 1;
		int idCellUnder = ( static_cast< int >( nextPosition.x ) / k_SPRITE_WIDTH ) + ( static_cast< int >( nextPosition.y ) / k_SPRITE_HEIGHT ) * k_LEVEL_WIDTH;

		// check collisions
		size_t typeCellLeft = GS_Game::getInstance()->getTile( idCellLeft );
		size_t typeCellRight = GS_Game::getInstance()->getTile( idCellRight );
		size_t typeCellUnder = moveCompo->get_direction().x < 0.0f ?
			GS_Game::getInstance()->getTile( idCellUnder + k_LEVEL_WIDTH ) :
			GS_Game::getInstance()->getTile( idCellUnder + k_LEVEL_WIDTH + static_cast< int >( moveCompo->get_direction().x ) );

		// if there's collision, change direction
		if ( typeCellLeft != 0 || typeCellRight != 0 || typeCellUnder == 0 )
		{
			moveCompo->update_direction( -1.0f );
		}
		else
		{
			GS_Vector2 newPosition = moveCompo->get_position() + moveCompo->get_direction() * moveCompo->get_speed() * _dt;
			newPosition.x -= GS_Game::getInstance()->getScroll().x - scrollCompo->get_scroll().x;
			moveCompo->set_position( newPosition );
		}
		scrollCompo->update_scroll( /*GS_Game::getInstance()->getScroll().x*/ moveCompo->get_direction() * moveCompo->get_speed() * _dt );
	}
}

void GS_MoveComponent::updateKeyboard( const float _dt )
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == nullptr )
	{
		return;
	}

	// check y position of the main entity
	if ( GS_InputSystem::getInstance()->getComponent( m_id ) && moveCompo->get_position().y > k_SCREEN_HEIGHT * k_SPRITE_HEIGHT )
	{
		GS_Game::getInstance()->setPlayerDead();
		return;
	}

	// jump management
	if ( GS_JumpDataComponent* jumpCompo = GS_JumpDataSystem::getInstance()->getComponent( m_id ) )
	{
		jumpCompo->Update();
	}

	moveCompo->update_velocity( _dt );
	moveCompo->update_scrolling();

#ifdef _DEBUG
	if ( auto debugCompo = DebugSystem::getInstance()->getComponent( m_id ) )
	{
		debugCompo->ClearText();

		std::stringstream oss;
		oss.setf( std::ios::fixed );
		oss.precision( 2 );
		oss << moveCompo->get_position().x << " : " << moveCompo->get_position().y;

		debugCompo->AddText( oss.str().c_str() );
	}
#endif // _DEBUG

}