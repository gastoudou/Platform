#include "Core/stdafx.h"
#include "ShootComponent.h"

#include "Entity.h"
#include "EntitySystem.h"
#include "RenderSystem.h"
#include "MovingSystem.h"
#include "InputSystem.h"
#include "PositionDataSystem.h"
#include "Game.h"
#include "MoveDataComponent.h"
#include "MoveComponent.h"
#include "ScrollSystem.h"

/// ShootComponent - implementation
GS_ShootComponent::GS_ShootComponent( size_t _parentId )
	: GS_LogicalComponent( _parentId )
{
}

GS_ShootComponent::~GS_ShootComponent() = default;

void GS_ShootComponent::init()
{
	initTimers();
}

void GS_ShootComponent::update( const float _dt )
{
	lock.lock();

	m_timer += _dt;
	if ( m_timer > m_timerLimit )
	{
		createNewRocket();
		initTimers();
	}

	lock.unlock();
}

void GS_ShootComponent::shutDown()
{
}

void GS_ShootComponent::initTimers()
{
	m_timer = 0.0f;
	m_timerLimit = 2.0f + (rand() % 5000) / 1000.0f;
}

void GS_ShootComponent::createNewRocket()
{
	GS_MoveDataComponent* moveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_id );
	if ( moveCompo == nullptr )
	{
		return;
	}
	/*char buffer[ 256 ];
	GetPrivateProfileString( "Move", "SpeedRocket", "150", buffer, 256, ".\\data\\config.ini");
	const float speed = static_cast< float >( atof( buffer ) );*/
	const float speed = 250.0f;

	size_t newId = GS_EntitySystem::getInstance()->registerEntity();
	GS_Vector2 direction = GS_Vector2( rand() % 10 > 5 ? -1.0f : 1.0f, 0.0f );
	GS_Vector2 position = moveCompo->get_position() + GS_Game::getInstance()->getScroll() + direction * ( k_SPRITE_WIDTH + 1.0f );
	GS_PositionDataSystem::getInstance()->addComponent( newId, position, speed );
	GS_RenderSystem::getInstance()->addComponent( newId, "data//rocket.bmp" );
	GS_MovingSystem::getInstance()->addComponent( newId, PROJECTILE );
	GS_ScrollSystem::getInstance()->addComponent( newId, direction );
}