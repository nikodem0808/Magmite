#pragma once

#include <SFML/Graphics.hpp>

#include "Magmite.hpp"

namespace maingame
{
	extern sf::Font font;
	extern sf::Text red_score_text;
	extern sf::Text black_score_text;
	extern sf::Text win_text;

	void init_game(
		magmite::game& game,
		magmite::scene& scene,
		sf::RenderWindow& wnd
	);
}


