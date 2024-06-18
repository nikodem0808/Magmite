#pragma once

#include <SFML/Graphics.hpp>

#include "all.fwd"
#include "Component.dcl"

namespace magmite
{
	struct renderer : component
	{
		static inline constexpr size_t type_id = 3;

		sf::Sprite sprite;

		void render(sf::RenderTarget& render_target);
	};
}














