
#include "all.def"

namespace magmite
{

	[[nodiscard]]
	auto component::parent_id() const
		-> eid_type
	{
		return _parent_id;
	}
	auto component::parent_id(eid_type new_parent_id)
		-> eid_type
	{
		auto old_parent_id = _parent_id;
		_parent_id = new_parent_id;
		return old_parent_id;
	}

	[[nodiscard]]
	auto component::parent()
		-> game_object&
	{
		return _game->active_scene().get_game_object(_parent_id);
	}

	[[nodiscard]]
	auto component::active() const
		-> bool
	{
		return _active;
	}
	auto component::active(bool new_active)
		-> bool
	{
		auto old_active = new_active;
		_active = new_active;
		return old_active;
	}

}
