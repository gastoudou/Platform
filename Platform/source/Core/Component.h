#ifndef __COMPONENT_H__
#define __COMPONENT_H__

/// LogicalComponent
/// This class provides an interface for logical components (with update/render, without data)
class GS_LogicalComponent
{
public:
	explicit GS_LogicalComponent( size_t _parentId )
		: m_id( _parentId )
	{
	}

	virtual ~GS_LogicalComponent() = default;

	virtual void init() = 0;
	virtual void update( const float _dt ) = 0;
	virtual void shutDown() = 0;

protected:
	size_t m_id;
	std::mutex lock;

private:
	GS_LogicalComponent();
	GS_LogicalComponent( const GS_LogicalComponent& );
	GS_LogicalComponent& operator=( const GS_LogicalComponent& ) = delete;
};

/// DataComponent
/// This class provides an interface for data components (no logical part)
class GS_DataComponent
{
public:
	explicit GS_DataComponent( size_t _parentId )
		: m_id( _parentId )
	{
	}

	virtual ~GS_DataComponent() = default;

protected:
	size_t m_id;
	std::mutex lock;

private:
	GS_DataComponent();
	GS_DataComponent( const GS_DataComponent& );
	GS_DataComponent& operator=( const GS_DataComponent& ) = delete;
};

#endif