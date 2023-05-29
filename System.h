#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#pragma once

class GS_LogicalComponent;

class GS_System
{
public:
	virtual ~GS_System()
	{
		shutDown();
	}

	void process( const float _dt );
	void shutDown();

protected:
	std::vector< GS_LogicalComponent* > m_components;
	std::map< size_t, size_t > m_indexTable; // lhs: entity id, rhs: component id in vector
};

#endif