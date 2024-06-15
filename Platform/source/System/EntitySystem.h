#ifndef __ENTITY_SYSTEM_H__
#define __ENTITY_SYSTEM_H__

/// includes
#include "Singleton.h"

/// forward declaration
class GS_Entity;

/// GS_EntitySystem
/// This class manages entities in the game
class GS_EntitySystem : public GS_Singleton< GS_EntitySystem >
{
public:
	GS_EntitySystem();
	virtual ~GS_EntitySystem();

	void process( const float );
	void shutDown();

	size_t registerEntity();
	GS_Entity* getEntityById( size_t ) const;
	void killEntityById( size_t );
	const std::vector< GS_Entity* >& getAllEntities() const;

private:
	GS_EntitySystem( const GS_EntitySystem& );
	GS_EntitySystem& operator=( const GS_EntitySystem& ) = delete;

	std::vector< GS_Entity* > m_entities;
	std::vector< GS_Entity* > m_toRemove;
	size_t m_nextId;
	mutable std::mutex lock;
};

#endif