#include "Input.hpp"


namespace magmite
{
	std::array<bool, sf::Keyboard::KeyCount> input::key_state{};
	std::array<bool, sf::Keyboard::KeyCount> input::key_state_last_frame{};
	std::array<bool, sf::Keyboard::KeyCount> input::key_down{};
	std::array<bool, sf::Keyboard::KeyCount> input::key_up{};

	std::vector<std::function<void(sf::Vector2i)>> input::on_lmb_clicked{};

	[[nodiscard]] bool input::get_key_state(sf::Keyboard::Key kc)
	{
		return key_state[static_cast<size_t>(kc)];
	}

	[[nodiscard]] bool input::get_key_down(sf::Keyboard::Key kc)
	{
		return key_down[static_cast<size_t>(kc)];
	}

	[[nodiscard]] bool input::get_key_up(sf::Keyboard::Key kc)
	{
		return key_up[static_cast<size_t>(kc)];
	}
}