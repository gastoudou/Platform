#ifndef __JUMP_DATA_SYSTEM_H__
#define __JUMP_DATA_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "Store.h"

/// forward declaration
class GS_JumpDataComponent;

/// GS_JumpDataSystem
/// This class stores jump data components
class GS_JumpDataSystem final : public GS_Singleton< GS_JumpDataSystem >, public GS_Store
{
public:
	GS_JumpDataSystem();
	~GS_JumpDataSystem();

	void addComponent( size_t );
	GS_JumpDataComponent* getComponent( size_t ) const;

private:
	GS_JumpDataSystem( const GS_JumpDataSystem& );
	GS_JumpDataSystem& operator=( const GS_JumpDataSystem& ) = delete;
};

#endif