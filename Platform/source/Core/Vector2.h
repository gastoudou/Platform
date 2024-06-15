#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

/// GS_Vector2
/// This class represents a 2D vector
class GS_Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	GS_Vector2()
		: x( 0.0f )
		, y( 0.0f )
	{
	}

	explicit GS_Vector2( const float _x, const float _y )
		: x( _x )
		, y( _y )
	{
	}

	~GS_Vector2()
	{
	}

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	const GS_Vector2 operator+( const GS_Vector2& _lhs ) const
	{
		return GS_Vector2( this->x + _lhs.x, this->y + _lhs.y );
	}

	const GS_Vector2& operator+=( const GS_Vector2& _lhs )
	{
		this->x += _lhs.x;
		this->y += _lhs.y;
		return *this;
	}

	const GS_Vector2 operator+=( const GS_Vector2& _lhs ) const
	{
		return GS_Vector2( this->x + _lhs.x, this->y + _lhs.y );
	}

	const GS_Vector2 operator-( const GS_Vector2& _lhs ) const
	{
		return GS_Vector2( this->x - _lhs.x, this->y - _lhs.y );
	}

	const GS_Vector2& operator-=( const GS_Vector2& _rhs )
	{
		this->x -= _rhs.x;
		this->y -= _rhs.y;
		return *this;
	}

	const GS_Vector2 operator-=( const GS_Vector2& _rhs ) const
	{
		return GS_Vector2( this->x - _rhs.x, this->y - _rhs.y );
	}

	const GS_Vector2 operator*( const float _f ) const
	{
		return GS_Vector2( this->x * _f, this->y * _f );
	}

	const GS_Vector2& operator*=( const float _f )
	{
		this->x *= _f;
		this->y *= _f;
		return *this;
	}

	const GS_Vector2 operator*=( const float _f ) const
	{
		return GS_Vector2( this->x * _f, this->y * _f );
	}

	const GS_Vector2 operator/( const float _f ) const
	{
		return GS_Vector2( this->x / _f, this->y / _f );
	}

	const GS_Vector2& operator/=( const float _f )
	{
		this->x /= _f;
		this->y /= _f;
		return *this;
	}

	const GS_Vector2 operator/=( const float _f ) const
	{
		return GS_Vector2( this->x / _f, this->y / _f );
	}

	float length() const
	{
		return sqrt( x * x + y * y );
	}

	float lengthSq() const
	{
		return x * x + y * y;
	}
};

#endif