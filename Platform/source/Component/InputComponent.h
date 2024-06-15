#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

/// includes
#include "Component.h"

/// InputComponent
/// This class is used to manage inputs info got from keyState function from NERDGame
class GS_InputComponent : public GS_LogicalComponent
{
public:
	explicit GS_InputComponent( size_t );
	virtual ~GS_InputComponent();

	virtual void init();
	virtual void update( const float );
	virtual void render() {} // no render
	virtual void shutDown();

private:
	GS_InputComponent();
	GS_InputComponent( const GS_InputComponent& );
	GS_InputComponent& operator=( const GS_InputComponent& ) = delete;

	bool m_UpKeyRelease = true;
	bool m_UpJoyRelease = true;
};

#endif