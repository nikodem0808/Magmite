#pragma once

#include <array>
#include <vector>
#include <queue>

#include "all.fwd"

#include "StaticCell.dcl"
#include "CellTuple.dcl"
#include "GameObject.dcl"
#include "Renderer.dcl"
#include "Behaviour.dcl"
#include "LuaScript.dcl"

// #include "ForConstexpr.hpp"
// #include "Config.hpp"
// #include "Component.hpp"
// #include "Transform.hpp"
// #include "LuaScript.hpp"
// #include "Behaviour.hpp"
// #include "Renderer.hpp"
// #include "CellTuple.hpp"
#include "Time.hpp"

namespace magmite
{
	struct scene
	{

		game* _game = nullptr;
		time _time{};

		ecs::cell_tuple <
			game_object,
			renderer,
			behaviour,
			lua_script
		> ecs_container;

		std::queue<eid_type> free_eids{};

		scene(game& parent);

		[[nodiscard]] auto parent() -> game&;
		auto parent(game& new_game) -> game*;

		[[nodiscard]]
		auto game_object_cell() -> ecs::static_cell<game_object>&;

		auto add_game_object() -> eid_type;

		[[nodiscard]] auto game_object_exists(eid_type eid) -> bool;

		template <typename T>
		[[nodiscard]] auto object_of_type_exists(uid_type uid) -> bool;

		template <size_t type_id>
		[[nodiscard]] auto object_of_type_id_exists(uid_type uid) -> bool;

		template <typename T>
		[[nodiscard]] auto get_object_of_type(uid_type uid) -> auto&;

		template <size_t type_id>
		[[nodiscard]] auto get_object_by_type_id(uid_type uid) -> auto&;
		
		auto get_game_object(eid_type eid) -> game_object&;

		auto destroy_game_object(eid_type eid) -> bool;

		template <typename C>
			requires (not std::is_same_v<C, game_object>)
		auto add_component(eid_type eid) -> uid_type;
		
		template <typename C>
			requires (not std::is_same_v<C, game_object>)
		auto remove_component(eid_type eid) -> uid_type;
	};
}






