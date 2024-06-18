
#include "all.def"

namespace magmite
{
	game::game()
		: _active_scene{ std::make_unique<scene>(*this) }
	{ }

	[[nodiscard]] auto game::active_scene()
		-> scene&
	{
		return *_active_scene;
	}

	[[nodiscard]] auto game::get_time()
		-> time&
	{
		return _time;
	}

	[[nodiscard]] auto game::get_resource_manager()
		-> resource_manager&
	{
		return _resource_manager;
	}

	//index_type active_scene(index_type new_scene)
	//{
	//	// [TODO] load / unload scene
	//
	//	index_type old_scene = _active_scene - &*scenes.begin();
	//	_active_scene = &scenes[new_scene];
	//	return old_scene;
	//}

}


