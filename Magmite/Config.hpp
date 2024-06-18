#pragma once

#include <cstdint>


namespace magmite
{
	using eid_type = size_t;
	using uid_type = size_t;
	using index_type = size_t;

	inline constexpr eid_type invalid_eid = SIZE_MAX;
	inline constexpr uid_type invalid_uid = SIZE_MAX;
	inline constexpr index_type invalid_index = SIZE_MAX;
}


namespace magmite::config
{
	
	inline constexpr size_t max_objects = 102400;
	static_assert(max_objects < SIZE_MAX, "magmite::ecs::static_cell<typename> : Config parameter 'magmite::config::max_objects' must be smaller than SIZE_MAX");

	inline constexpr size_t component_type_count = 3;

}


