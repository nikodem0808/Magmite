#pragma once

#include <queue>

#include "all.fwd"
#include "StaticCell.dcl"

namespace magmite::ecs
{
	template <typename T, typename... R>
	struct cell_tuple<T, R...> : cell_tuple<R...>
	{
		using base = cell_tuple<R...>;
		using component_type = T;

		static_cell<T> cell;

		template <typename C>
		auto get_cell_of_type() -> static_cell<C>&;

		template <size_t type_id>
		auto get_cell_by_type_id() -> auto&;

	};

	template <typename T>
	struct cell_tuple<T>
	{
		using component_type = T;
		using base_type = void;

		static_cell<T> cell;

		template <typename C>
		auto get_cell_of_type() -> static_cell<C>&;
		
		template <size_t type_id>
		auto get_cell_by_type_id() -> auto&;
	};

}

