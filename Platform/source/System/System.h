#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#pragma once

class GS_LogicalComponent;
struct Message;

class GS_System
{
public:
	virtual ~GS_System()
	{
		shutDown();
	}

	void process( const float _dt );
	void shutDown();

	virtual void handle_message( const Message& )
	{
		assert( false );
	}

protected:
	std::vector< GS_LogicalComponent* > m_components;
	//std::vector< Message > m_messages;
	std::map< size_t, size_t > m_indexTable; // lhs: entity id, rhs: component id in vector
};

#endif