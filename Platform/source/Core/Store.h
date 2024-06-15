#ifndef __BASE_STORE_H__
#define __BASE_STORE_H__

#pragma once

class GS_DataComponent;

class GS_Store
{
public:
	GS_Store();
	virtual ~GS_Store();
	void shutDown();

protected:
	std::vector< GS_DataComponent* > m_components;
	std::map< size_t, size_t > m_indexTable; // lhs: entity id, rhs: component id in vector
};

#endif