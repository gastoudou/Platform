#ifndef __ENTITY_H__
#define __ENTITY_H__

/// GS_Entity
/// This class represents an entity
/// An entity is just a unique id to specify the components related to this entity
class GS_Entity
{
	friend class GS_EntitySystem;
public:
	~GS_Entity();

	size_t getId() const;

private:
	explicit GS_Entity( size_t );

	GS_Entity() = delete;
	GS_Entity( const GS_Entity& ) = delete;
	GS_Entity& operator=( const GS_Entity& ) = delete;

	size_t m_id;
};

#endif