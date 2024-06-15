#pragma once

struct Message
{
	Message();
	virtual ~Message();

	uint64_t id = 0u;
	void* data = nullptr;
};