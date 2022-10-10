#pragma once

#include "log.h"

namespace Test
{
	static void Expect_True(bool expression)
	{
		expression ? Log::info("OK") : Log::error("ERROR");
	}
}