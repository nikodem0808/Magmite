#pragma once

#include <string>

#include "all.fwd"
#include "Component.dcl"

namespace magmite
{
	struct lua_script : component
	{
		static inline constexpr size_t type_id = 2;

		void load_from_file(const std::string& path);

		void start();

		void update();
	};
}


