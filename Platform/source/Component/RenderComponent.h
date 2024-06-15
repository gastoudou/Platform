#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__

/// includes
#include "Component.h"

/// RenderComponent
/// This class represents the rendering component. Used to display data on screen.
class GS_RenderComponent final : public GS_LogicalComponent
{
public:
	GS_RenderComponent( size_t );
	virtual ~GS_RenderComponent();

	void init() override;
	void update( const float ) override; // render here
	void shutDown() override;

private:
	GS_RenderComponent();
	GS_RenderComponent( const GS_RenderComponent& );
	GS_RenderComponent& operator=( const GS_RenderComponent& ) = delete;
};

#endif // __RENDER_COMPONENT_H__