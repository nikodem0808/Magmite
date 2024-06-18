
#include "all.def"

namespace magmite
{
	[[nodiscard]]
	auto game_object::get_scene()
		-> scene&
	{
		return _game->active_scene();
	}

	[[nodiscard]]
	auto game_object::id() const
		-> eid_type
	{
		return _id;
	}
	auto game_object::id(eid_type new_id)
		-> eid_type
	{
		auto old_id = _id;
		_id = new_id;
		return old_id;
	}

	[[nodiscard]]
	auto game_object::parent_id() const
		-> eid_type
	{
		return _parent_id;
	}
	auto game_object::parent_id(eid_type new_parent_id)
		-> eid_type
	{
		auto old_parent_id = _parent_id;

		if (parent_id() != invalid_eid)
		{
			auto& parent = get_scene().get_game_object(parent_id());

			parent.children().erase(parent.children().find(parent_id()));
		}

		if (get_scene().game_object_exists(new_parent_id))
		{
			auto& new_parent = get_scene().get_game_object(new_parent_id);
			new_parent.children().insert(_id);
		}

		_parent_id = new_parent_id;

		return old_parent_id;
	}

	[[nodiscard]]
	auto game_object::active() const
		-> bool
	{
		return _active;
	}
	auto game_object::active(bool new_active)
		-> bool
	{
		auto old_active = new_active;
		_active = new_active;
		return old_active;
	}

	[[nodiscard]]
	auto game_object::name() const
		-> const std::string&
	{
		return _name;
	}
	auto game_object::name(std::string new_name)
		-> std::string
	{
		auto old_name = std::move(_name);
		_name = std::move(new_name);
		return old_name;
	}

	[[nodiscard]]
	auto game_object::transform()
		-> magmite::transform&
	{
		return _transform;
	}

	[[nodiscard]]
	auto game_object::children() -> std::unordered_set<eid_type>&
	{
		return _children;
	}

}
