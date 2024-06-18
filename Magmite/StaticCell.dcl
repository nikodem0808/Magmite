#pragma once

#include <array>
#include <concepts>

#include "all.fwd"

namespace magmite::ecs
{
	template <typename T>
	struct static_cell
	{
		static inline constexpr size_t cell_size = config::max_objects;

		std::array<T, cell_size> objects{};
		std::array<index_type, cell_size> uid_map{};
		index_type used_objects = 0;

		static_cell() noexcept;

		T& get(uid_type uid);

		T& get_raw(index_type i);

		bool exists(uid_type uid);

		uid_type alloc(uid_type uid);

		void move_id(uid_type new_uid, uid_type uid);

		bool free(uid_type uid);
	};
}


