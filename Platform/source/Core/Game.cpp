#include "Core/stdafx.h"
#include "Game.h"

#include "DebugDrawSystem.h"
#include "DebugSystem.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Game.h"
#include "InputSystem.h"
#include "JumpDataSystem.h"
#include "MoveComponent.h"
#include "MoveDataComponent.h"
#include "MovingSystem.h"
#include "NERDGame.h"
#include "NERDSprite.h"
#include "PositionDataSystem.h"
#include "RenderSystem.h"
#include "ScrollSystem.h"
#include "ShootSystem.h"

/// Game - implementation
GS_Game::GS_Game() = default;

GS_Game::~GS_Game()
{
	for ( auto sprite : m_sprites )
	{
		sprite->destroy();
		delete sprite;
	}
	delete m_game;
}

void GS_Game::init()
{
	m_level.resize( k_LEVEL_HEIGHT * k_LEVEL_WIDTH, 0u );

	m_game = new NERDGame();
	m_game->initialize( k_SCREEN_WIDTH * k_SPRITE_WIDTH, k_SCREEN_HEIGHT * k_SPRITE_HEIGHT );

	m_sprites.push_back( m_game->createSpriteFromBMP( "data//grassLeft.bmp" ) );
	m_sprites.push_back( m_game->createSpriteFromBMP( "data//grassMid.bmp" ) );
	m_sprites.push_back( m_game->createSpriteFromBMP( "data//grassRight.bmp" ) );
	m_sprites.push_back( m_game->createSpriteFromBMP( "data//endFlag.bmp" ) );
	m_maxSprites = m_sprites.size();

	loadLevel();

	m_isPlayerDead = false;
	m_shouldRestart = false;
	m_shouldLoadNewLevel = false;
	m_isLevelClear = false;
	m_isRunning = true;

	m_id = GS_EntitySystem::getInstance()->registerEntity();
	GS_ScrollSystem::getInstance()->addComponent( m_id, GS_Vector2( 0.0f, 0.0f ) );
}

void GS_Game::reInit()
{
	GS_EntitySystem::getInstance()->shutDown();
	reloadLevel();
	setScroll( GS_Vector2( 0.0f, 0.0f ) );
	m_isPlayerDead = false;
	m_shouldRestart = false;
	m_shouldLoadNewLevel = false;
	m_isLevelClear = false;
	m_isRunning = true;
}

void GS_Game::loadNewLevel()
{
	GS_EntitySystem::getInstance()->shutDown();
	/*memset( &m_level, -1, sizeof( int ) * k_LEVEL_WIDTH * k_LEVEL_HEIGHT );*/
	m_level.resize( k_LEVEL_HEIGHT * k_LEVEL_WIDTH, 0u );
	loadLevel();
	setScroll( GS_Vector2( 0.0f, 0.0f ) );
	m_isPlayerDead = false;
	m_shouldRestart = false;
	m_shouldLoadNewLevel = false;
	m_isLevelClear = false;
	m_isRunning = true;
}

bool GS_Game::update()
{
#ifdef _DEBUG
	OPTICK_EVENT();
#endif // _DEBUG

	if ( m_game->update() )
	{
		renderLevel();
		GS_EntitySystem::getInstance()->process( m_game->getElapsedTime() );

		if ( m_game->getKeyState() & NERDGame::NERD_KEY_SPACE )
		{
			m_isRunning = false;
		}
		if ( m_isLevelClear )
		{
			m_shouldLoadNewLevel = true;
			m_idLevel++;
			if ( m_idLevel > 2 )
			{ // we only have 3 levels for now
				m_idLevel = 0;
			}
			loadNewLevel();
		}

		if ( m_isPlayerDead )
		{
			//m_shouldRestart = true; // uncomment to restart automatically the level
			m_isRunning = false;
		}
		m_game->postUpdate();
		return true;
	}
	m_isRunning = false;
	return false;
}

void GS_Game::shutDown()
{
	// remove tiles
	std::vector< GS_Sprite* >::iterator it = m_sprites.begin();
	const std::vector< GS_Sprite* >::const_iterator itEnd = m_sprites.end();
	for ( ; it != itEnd; ++it )
	{
		( *it )->destroy();
	}
	// shutdown game
	m_game->shutdown();
}

float GS_Game::getElapsedTime() const
{
	return m_game->getElapsedTime();
}

GS_Sprite* GS_Game::loadSprite( const std::string& _path )
{
	return m_game->createSpriteFromBMP( _path.c_str() );
}

bool GS_Game::isRunning() const
{
	return m_isRunning;
}

bool GS_Game::shouldRestart() const
{
	return m_shouldRestart;
}

int GS_Game::getKeyState() const
{
	return m_game->getKeyState();
}

int GS_Game::getJoypadValueX( int id ) const
{
	return m_game->getJoypadValueX( id );
}

int GS_Game::getJoypadValueY( int id ) const
{
	return m_game->getJoypadValueY( id );
}

int GS_Game::getJoypadBtn( int id ) const
{
	return m_game->getJoypadBtn( id );
}

size_t GS_Game::getTile( size_t _id ) const
{
	if ( _id >= 0 && _id < k_LEVEL_HEIGHT * k_LEVEL_WIDTH )
	{
		return m_level[ _id ];
	}
	return std::numeric_limits< size_t >::max();
}

void GS_Game::loadLevel()
{
#ifdef _DEBUG
	OPTICK_EVENT();
#endif // _DEBUG

	std::fstream file;
	char num[ 2 ] = " ";
	sprintf_s( num, "%zu", m_idLevel );
	std::string fileName( "data//level" );
	fileName.append( num );
	fileName.append( ".txt" );
	file.open( fileName.c_str(), std::ios::in );
	if ( file.is_open() )
	{
		int i = 0;
		int c = file.get();
		while ( file.good() )
		{
			if ( c >= '0' && c <= '9' )
			{
				int id = c - 48;
				if ( id > m_maxSprites && id < 9 )
				{ // enemy!
					createEnemy( id, i );
					id = 0;
				}
				else if ( id == 9 )
				{ // player!
					createPlayer( i );
					id = 0;
				}
				m_level[ i++ ] = id;
			}
			c = file.get();
		}
		file.close();
	}
	else
	{
		std::cout << "Level Load error." << std::endl;
	}
}

void GS_Game::reloadLevel()
{
	std::fstream file;
	char num[ 2 ] = " ";
	sprintf_s( num, "%zu", m_idLevel );
	std::string fileName( "data//level" );
	fileName.append( num );
	fileName.append( ".txt" );
	file.open( fileName.c_str(), std::ios::in );
	if ( file.is_open() )
	{
		int i = 0;
		int c = file.get();
		while ( file.good() )
		{
			if ( c >= '0' && c <= '9' )
			{
				int id = c - 48;
				if ( id > m_maxSprites && id < 9 )
				{ // enemy!
					createEnemy( id, i );
				}
				else if ( id == 9 )
				{ // player!
					createPlayer( i );
				}
				++i;
			}
			c = file.get();
		}
		file.close();
	}
	else
	{
		std::cout << "Level reload error." << std::endl;
	}
}

void GS_Game::renderLevel()
{
#ifdef _DEBUG
	OPTICK_EVENT();
#endif // _DEBUG

	for ( size_t i = 0u; i < k_LEVEL_WIDTH; ++i )
	{
		for ( size_t j = 0u; j < k_LEVEL_HEIGHT; ++j )
		{
			size_t id = m_level[ j * k_LEVEL_WIDTH + i ];
			if ( id > 0 && id <= m_maxSprites )
			{
				auto x = static_cast< int >( i * k_SPRITE_WIDTH - getScroll().x );
				auto y = static_cast< int >( j * k_SPRITE_HEIGHT - getScroll().y );

				m_sprites[ id - 1 ]->draw( x, y, 1 );
#ifdef _DEBUG
				m_sprites[ id - 1 ]->draw_debug( x, y );
#endif // _DEBUG
			}

#ifdef _DEBUG
			/*if ( id == 0 )
			{
				SDL_SetRenderDrawColor( m_game->renderer, 255, 0, 0, 255 );
				SDL_Rect position;
				position.x = static_cast< int >( i * k_SPRITE_WIDTH - getScroll().x );
				position.y = static_cast< int >( j * k_SPRITE_HEIGHT - getScroll().y );
				position.w = k_SPRITE_WIDTH;
				position.h = k_SPRITE_HEIGHT;

				const GS_Vector2 extendSprite( static_cast< float >( k_SPRITE_WIDTH ), static_cast< float >( k_SPRITE_HEIGHT ) );
				GS_Vector2 topLeft = GS_Vector2( static_cast< float >( ( i % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH ) - getScroll().x,
					static_cast< float >( ( i / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT ) - getScroll().y );
				GS_AABB tile( topLeft, extendSprite );

				if ( GS_MoveDataComponent* playerMoveCompo = GS_PositionDataSystem::getInstance()->getComponent( m_playerID ) )
				{
					const GS_AABB playerAABB( playerMoveCompo->get_position(), extendSprite);

					//if ( playerAABB.overlaps( tile ) )
					{
						SDL_RenderFillRect( m_game->renderer, &position );
					}
					//else
					{
						//SDL_RenderDrawRect( m_game->renderer, &position );
					}
				}
			}*/
#endif // _DEBUG
		}
	}
}

void GS_Game::setLevelClear()
{
	m_isLevelClear = true;
}

void GS_Game::setPlayerDead()
{
	m_isPlayerDead = true;
}

void GS_Game::createEnemy( const  int _type, const int _idCell ) const
{
	/*char buffer[ 256 ];
	GetPrivateProfileString( "Move", "SpeedEnemy", "150", buffer, 256, ".\\data\\config.ini");
	const float speed = static_cast< float >( atof( buffer ) );*/
	const float speed = 150.0f;

	size_t idEntity = GS_EntitySystem::getInstance()->registerEntity();
	GS_Vector2 position = GS_Vector2( static_cast< float >( ( _idCell % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH ), static_cast< float >( ( _idCell / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT ) );
	GS_PositionDataSystem::getInstance()->addComponent( idEntity, position, speed );
	GS_RenderSystem::getInstance()->addComponent( idEntity, "data//enemy.bmp" );
	GS_MovingSystem::getInstance()->addComponent( idEntity, SLIDER );
	if ( _type == 6 )
	{ // enemy shooter
		GS_ShootSystem::getInstance()->addComponent( idEntity );
	}
	GS_ScrollSystem::getInstance()->addComponent( idEntity, GS_Vector2( -1.0f, 0.0f ) );
}

void GS_Game::createPlayer( const int _idCell )
{
	/*char buffer[ 256 ];
	GetPrivateProfileString( "Move", "SpeedPlayer", "150", buffer, 256, ".\\data\\config.ini");
	float speed = static_cast< float >( atof( buffer ) );*/
	const float speed = 150.0f;

	m_playerID = GS_EntitySystem::getInstance()->registerEntity();
	GS_Vector2 position = GS_Vector2( static_cast< float >( ( _idCell % k_LEVEL_WIDTH ) * k_SPRITE_WIDTH ), static_cast< float >( ( _idCell / k_LEVEL_WIDTH ) * k_SPRITE_HEIGHT ) );
	GS_PositionDataSystem::getInstance()->addComponent( m_playerID, position, speed );
	GS_RenderSystem::getInstance()->addComponent( m_playerID, "data//player.bmp" );
	GS_InputSystem::getInstance()->addComponent( m_playerID );
	GS_MovingSystem::getInstance()->addComponent( m_playerID, KEYBOARD );
	GS_JumpDataSystem::getInstance()->addComponent( m_playerID );
#ifdef _DEBUG
	DebugSystem::getInstance()->addComponent( m_playerID );
	DebugDrawSystem::getInstance()->addComponent( m_playerID );
#endif // _DEBUG
}

const GS_Vector2& GS_Game::getScroll() const
{
	return GS_ScrollSystem::getInstance()->getComponent( m_id )->get_scroll();
}

void GS_Game::setScroll( const GS_Vector2& new_scroll )
{
	GS_ScrollSystem::getInstance()->getComponent( m_id )->update_scroll( new_scroll );
}