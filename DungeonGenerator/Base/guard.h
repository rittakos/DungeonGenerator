#pragma once
#include <crtdbg.h>
#include <chrono>
#include "log.h"

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

class TimeGuard : public Guard
{
private:
	std::chrono::steady_clock::time_point startTime;
	const std::string text;
public:
	TimeGuard(std::string text = "") : text{text} { startTime = std::chrono::steady_clock::now(); }

	virtual void end() const override 
	{ 
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count();
		std::string result = "elapsed time: " + std::to_string(elapsed) + "ms";
		Log::info(text + " " + result);
	}
	virtual ~TimeGuard() { end(); };
};