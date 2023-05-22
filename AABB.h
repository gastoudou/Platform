#ifndef __AABB_H__
#define __AABB_H__

/// GS_AABB
/// This class represents an axis aligned bounding box
class GS_AABB
{
public:
	explicit GS_AABB( const GS_Vector2& p, const GS_Vector2& e )
		: P( p ), E( e )
	{
	}

	const bool overlaps( const GS_AABB& _lhs ) const
	{
		const GS_Vector2 T = _lhs.P - P;
		return fabs( T.x ) < E.x && fabs( T.y ) < E.y;
	}

private:
	GS_AABB();
	GS_AABB( const GS_AABB& );
	GS_AABB& operator=( const GS_AABB& ) = delete;

	GS_Vector2 P;	// top left corner
	GS_Vector2 E;	// extend
};

#endif