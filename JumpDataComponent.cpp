#include "stdafx.h"
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