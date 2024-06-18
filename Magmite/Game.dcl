#pragma once

#include <memory>
#include <vector>

#include "all.fwd"

namespace magmite
{
	struct game
	{
	private:

		const size_t scenes = 1;

		std::unique_ptr<scene> _active_scene;

		time _time;
		resource_manager _resource_manager;

	public:

		sf::RenderWindow* wnd = nullptr;

		game();

		[[nodiscard]] auto active_scene() -> scene&;

		[[nodiscard]] auto get_time() -> time&;
		[[nodiscard]] auto get_resource_manager() -> resource_manager&;
		
		//inline index_type active_scene(index_type new_scene)
		//{
		//	// [TODO] load / unload scene
		//
		//	index_type old_scene = _active_scene - &*scenes.begin();
		//	_active_scene = &scenes[new_scene];
		//	return old_scene;
		//}
	};
}

