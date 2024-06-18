#pragma once

#include <SFML/System.hpp>

#include "all.fwd"

namespace magmite
{

	struct transform
	{
		sf::Vector2f position = { 0, 0 };
		float rotation = 0;
		sf::Vector2f scale = { 1, 1 };
		int layer = 0;

		// constexpr inline transform() noexcept {}
	};

}



