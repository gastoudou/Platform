#include "Core/stdafx.h"
#include "InputComponent.h"

#include "NERDGame.h"
#include "Entity.h"
#include "Game.h"
#include "MovingSystem.h"
#include "MoveComponent.h"

#include "SDL_events.h"

const int JOYSTICK_DEAD_ZONE = 8000;

/// InputComponent - implementation
GS_InputComponent::GS_InputComponent( size_t _parentId )
	: GS_LogicalComponent( _parentId )
{
}

GS_InputComponent::~GS_InputComponent()
{
}

void GS_InputComponent::init()
{
	m_UpKeyRelease = true;
}

void GS_InputComponent::update( const float )
{
	lock.lock();

	int keyState = GS_Game::getInstance()->getKeyState();
	// key down
	if ( keyState & NERDGame::NERD_KEY_LEFT )
	{
		GS_MovingSystem::getInstance()->setMove( m_id, LEFT );
	}
	if ( keyState & NERDGame::NERD_KEY_RIGHT )
	{
		GS_MovingSystem::getInstance()->setMove( m_id, RIGHT );
	}
	if ( (keyState & NERDGame::NERD_KEY_UP) && m_UpKeyRelease )
	{
		GS_MovingSystem::getInstance()->setJump( m_id );
		m_UpKeyRelease = false;
	}
	if ( (keyState & NERDGame::NERD_KEY_DOWN) )
	{
		// nothing
	}
	// key up
	if ( (keyState & NERDGame::NERD_KEY_UP) == 0 )
	{
		m_UpKeyRelease = true;
	}

	int joypadOnX = GS_Game::getInstance()->getJoypadValueX( 0 );
	if ( joypadOnX > JOYSTICK_DEAD_ZONE )
	{
		GS_MovingSystem::getInstance()->setMove( m_id, RIGHT );
	}
	else if ( joypadOnX < -JOYSTICK_DEAD_ZONE )
	{
		GS_MovingSystem::getInstance()->setMove( m_id, LEFT );
	}

	int joyPadBtnJmp = GS_Game::getInstance()->getJoypadBtn( 0 );
	if ( joyPadBtnJmp == SDL_PRESSED && m_UpJoyRelease )
	{
		GS_MovingSystem::getInstance()->setJump( m_id );
		m_UpJoyRelease = false;
	}
	if ( joyPadBtnJmp == SDL_RELEASED )
	{
		m_UpJoyRelease = true;
	}

	lock.unlock();
}

void GS_InputComponent::shutDown()
{
}