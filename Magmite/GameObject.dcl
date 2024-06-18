#pragma once

#include <vector>
#include <unordered_set>
#include <string_view>
#include <bitset>

#include "all.fwd"
#include "Transform.dcl"
#include "Component.dcl"

namespace magmite
{
	struct game_object
	{
		static inline constexpr size_t type_id = 0;

	protected:
		game* _game = nullptr;

		bool _active = true;
		eid_type _id = invalid_uid;
		eid_type _parent_id = invalid_uid;

		std::string _name;
		std::unordered_set<std::string> _tags;

		magmite::transform _transform;

		std::unordered_set<eid_type> _children;

		friend scene;

	public:

		[[nodiscard]]
		auto get_scene() -> scene&;

		[[nodiscard]]
		auto id() const -> eid_type;
		auto id(eid_type new_id) -> eid_type;

		[[nodiscard]] auto parent_id() const -> eid_type;
		auto parent_id(eid_type new_parent_id) -> eid_type;

		template <typename C>
		auto has_component() -> bool;

		template <typename C>
		auto get_component() -> C&;

		template <typename C>
		auto add_component() -> uid_type;

		template <typename C>
		auto remove_component() -> bool;

		[[nodiscard]] auto active() const -> bool;
		auto active(bool new_active) -> bool;

		[[nodiscard]] auto name() const -> const std::string&;
		auto name(std::string new_name) -> std::string;

		[[nodiscard]] auto transform() -> magmite::transform&;

		[[nodiscard]] auto children() -> std::unordered_set<eid_type>&;

		//scene& get_scene()
		//{
		//	return _game->active_scene(); // [TODO] clean up
		//}

		//template <typename T>
		//[[nodiscard]] inline const auto& get_component_of_type() const
		//{
		//	return get_scene().get_object_of_type<T>(_id);
		//}
	};
}







