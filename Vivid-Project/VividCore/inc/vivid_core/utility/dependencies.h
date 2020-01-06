#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(utility)

class dependencies
{
private:
	dependencies();
public:
	dependencies(dependencies const&) = delete;
	void operator=(dependencies const&) = delete;

	static dependencies& get_instance();
};

END_NAME(utility)
END_ENGINE