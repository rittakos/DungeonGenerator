#pragma once
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

class Guard
{
public: 

	virtual void end() const = 0;
};

class LeakDetectionGuard : public Guard
{
public:
	LeakDetectionGuard() = default;

	virtual void end() const override { _CrtDumpMemoryLeaks(); }
	virtual ~LeakDetectionGuard() { end(); };
};