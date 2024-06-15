#ifndef __MOVING_SYSTEM_H__
#define __MOVING_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "System.h"

/// forward declaration
class GS_MoveComponent;

enum MvtType : size_t;
enum Direction : int;

/// GS_MovingSystem
/// This class stores move components
class GS_MovingSystem final : public GS_Singleton< GS_MovingSystem >, public GS_System
{
public:
	GS_MovingSystem();

	void addComponent( size_t, MvtType );

	void setMove( size_t, Direction );
	void setJump( size_t );

private:
	std::mutex lock;
};

#endif