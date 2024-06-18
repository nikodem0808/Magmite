#pragma once



#include <array>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>



namespace magmite
{
	struct input
	{
		static std::array<bool, sf::Keyboard::KeyCount> key_state;
		static std::array<bool, sf::Keyboard::KeyCount> key_state_last_frame;
		static std::array<bool, sf::Keyboard::KeyCount> key_down;
		static std::array<bool, sf::Keyboard::KeyCount> key_up;

		static std::vector<std::function<void(sf::Vector2i)>> on_lmb_clicked;

		/* [TODO] */
		[[nodiscard]] bool get_key_state(sf::Keyboard::Key kc);
		[[nodiscard]] bool get_key_down(sf::Keyboard::Key kc);
		[[nodiscard]] bool get_key_up(sf::Keyboard::Key kc);
	};
}