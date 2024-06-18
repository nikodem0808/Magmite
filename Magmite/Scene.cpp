
#include "all.def"

// "unresolved external symbol"
#include "GameObject.cpp"

namespace magmite
{

	scene::scene(game& parent)
		: _game{ &parent }
	{
		for (eid_type i = 0; i < config::max_objects; ++i)
		{
			free_eids.push(i);
		}
	}

	[[nodiscard]]
	auto scene::parent()
		-> game&
	{
		return *_game;
	}
	auto scene::parent(game& new_game)
		-> game*
	{
		auto old_game = _game;
		_game = &new_game;
		return old_game;
	}

	[[nodiscard]]
	auto scene::game_object_cell()
		-> ecs::static_cell<game_object>&
	{
		return ecs_container.get_cell_of_type<game_object>();
	}

	auto scene::add_game_object()
		-> eid_type
	{
		eid_type eid = free_eids.front();
		free_eids.pop();

		game_object_cell().alloc(eid);

		auto& obj = game_object_cell().get(eid);
		obj._game = _game;
		obj.id(eid);

		return eid;
	}

	[[nodiscard]]
	auto scene::game_object_exists(eid_type eid)
		-> bool
	{
		return game_object_cell().exists(eid);
	}

	auto scene::get_game_object(eid_type eid)
		-> game_object&
	{
		return game_object_cell().get(eid);
	}

	auto scene::destroy_game_object(eid_type eid)
		-> bool
	{
		if (!game_object_exists(eid))
		{
			return false;
		}

		auto& target = get_game_object(eid);

		// [TODO] detach from parent and cascade to children
		for (auto child_eid : target.children())
		{
			destroy_game_object(child_eid);
		}

		if (target.parent_id() != invalid_eid)
		{
			auto& parent = get_game_object(target.parent_id());
			parent.children().erase(parent.children().find(target.id()));
			target.parent_id(invalid_eid);
		}

		meta::for_constexpr<1ULL, config::component_type_count + 1>([&, target, this] <size_t i> () mutable {
			if (object_of_type_id_exists<i>(target.id()))
			{
				ecs_container.get_cell_by_type_id<i>().free(eid);
			}
		});

		free_eids.push(eid);

		return true;
	}
}
