#ifndef __SCROLL_DATA_COMPONENT_H__
#define __SCROLL_DATA_COMPONENT_H__

/// includes
#include "Component.h"

/// GS_ScrollDataComponent
/// This class provides data for scrolling
class GS_ScrollDataComponent final : public GS_DataComponent
{
public:
	GS_ScrollDataComponent( size_t );
	virtual ~GS_ScrollDataComponent();

	void update_scroll( const GS_Vector2& new_scroll );
	const GS_Vector2& get_scroll() const;

private:
	GS_ScrollDataComponent() = delete;
	GS_ScrollDataComponent( const GS_ScrollDataComponent& ) = delete;
	GS_ScrollDataComponent& operator=( const GS_ScrollDataComponent& ) = delete;

	/// scrolling data
	GS_Vector2 m_lastScrollOnX = GS_Vector2( 0.0f, 0.0f );
};

#endif