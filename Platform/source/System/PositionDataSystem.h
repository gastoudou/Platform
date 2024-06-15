#ifndef __POSITION_DATA_SYSTEM_H__
#define __POSITION_DATA_SYSTEM_H__

/// includes
#include "Singleton.h"
#include "Store.h"

/// forward declaration
class GS_MoveDataComponent;

/// GS_PositionDataSystem
/// This class stores move data components
class GS_PositionDataSystem final : public GS_Singleton< GS_PositionDataSystem >, public GS_Store
{
public:
	GS_PositionDataSystem();
	~GS_PositionDataSystem();

	void addComponent( size_t, const GS_Vector2 & = GS_Vector2(), const float = 0.0f );
	GS_MoveDataComponent* getComponent( size_t ) const;
};

#endif