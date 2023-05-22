#ifndef __SCROLL_DATA_COMPONENT_H__
#define __SCROLL_DATA_COMPONENT_H__

/// includes
#include "Component.h"

/// GS_ScrollDataComponent
/// This class provides data for scrolling
class GS_ScrollDataComponent : public GS_DataComponent
{
public:
	GS_ScrollDataComponent( size_t );
	virtual ~GS_ScrollDataComponent();

	/// scrolling data
	float m_lastScrollOnX = 0.0f;
private:
	GS_ScrollDataComponent() = delete;
	GS_ScrollDataComponent( const GS_ScrollDataComponent& ) = delete;
	GS_ScrollDataComponent& operator=( const GS_ScrollDataComponent& ) = delete;
};

#endif