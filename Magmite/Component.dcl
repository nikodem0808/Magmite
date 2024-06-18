#pragma once

#include <vector>
#include <cstdint>

#include "all.fwd"

namespace magmite
{
	struct component
	{

	protected:

		game* _game = nullptr;
		bool _active = true;

		eid_type _parent_id = invalid_eid;

		friend scene;
	public:

		[[nodiscard]] auto parent_id() const -> eid_type;
		auto parent_id(eid_type new_parent_id) -> eid_type;

		[[nodiscard]] auto parent() -> game_object&;

		[[nodiscard]] auto active() const -> bool;
		auto active(bool new_active) -> bool;
	};

}
