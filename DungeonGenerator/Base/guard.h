#pragma once
#include <crtdbg.h>
#include <chrono>
#include "log.h"

#define _CRTDBG_MAP_ALLOC

class Guard
{
public: 

	virtual ~Guard() = default;
};

class LeakDetectionGuard final : public Guard
{
public:
	LeakDetectionGuard() = default;

	void end() const { _CrtDumpMemoryLeaks(); }
	virtual ~LeakDetectionGuard() override { end(); }
};

class TimeGuard final : public Guard
{
	std::chrono::steady_clock::time_point startTime;
	const std::string text;
public:
	explicit TimeGuard(std::string text = "") : text{text} { startTime = std::chrono::steady_clock::now(); }

	void end() const 
	{ 
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count();
		std::string result = "elapsed time: " + std::to_string(elapsed) + "ms";
		Log::info(text + " " + result);
	}
	virtual ~TimeGuard() override { end(); }
};