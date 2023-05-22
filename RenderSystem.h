#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "System.h"

/// forward declaration
class GS_RenderComponent;

/// GS_RenderSystem
/// This class manages rendering part
class GS_RenderSystem : public GS_Singleton< GS_RenderSystem >, public GS_System
{
public:
	GS_RenderSystem();
	~GS_RenderSystem();

	void addComponent( size_t _id, const char* _path );

private:
	GS_RenderSystem( const GS_RenderSystem& ) = delete;
	GS_RenderSystem& operator=( const GS_RenderSystem& ) = delete;
};

#endif